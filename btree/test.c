#include <stdlib.h>
#include <stdio.h>

int f()
{
    static int n = -1;
    n++;
    return n;
}

int main()
{
    int i = 0;

    for (i = 0; i < 10; ++i)
        printf("%d\n", f());

    return 0;
}
