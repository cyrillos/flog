#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "flog.h"

#define typecode(x)			\
	_Generic((x),				\
		 /* Basic types */		\
		 char:			1,	\
		 signed char:		2,	\
		 unsigned char:		3,	\
		 signed short int:	4,	\
		 unsigned short int:	5,	\
		 signed int:		6,	\
		 unsigned int:		7,	\
		 signed long:		8,	\
		 unsigned long:		9,	\
		 signed long long:	10,	\
		 unsigned long long:	11,	\
		 float:			12,	\
		 double:		13,	\
		 long double:		14,	\
		 default:		15)

int main(int argc, char *argv[])
{
	size_t i;
	const char *s;
	int z;
	unsigned int d;

#define PR_ARG(x)	printf("type %d\n", flog_typecode(x))

	FLOG_FOR_EACH(PR_ARG, i, s, z, d);
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
