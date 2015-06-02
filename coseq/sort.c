#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"

int main(int argc, char** argv)
{
	char* inlet = argv[1];
        char* outlet = argv[2];
        sort_on_RAM(inlet, outlet);
	return 0;
}
