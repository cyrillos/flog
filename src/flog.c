#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#include <ffi.h>

#include "flog.h"
#include "util.h"

static char mbuf[1 << 20];

int flog_decode_all(int fdin, int fdout)
{
	flog_msg_t *m = (void *)mbuf;
	ffi_type *args[34] = {
		[0]		= &ffi_type_sint,
		[1]		= &ffi_type_pointer,
		[2 ... 33]	= &ffi_type_slong
	};
	void *values[34];
	ffi_cif cif;
	ffi_arg rc;
	size_t i, ret;
	char *fmt;

	values[0] = (void *)&fdout;

	while (1) {
		ret = read(fdin, mbuf, sizeof(m));
		if (ret == 0)
			break;
		if (ret < 0) {
			fprintf(stderr, "Unable to read a message: %m");
			return -1;
		}
		ret = m->size - sizeof(m);
		if (m->size > sizeof(mbuf)) {
			fprintf(stderr, "The buffer is too small");
			return -1;
		}
		if (read(fdin, mbuf + sizeof(m), ret) != ret) {
			fprintf(stderr, "Unable to read a message: %m");
			return -1;
		}

		fmt = mbuf + m->fmt;
		values[1] = &fmt;

		for (i = 0; i < m->nargs; i++) {
			values[i + 2] = (void *)&m->args[i];
			if (m->mask & (1u << i)) {
				m->args[i] = (long)(mbuf + m->args[i]);
			}
		}

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, m->nargs + 2,
				 &ffi_type_sint, args) == FFI_OK)
			ffi_call(&cif, FFI_FN(dprintf), &rc, values);
	}
	return 0;
}

int flog_enqueue(flog_msg_t *m)
{
	m->size = (m->size + 63) / 64 * 64;
	write(1, m, m->size);
	return 0;
}

extern char *rodata_start;
extern char *rodata_end;

void flog_encode_msg(int fdout, unsigned int nargs, unsigned int mask, const char *format, ...)
{
	flog_msg_t *m = (void *)mbuf;
	va_list argptr;
	char *str_start;
	size_t i, n;

	m->nargs = nargs;
	m->mask = mask;

	str_start = (void *)m->args + sizeof(m->args[0]) * nargs;
	n = strlen(format) + 1;
	if (sizeof(mbuf) < (str_start + n + 1 - mbuf)) {
		fprintf(stderr, "No memory for string argument\n");
		return;
	}
	memcpy(str_start, format, n);
	m->fmt = str_start - mbuf;
	str_start += n;

	va_start(argptr, format);
	for (i = 0; i < nargs; i++) {
		m->args[i] = (long)va_arg(argptr, long);
		/*
		 * If we got a string, we should either
		 * reference it when in rodata, or make
		 * a copy (FIXME implement rodata refs).
		 */
		if (mask & (1u << i)) {
			n = strlen((void *)m->args[i]);

			if (sizeof(mbuf) > (str_start + n + 1 - mbuf)) {
				memcpy(str_start, (void *)m->args[i], n + 1);
				m->args[i] = str_start - mbuf;
				str_start += n + 1;
			} else {
				fprintf(stderr, "No memory for string argument\n");
				return;
			}
		}
	}
	va_end(argptr);
	m->size = str_start - mbuf;

	flog_enqueue(m);
}
