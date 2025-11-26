#include <stdio.h>
#include <stdint.h>

int main()
{

    uint64_t i;
    i = 0;

    while (1)
    {
        printf("%llu\n", i);
        i++;
    }

    return 0;
}