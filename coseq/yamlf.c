#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"
#include "yaml.h"

int main(int argc, char** argv)
{
	/* printf("%d\n", argc); */
	pipe_to_yaml(argv[1]);
	return 0;
}
