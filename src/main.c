#include <stdio.h>
#include <stdlib.h>

#include "flog.h"

int main(int argc, char *argv[])
{
	flog_printf("Some message %s %s\b", "String1", "string2");

	return 0;
}
