#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <ffi.h>

#include "flog.h"
#include "util.h"

static char mqbuf[32 << 20];
static flog_msg_t **msgq = (flog_msg_t **)(void *)mqbuf;
static unsigned long mqbuf_end = sizeof(mqbuf) / sizeof(msgq[0]);
static size_t msgq_last;

void flog_decode_all(int fdout)
{
	ffi_type *args[34] = {
		[0]		= &ffi_type_sint,
		[1]		= &ffi_type_pointer,
		[2 ... 33]	= &ffi_type_slong
	};
	void *values[34];
	ffi_cif cif;
	ffi_arg rc;
	size_t i, j;

	for (i = 0; i < msgq_last; i++) {
		values[0] = (void *)&fdout;
		values[1] = (void *)&msgq[i]->fmt;

		for (j = 0; j < msgq[i]->nargs; j++)
			values[j + 2] = (void *)&msgq[i]->args[j];

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, msgq[i]->nargs + 2,
				 &ffi_type_sint, args) == FFI_OK)
			ffi_call(&cif, FFI_FN(dprintf), &rc, values);
	}
}

int flog_enqueue(flog_msg_t *m)
{
	static const size_t delta = 128;

	if (mqbuf_end <= (msgq_last + 1)) {
		fprintf(stderr, "No memory for mqbuf\n");
		exit(1);
	}

	msgq[msgq_last++] = m;
	return 0;
}

extern char *rodata_start;
extern char *rodata_end;

static char mbuf[80 << 20];
static unsigned long mbuf_start = 0;
static unsigned long mbuf_end = sizeof(mbuf);

void flog_encode_msg(unsigned int nargs, unsigned int mask, const char *format, ...)
{
	va_list argptr;
	flog_msg_t *m;
	size_t size;

	size = sizeof(*m) + sizeof(m->args[0]) * nargs;

	if (mbuf_end > (mbuf_start + size)) {
		m = (void *)&mbuf[mbuf_start];
		mbuf_start += size;
	} else {
		fprintf(stderr, "No memory for mbuf\n");
		exit(1);
	}

	if (m) {
		char *str_start;
		unsigned long v;
		size_t i;

		m->fmt = format;
		m->nargs = nargs;
		m->mask = mask;

		/*
		 * At least one string present in args.
		 */
		if (mask)
			str_start = (void *)m->args + size;

		va_start(argptr, format);
		for (i = 0; i < nargs; i++) {
			m->args[i] = (long)va_arg(argptr, long);
			/*
			 * If we got a string, we should either
			 * reference it when in rodata, or make
			 * a copy (FIXME implement rodata refs).
			 */
			if (mask & (1u << i)) {
				size_t n = strlen((void *)m->args[i]);

				if (mbuf_end > (mbuf_start + n + 1)) {
					memcpy(str_start, (void *)m->args[i], n + 1);
					m->args[i] = (long)(void *)str_start;
					mbuf_start += n + 1;
					str_start += n + 1;
				} else {
					fprintf(stderr, "No memory for string argument\n");
					exit(1);
				}
			}
		}
		va_end(argptr);

		flog_enqueue(m);
	}
}
