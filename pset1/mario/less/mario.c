#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //makes sure user enters number between 0 and 23//

    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (0 > n || n > 23);

    //creates pyramid//

    for (int r = 0; r < n; r++)
    {
        for (int s = 0; s < n - 1 - r; s++)
        {
            printf(" ");
        }
        for (int b = 0; b < r + 2; b++)
        {
            printf("#");
        }

        printf("  ");

        for (int b = 0; b < r + 2; b++)
        {
            printf("#");
        }
        for (int s = 0; s < n - 1 - r; s++)
        {
            printf(" ");
        }
        printf("\n");
    }
}