#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        //prompts user for plaintext
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        int k = atoi(argv[1]) % 26;
    }
}