#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //displays error message if user does not provide a single command line argument
    if (argc == 2)
    {
        //makes sure keyword is an alpha and assigns key value starting at 0
        string k = argv[1];
        int n = strlen(k);
        for (int i = 0; i < n; i++)
        {
            if (isalpha(k[i]))
            {
                if (isupper(k[i]))
                {
                    k[i] -= 65;
                }
                if (islower(k[i]))
                {
                    k[i] -= 97;
                }
            }
            else
            {
                //prints error and returns value of 1 from main
                printf("Error\n");
                return 1;
            }
        }
        //prompts user for plaintext
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        //enciphers plaintext using key
        int y = strlen(p);
        for (int i = 0, j = 0; i < y; i++)
        {
            if (isalpha(p[i]))
            {
                if (isupper(p[i]))
                {
                    if (p[i] + (k[j % n]) > 90)
                    {
                        printf("%c", (p[i] + (k[j % n]) - 26));
                    }
                    else
                    {
                        printf("%c", p[i] + (k[j % n]));
                    }
                }
                if (islower(p[i]))
                {
                    if (p[i] + (k[j % n]) > 122)
                    {
                        printf("%c", p[i] + (k[j % n]) - 26);
                    }
                    else
                    {
                        printf("%c", p[i] + (k[j % n]));
                    }
                }
                j++;
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