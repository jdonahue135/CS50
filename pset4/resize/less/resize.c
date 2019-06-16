// Copies a BMP file
//Suceeded in making file larger, but need to fix errors with padding

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy resize infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n > 101 || n < 1)
    {
        fprintf(stderr, "Usage: resize must be positive interger less than 101\n");
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    // determine padding for infile's scanlines
    int Ipadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //changes width and height of image in header
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for outfile's scanlines
    int Opadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Changes bi.Bisizeimage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(bi.biWidth)) + Opadding) * abs(bi.biHeight);

    //Changes bfSize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    int biWidth = abs(bi.biWidth);
    int biHeight = abs(bi.biHeight);
    for(int row = 0; row < biHeight/n; row++)
    {
       for (int line = 0; line < n - 1; line++)
       {
            // iterate over pixels in scanline
            for (int pixel = 0; pixel < biWidth/n; pixel++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //write outfile's padding
            for (int m = 0; m < Opadding; m++)
            {
                fputc(0x00, outptr);
            }
            //move infile cursor back
            fseek(inptr, 54 + (row*3*biWidth/n) + (row*Ipadding), SEEK_SET);

       }
       // iterate over pixels in scanline
        for (int j = 0; j < biWidth/n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile n times
            for (int l = 0; l < n; l++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        //write outfile's padding
        for (int k = 0; k < Opadding; k++)
        {
            fputc(0x00, outptr);
        }
        //skip over infile padding
        fseek(inptr, Ipadding, SEEK_CUR);
    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
