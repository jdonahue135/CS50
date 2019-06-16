#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    char buffer[50];

    int course = 50;
//%d is a placeholder for a decimal value
    sprintf(buffer,"CS%d rocks!", course);

    printf("%s\n", buffer);
}