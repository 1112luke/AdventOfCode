#include <stdio.h>
#include <stdint.h>

uint8_t swap(uint32_t *arr, uint16_t idx1, uint16_t idx2)
{

    uint32_t tmp;

    tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;

    return 0;
}

uint8_t sort_ascending(uint32_t *arr, uint16_t size)
{

    for (int i = size - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr, j, j + 1);
            }
        }
    }

    return 0;
}

uint32_t totaldiff(uint32_t *arr1, uint32_t *arr2, uint16_t size)
{

    // sort
    sort_ascending(arr1, size);
    sort_ascending(arr2, size);

    // compare and add to total difference
    uint32_t total = 0;

    for (int i = 0; i < size; i++)
    {
        total += ((arr1[i] > arr2[i]) ? arr1[i] - arr2[i] : arr2[i] - arr1[i]);
    }

    return total;
}

uint32_t similarity(uint32_t *l1, uint32_t *l2, uint16_t size)
{

    uint32_t total = 0;

    uint32_t seen[BUFSIZ];
    uint16_t seensize = 0;

    uint8_t skip = 0;

    uint8_t matches = 0;

    // walk l1
    for (int i = 0; i < size; i++)
    {
        skip = 0;
        // check if in seen
        for (int j = 0; j < seensize; j++)
        {
            if (seen[j] == l1[i])
            {
                skip = 1;
                break;
            }
        }
        if (skip)
        {
            break;
        }

        // not seen before, count matches in right list
        seen[seensize] = l1[i];
        seensize++;
        matches = 0;

        for (int j = 0; j < size; j++)
        {
            if (l1[i] == l2[j])
            {
                matches++;
            }
        }

        // add to total
        total += l1[i] * matches;
    }

    return total;
}

uint16_t printarr(uint32_t *arr, uint16_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}

int main()
{

    uint32_t l1[BUFSIZ];
    uint32_t l2[BUFSIZ];

    uint16_t lsize = 0;

    int i1;
    int i2;

    FILE *fp = fopen("input.txt", "r");

    while (fscanf(fp, "%d %d\n", &i1, &i2) >= 0)
    {
        // printf("I1: %d, I2: %d\n", i1, i2);

        l1[lsize] = i1;
        l2[lsize] = i2;

        lsize++;
    };

    uint32_t totaldifference = totaldiff(l1, l2, lsize);

    uint32_t totalsim = similarity(l1, l2, lsize);

    // print
    // printarr(l1, lsize);
    // printarr(l2, lsize);
    printf("%d\n", totalsim);

    fclose(fp);

    return 0;
}
