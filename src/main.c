#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "flog.h"

extern void stack_scan(const char *format, ...);

int main(int argc, char *argv[])
{
	size_t i;

//	stack_scan("Format\n",
//		   (char)1, (short)2,
//		   (char)3, (short)4,
//		   (char)5, (short)6,
//		   (char)7, (short)8,
//		   (char)9, (short)10,
//		   (long)-1, (long)-2,
//		   0xdeadbeef, 0xdeadbeef);
//	exit(0);

//	flog_encode("Some message %s %lu\n",
//		    "String1", (unsigned long)2);
//	flog_decode_all(fileno(stdout));
//	exit(0);

	if (argc > 1 && argv[1]) {
		for (i = 0; i < 100000; i++)
			printf("Some message %s %s %c %li %d %lu\n",
			       "String1", "string2",
			       'c', (long)-4, (short)2,
			       (unsigned long)2);
	} else {
		for (i = 0; i < 100000; i++)
			flog_encode("Some message %s %s %c %li %d %lu\n",
				    "String1", "string2",
				    'c', (long)-4, (short)2,
				    (unsigned long)2);
//		flog_decode_all(fileno(stdout));
	}
	return 0;
}
