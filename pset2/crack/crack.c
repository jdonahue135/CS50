#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>

#define _XOPEN_SOURCE

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        //verifies correct number of arguments
        printf("Usage: ./crack hash\n");
        return 1;
    }

    //makes sure hash is no longer than 5 chars
    int hash_length = strlen(argv[1]);
    if (hash_length > 5)
    {
        printf("hash is too long\n");
        return 1;
    }

}
