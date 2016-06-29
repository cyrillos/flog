#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <ffi.h>

#include "flog.h"
#include "util.h"

static flog_msg_t **msgq;
static size_t msgq_size;
static size_t msgq_last;

int flog_enqueue(flog_msg_t *m)
{
	static char buf[16<<20];
	static long buf_start = 0;
	static long buf_end = sizeof(buf);
	size_t size;

	static const size_t delta = 128;

	size = sizeof(*msgq) * delta;

	if (msgq_last >= msgq_size) {
		if (buf_end > (buf_start + size)) {
			msgq = (void *)&buf[buf_start];
			msgq_size += delta;
			buf_start += size;
		}
	}

	if (buf_end > buf_start)
		msgq[msgq_last++] = m;
}

void flog_decode_all(int fdout)
{
	ffi_type *args[33] = { [0] = &ffi_type_pointer, [1 ... 32] = &ffi_type_slong };
	void *values[33];
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

extern char *rodata_start;
extern char *rodata_end;

void flog_encode_msg(unsigned int nargs, unsigned int mask, const char *format, ...)
{
	static char buf[16<<20];
	static long buf_start = 0;
	static long buf_end = sizeof(buf);
	size_t size;

	va_list argptr;
	flog_msg_t *m;

	size = sizeof(*m) + sizeof(m->args[0]) * nargs;

	if (buf_end > (buf_start + size)) {
		m = (void *)&buf[buf_start];
		buf_start += size;
	} else
		return;

	if (m) {
		unsigned long v;
		size_t i;

		m->fmt = format;
		m->nargs = nargs;
		m->mask = mask;

		va_start(argptr, format);
		for (i = 0; i < nargs; i++) {
			m->args[i] = (long)va_arg(argptr, long);
			if (mask & (1u << i)) {
				if ((char *)m->args[i] < rodata_start ||
				    (char *)m->args[i] >= rodata_end)
				/*
				 * It's is a pointer to one of
				 * char * form and could be a string,
				 * so figure out if we need to dup it.
				 */
				//m->args[i] = (long)(void *)strdup((void *)m->args[i]);
				;
			}
		}
		va_end(argptr);

		flog_enqueue(m);
	}
}
