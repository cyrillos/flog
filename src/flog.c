#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

void flog_decode_msg(int fdout, const char *format, ...)
{
	va_list argptr;

	va_start(argptr, format);
	vdprintf(fdout, format, argptr);
	va_end(argptr);
}

void flog_decode_all(int fdout)
{
	size_t i;

	for (i = 0; i < msgq_last; i++)
		flog_decode_msg(fdout, msgq[i]->fmt,
				msgq[i]->args[0],
				msgq[i]->args[1],
				msgq[i]->args[2],
				msgq[i]->args[3],
				msgq[i]->args[4],
				msgq[i]->args[5]);
}

void flog_encode_msg(size_t nargs, const char *format, ...)
{
	va_list argptr;
	flog_msg_t *m;

	m = xmalloc(sizeof(*m) + sizeof(m->args[1]) * nargs);
	if (m) {
		unsigned long v;
		size_t i;

		va_start(argptr, format);
		m->type = FLOG_MSG_TYPE_REGULAR;
		m->fmt = format;

		for (i = 0; i < nargs; i++)
			m->args[i] = va_arg(argptr, unsigned long);
		va_end(argptr);
		flog_enqueue(m);
	}
}
