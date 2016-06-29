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
	size_t i;

	printf("str1 %p str2 %p rodata_start %p rodata_end %p\n",
	       str1, str2, rodata_start, rodata_end);

	if (argc > 1 && argv[1]) {
		for (i = 0; i < 100000; i++)
			printf("Some message %s %s %c %li %d %lu\n",
			       str1, str2,
			       'c', (long)-4, (short)2,
			       (unsigned long)2);
	} else {
		for (i = 0; i < 1; i++)
			flog_encode("Some message %s %s %c %li %d %lu\n",
				    str1, str2,
				    'c', (long)-4, (short)2,
				    (unsigned long)2);
//		flog_decode_all(fileno(stdout));
	}
	return 0;
}
