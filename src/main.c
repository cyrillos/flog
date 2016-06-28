#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "flog.h"

int main(int argc, char *argv[])
{
	size_t i;

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
