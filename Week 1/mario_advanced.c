#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i, j, n, row;
    row = get_int("Heigh: ");
    if (row <= 8 && row >= 1) // 1
    {
        for (i = 1; i <= row; i++)
        {                                 // 2
            for (j = 0; j < row - i; j++) // 3
            {
                printf(" "); // 4
            }
            for (j = 0; j < i; j++) // 5
            {
                printf("#");
            }
            printf(" ");
            for (j = 0; j < i; j++) // 6
            {
                printf("#");
            }
            printf("\n"); // 7
        }
    }
    else
    {
        main();
    }
}