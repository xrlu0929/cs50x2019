// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
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
        printf("Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
//             if (triple.rgbtRed == 0xff || triple.rgbtRed == 0xee || triple.rgbtRed == 0xcc || triple.rgbtRed == 0xdd || triple.rgbtRed == 0xaa || triple.rgbtRed == 0xbb || triple.rgbtRed == 0x99 || triple.rgbtRed == 0x88 || triple.rgbtRed == 0x77 || triple.rgbtRed == 0x66 || triple.rgbtRed == 0x55 || triple.rgbtRed == 0x44 || triple.rgbtRed == 0x33 || triple.rgbtRed == 0x22 || triple.rgbtRed == 0x11)
//             {
//                 triple.rgbtRed = 0xff;
//             }
//             if (triple.rgbtBlue == 0x00 || triple.rgbtBlue == 0x11 || triple.rgbtBlue == 0x22 || triple.rgbtBlue == 0x33 || triple.rgbtBlue == 0x44 || triple.rgbtBlue == 0x55 || triple.rgbtBlue == 0x66 || triple.rgbtBlue == 0x77 || triple.rgbtBlue == 0x88 || triple.rgbtBlue == 0x99 ||triple.rgbtBlue == 0xaa || triple.rgbtBlue == 0xbb || triple.rgbtBlue == 0xcc || triple.rgbtBlue == 0xdd || triple.rgbtBlue == 0xee)
//             {
                triple.rgbtBlue = 0x00;
//             }
//             if (triple.rgbtGreen == 0xff)
//             {
                triple.rgbtGreen = 0x00;
//             }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
