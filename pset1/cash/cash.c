#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float n;

//n is a positive float
    do
    {
        n = get_float("change owed: ");
    }
    while (0 > n);

//gets number of cents
    int change = round(n * 100);
    int coins = 0;

//determines number of quarters
    while (change >= 25)
    {
        coins++;
        change -= 25;
    }

//determines number of dimes
    while (change >= 10)
    {
        coins++;
        change -= 10;
    }

//determines number of nickels
    while (change >= 5)
    {
        coins++;
        change -= 5;
    }

//determines number of pennies
    while (change >= 1)
    {
        coins++;
        change -= 1;
    }
    printf("%i", coins);
    printf("\n");
}