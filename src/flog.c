#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "flog.h"
#include "util.h"

void flog_encode(size_t nargs, const char *format, ...)
{
	flog_msg_t *m = xmalloc(sizeof(*m) + sizeof(m->args[1]) * nargs);

	if (m) {
		va_list argptr;
		unsigned long v;
		size_t i;

		va_start(argptr, format);
		m->fmt = format;
		m->type = 0;

		for (i = 0; i < nargs; i++)
			m->args[i] = va_arg(argptr, unsigned long);

		va_end(argptr);
	}
	printf("nargs -> %d, fmt %s\n", nargs, format);
}
