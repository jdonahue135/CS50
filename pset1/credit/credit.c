#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

//program that validates credit card number and outputs type of card
int main(void)
{
    //gets credit card number from user
    long long number = get_long_long("Number: ");
    char *card_type = malloc(sizeof(char[11]));

    //valid card number?
    long long tmp = number;
    long long sum = 0;
    while (tmp != 0)
    {
        //parses card number into individual digits and uses algorithm invented by Hans Peter Luhn
        int l = tmp % 10;
        tmp = tmp / 10;
        int m = (tmp % 10) * 2;
        if (m > 9)
        {
            m = (m % 10) + 1;
        }
        tmp = tmp / 10;
        sum = sum + m + l;
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //verifies type of card
    if ((number >= 340000000000000 && number < 350000000000000) || (number >= 370000000000000 && number < 380000000000000))
    {
        strcpy(card_type, "AMEX");
    }
    else if (number >= 5100000000000000 && number < 5600000000000000)
    {
        strcpy(card_type, "MASTERCARD");
    }
    else if ((number >= 4000000000000 && number <= 5000000000000) || (number >= 4000000000000000 && number <= 5000000000000000))
    {
        strcpy(card_type, "VISA");
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
    printf("%s\n", card_type);
    free(card_type);
    return 0;
}