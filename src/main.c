#include <stdio.h>
#include <stdlib.h>

#include "flog.h"

int main(int argc, char *argv[])
{
	pr_debug("Some message %s\b", "String1");
	
	return 0;
}
