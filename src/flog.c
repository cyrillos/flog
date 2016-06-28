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
	static const size_t delta = 4096;
	if (msgq_last <= msgq_size) {
		if (xrealloc_safe(&msgq, sizeof(*msgq) * (msgq_size + delta)))
			return -ENOMEM;
		msgq_size += delta;
	}

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
			values[j + 2] = (void *)&msgq[i]->args[j].val;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, msgq[i]->nargs + 2,
				 &ffi_type_sint, args) == FFI_OK)
			ffi_call(&cif, FFI_FN(dprintf), &rc, values);
	}
}

void flog_encode_msg(size_t nargs, const char *format, ...)
{
	va_list argptr;
	flog_msg_t *m;

	printf("nargs %d\n", nargs);

	m = malloc(sizeof(*m) + sizeof(m->args[0]) * nargs);
	if (m) {
		unsigned long v;
		size_t i;

		va_start(argptr, format);
		m->type = FLOG_MSG_TYPE_REGULAR;
		m->fmt = format;
		m->nargs = nargs;
#if 1
		for (i = 0; i < nargs; i++)
			m->args[i].type = va_arg(argptr, unsigned int);
		for (i = 0; i < nargs; i++) {
			switch (m->args[i].type) {
#if 0
			case 1 ... 7:
				m->args[i].val = va_arg(argptr, int);
				break;
			case 8 ... 9:
				m->args[i].val = va_arg(argptr, long);
				break;
			case 10 ... 11:
				m->args[i].val = va_arg(argptr, long long);
				break;
			/* char pointers are treated as strings! */
			case 18 ... 26:
			case 30 ... 38:
				m->args[i].val = (long)va_arg(argptr, void *);
				break;
#endif
			case 15 ... 17:
			case 27 ... 29:
				//m->args[i].val = (long)(void *)strdup(va_arg(argptr, char *));
				m->args[i].val = va_arg(argptr, long);
				break;
			default:
				m->args[i].val = va_arg(argptr, long);
				break;
			}
		}
		va_end(argptr);
#endif
		flog_enqueue(m);
	}
}
