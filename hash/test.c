#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int number;
    int (*func)(int,int);
} noodle;

int add(int a, int b)
{ return a + b; }

int main()
{
    noodle bacon;
    int i = 0;

    bacon.number = 0;
    bacon.func = add;

    for (i = 0; i < 10; ++i)
    {
        bacon.number = bacon.func(i, bacon.number);
        printf("%d: %d\n", i, bacon.number);
    }

    return 0;
}
