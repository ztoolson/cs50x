/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and n value
    int n         = atoi(argv[1]);
    char* infile  = argv[2];
    char* outfile = argv[3];

    // check n value, must be in [1,100]
    if (n < 1 || n > 100)
    {
        printf("Please ensire the resize n is in [1, 100]\n");
        return 7;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER infile_bf;
    fread(&infile_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER infile_bi;
    fread(&infile_bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (infile_bf.bfType != 0x4d42 || infile_bf.bfOffBits != 54 || infile_bi.biSize != 40 || 
        infile_bi.biBitCount != 24 || infile_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Update output file header information for resize
    BITMAPFILEHEADER outfile_bf = infile_bf;
    BITMAPINFOHEADER outfile_bi = infile_bi;
    
    // Width and Height are increased by n
    outfile_bi.biWidth = infile_bi.biWidth * n;
    outfile_bi.biHeight = infile_bi.biHeight * n;

    // determine padding for scanlines
    int infile_padding  =  (4 - (infile_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outfile_padding =  (4 - (outfile_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate total file size and biSizeImage with padding
    // Formula found at: http://msdn.microsoft.com/en-us/library/dd947044(v=office.12).aspx
    outfile_bi.biSizeImage = ((outfile_bi.biWidth * outfile_bi.biBitCount + 31) & ~31) / 8 * outfile_bi.biHeight;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outfile_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outfile_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(infile_bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < infile_bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                // resize horizontally
                for (int x = 0; x < n; x++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < outfile_padding; k++)
            {
                fputc(0x00, outptr);
            }

            // return to beginning of next scanline
            if (j < n-1)
            {
                fseek(inptr, -infile_bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }

        }

        // skip over padding, if any in input file
        fseek(inptr, infile_padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
