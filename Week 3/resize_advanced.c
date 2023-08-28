#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }
    // Get resize factor and validate it
    float resizeFactor = atof(argv[1]);
    if (resizeFactor <= 0 || resizeFactor > 100)
    {
        printf("Resize factor must be between 0 and 100\n");
        return 5;
    }
    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // Open input file
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // Open output file
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    // Read infile's headers
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // Update headers for resized image
    BITMAPFILEHEADER bfR = bf;
    BITMAPINFOHEADER biR = bi;
    biR.biWidth *= resizeFactor;
    biR.biHeight *= resizeFactor;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (biR.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    biR.biSizeImage = ((biR.biWidth * sizeof(RGBTRIPLE)) + outPadding) * abs(biR.biHeight);
    bfR.bfSize = biR.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // Write outfile's headers
    fwrite(&bfR, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&biR, sizeof(BITMAPINFOHEADER), 1, outptr);
    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Create a buffer to hold a scanline of pixels
        RGBTRIPLE *scanline = malloc(sizeof(RGBTRIPLE) * biR.biWidth);
        int scanlineIndex = 0;
        // Iterate vertically for resize
        for (int j = 0; j < resizeFactor; j++)
        {
            // Iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // Write RGB triple to scanline buffer 'resizeFactor' times
                for (int l = 0; l < resizeFactor; l++)
                {
                    scanline[scanlineIndex] = triple;
                    scanlineIndex++;
                }
            }
        }
        // Write the scanline buffer to outfile
        for (int j = 0; j < biR.biWidth; j++)
        {
            fwrite(&scanline[j], sizeof(RGBTRIPLE), 1, outptr);
        }
        // Add padding to outfile
        for (int m = 0; m < outPadding; m++)
        {
            fputc(0x00, outptr);
        }
        // Free the scanline buffer
        free(scanline);
        // Skip over padding in input file
        fseek(inptr, padding, SEEK_CUR);
    }
    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}
