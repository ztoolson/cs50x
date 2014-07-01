/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename \n");
        return 1;
    }

    // remember filename
    char* infile = argv[1];

    // open memory card file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // find beginning of jpg
    // jpeg file  starts with either:
    // 0xff 0xd8 0xff 0xe0
    // 0xff 0xd8 0xff 0xe1
    uint8_t jpg_start[3] = { 0xff, 0xd8, 0xff }; // all jpg must start with these 3 bytes
    uint8_t jpg_end[2] = { 0xe0, 0xe1 }; // jpg 4th byte can be either one of these bytes

    int size = 512;
    bool is_jpg = false;

    // initialize to all zero's
    uint8_t buffer[size];  // used to hold 512 bytes that represent unsigned integer

    int file_num = 0;
    // Read until we read first jpg
    while( !is_jpg )
    {
        // Read in 512 bytes
        fread(&buffer, size, 1 , inptr);

        // Check if it is a jpg
        if (
                // First 3 bytes are always the same
                buffer[0] == jpg_start[0] &&
                buffer[1] == jpg_start[1] &&
                buffer[2] == jpg_start[2] &&
                ( (buffer[3] == jpg_end[0]) || (buffer[3] == jpg_end[1]) ) // jpg can be either of these bytes at 3rd index

           )
        {
            file_num++;
            is_jpg = true;
        }

    }

    
    // Read until end of file, rest of file will be jpg files in a row.
    while( !feof(inptr) )
    {
        fread(&buffer, size, 1 , inptr);
        // Check if we have read in a jpg
        if (
                // First 3 bytes are always the same
                buffer[0] == jpg_start[0] &&
                buffer[1] == jpg_start[1] &&
                buffer[2] == jpg_start[2] &&
                ( (buffer[3] == jpg_end[0]) || (buffer[3] == jpg_end[1]) ) // jpg can be eithr of these bytes at 3rd index

           )
        {
            file_num++;
            is_jpg = true;
        }
    }

    printf("END: Number of Files is %i\n", file_num);

    // open a new jpg file to output bytes to

    // keep writing 512 bytes until a new jpg is found

    // detect end of file
}
