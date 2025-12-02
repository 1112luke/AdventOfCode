#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    int8_t dir;
    uint16_t amount;
} Combo;

Combo combos[5000];

uint32_t idx = 0;

// app variables
int16_t place = 50;

int main()
{

    // parse combos
    FILE *fp = fopen("inputtest.txt", "r");

    // read lines
    char buffer[BUFSIZ];
    while (fgets(buffer, sizeof(buffer), fp))
    {

        int8_t direction = 0;

        char *b = &buffer[0];

        switch (*b)
        {
        case 'L':
            direction = -1;
            break;
        case 'R':
            direction = 1;
            break;
        }

        b++;

        combos[idx].amount = (uint16_t)atoi(b);
        combos[idx].dir = direction;

        idx++;
    }

    // run through entire list and count number of zeros
    uint16_t zeros = 0;
    uint8_t old = 50;
    for (int i = 0; i < idx; i++)
    {

        place += combos[i].dir * combos[i].amount;

        // check for wraps
        if (place > 99)
        {
            zeros += place / 100;
        }

        if (place < 0)
        {
            zeros += ((place - 1) / 100) + 1;
        }

        place = (place % 100 + 100) % 100;

        if (place == 0)
        {
            zeros++;
        }

        old = place;
    }
    printf("%d\n", zeros);

    fclose(fp);

    return 0;
}