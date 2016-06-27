#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "flog.h"

#define typename(x)			\
	_Generic((x),			\
	size_t:		"size_t",	\
	long:		"long",		\
	int:		"int",		\
	float:		"float",	\
	char:		"char",		\
	char *:		"char *",	\
	const char *:	"const char *",	\
	default:	"other")

int main(int argc, char *argv[])
{
	size_t i;
	const char *s;

#define PR_ARG(x)	printf("type %d\n", flog_typecode(x))

	FLOG_FOR_EACH(PR_ARG, i, s);
	exit(0);

	if (argc > 1 && argv[1]) {
		for (i = 0; i < 100000; i++)
			printf("Some message %s %s %c %li %d %lu\n",
			       "String1", "string2",
			       'c', (long)-4,
			       (short)2,
			       (unsigned long)2);
	} else {
		for (i = 0; i < 10; i++)
			flog_encode("Some message %s %s %c %li %d %lu\n",
				    "String1", "string2",
				    'c', (long)-4, (short)2,
				    (unsigned long)2);
		flog_decode_all(fileno(stdout));
	}
	return 0;
}
