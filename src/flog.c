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
	static const size_t delta = 128;
	if (msgq_last <= msgq_size) {
		if (xrealloc_safe(&msgq, sizeof(*msgq) * (msgq_size + delta)))
			return -ENOMEM;
		msgq_size += delta;
	}

	msgq[msgq_last++] = m;
}

void flog_decode_all(int fdout)
{
	ffi_type *args[66] = { [0] = &ffi_type_pointer, [1 ... 64] = &ffi_type_ulong };
	void *values[66];
	ffi_cif cif;
	ffi_arg rc;
	size_t i, j;

	for (i = 0; i < msgq_last; i++) {
		values[0] = (void *)&fdout;
		values[1] = (void *)&msgq[i]->fmt;

		for (j = 0; j < msgq[i]->nargs; j++)
			values[j + 2] = (void *)&msgq[j]->args[j];

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, msgq[i]->nargs + 2,
				 &ffi_type_sint, args) == FFI_OK)
			ffi_call(&cif, FFI_FN(dprintf), &rc, values);
	}
}

void flog_encode_msg(size_t nargs, const char *format, ...)
{
	va_list argptr;
	flog_msg_t *m;

	m = xmalloc(sizeof(*m) + sizeof(m->args[0]) * nargs);
	if (m) {
		unsigned long v;
		size_t i;

		va_start(argptr, format);
		m->type = FLOG_MSG_TYPE_REGULAR;
		m->fmt = format;
		m->nargs = nargs;

		for (i = 0; i < nargs; i++)
			m->args[i] = va_arg(argptr, unsigned long);
		va_end(argptr);
		flog_enqueue(m);
	}
}
