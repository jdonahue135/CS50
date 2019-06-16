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
        // gets key if key is greater than 26
        int k = atoi(argv[1]) % 26;
        //encrypts alpha values
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (isalpha(p[i]))
            {
                if (isupper(p[i]))
                {
                    if (p[i] + k > 90)
                    {
                        printf("%c", (k + p[i] - 26));
                    }
                    else
                    {
                        printf("%c", (k + p[i]));
                    }
                }
                if (islower(p[i]))
                {
                    if (p[i] + k > 122)
                    {
                        printf("%c", (k + p[i] - 26));
                    }
                    else
                    {
                        printf("%c", (k + p[i]));
                    }
                }
            }
            //does not encypt non-alpha values
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n");
    }
    else
    {
        //prints error and returns value of 1 from main
        printf("Error\n");
        return 1;
    }
}

