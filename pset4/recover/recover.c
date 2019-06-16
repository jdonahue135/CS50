//Recovers jpegs from a forensic image

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *error_file = argv[1];
    unsigned char buffer[512] = {0};
    char jpgName[8] = {0};
    int jpgcounter = 0;
    FILE* outptr = NULL;

    //open memory card file
    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", error_file);
        return 2;
    }

    //Repeat until end of card
    //determine if buffer is start of a new jpeg
    while (fread(buffer, sizeof(buffer), 1, inptr) == 1)
    {
        //find beginning of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if(NULL!=outptr)
            {
              fclose(outptr);
              outptr=NULL;
            }
            //Create filename for jpegs
            sprintf(jpgName, "%03d.jpg", jpgcounter);
            outptr = fopen(jpgName, "w");
            //write 512 bytes until new jpeg is found
            fwrite(buffer, sizeof(buffer), 1, outptr);
            jpgcounter++;
        }
        else
        {
            if(NULL != outptr)
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }
    if(NULL!=outptr)
    fclose(outptr);
    if(NULL!=inptr)
    fclose(outptr);
    return 0;
}