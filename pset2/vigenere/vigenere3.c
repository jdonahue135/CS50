#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char c = get_char("letter: ");
    char d = get_char("letter: ");
    printf("%i", c + d);
}