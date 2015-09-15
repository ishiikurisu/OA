#include <oa.h>
#include "lempelziv.h"

int main(int argc, char *argv[]) {
    char *input = argv[1];
    char *output = argv[2];

    unLZ78(input, output);

    return 0;
}
