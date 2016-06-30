#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "flog.h"

extern void stack_scan(const char *format, ...);

extern char _rodata_start, _rodata_end;
char *rodata_start = &_rodata_start;
char *rodata_end = &_rodata_end;

int main(int argc, char *argv[])
{
	static const char str1[] = "String1";
	static const char str2[] = "string2";
	const size_t niter = 100000;
	size_t i;

	if (argc > 1 && atoi(argv[1]) == 1) {
		for (i = 0; i < niter; i++)
			printf("Some message %s %s %c %li %d %lu\n",
			       str1, str2,
			       'c', (long)-4, (short)2,
			       (unsigned long)2);
	} else {
		for (i = 0; i < niter; i++)
			flog_encode("Some message %s %s %c %li %d %lu\n",
				    str1, str2,
				    'c', (long)-4, (short)2,
				    (unsigned long)2);

		if (argc > 1 && atoi(argv[1]) == 2)
			flog_decode_all(fileno(stdout));
	}
	return 0;
}
