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

#define BLOCK_SIZE 512

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename \n");
        return 1;
    }

    // remember filename
    char* in_file = argv[1];

    // open memory card file
    FILE* inptr = fopen(in_file, "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        printf("Could not open %s.\n", in_file);
        return 2;
    }

    // jpeg file  starts with either:
    // 0xff 0xd8 0xff 0xe0
    // 0xff 0xd8 0xff 0xe1
    uint8_t jpg_start[3] = { 0xff, 0xd8, 0xff }; // all jpg must start with these 3 bytes
    uint8_t jpg_end[2] = { 0xe0, 0xe1 }; // jpg 4th byte can be either one of these bytes

    // initialze char for output file name
    char out_file[8];

    // declare outfile pointer for use of writing all jpg files
    FILE* outptr = NULL;

    uint8_t buffer[BLOCK_SIZE];  // used to hold 512 bytes that represent unsigned integer

    // keep track of the file num we are writing to.
    int file_num = 0;

    // flag to determine once we have hit the jpg files
    bool is_jpg = false;

    // Read until we read first jpg
    while( !is_jpg )
    {
        // Read in 512 bytes
        fread(&buffer, BLOCK_SIZE, 1 , inptr);

        // Check if it is a jpg
        if (
                // First 3 bytes are always the same
                buffer[0] == jpg_start[0] &&
                buffer[1] == jpg_start[1] &&
                buffer[2] == jpg_start[2] &&
                ( (buffer[3] == jpg_end[0]) || (buffer[3] == jpg_end[1]) ) // jpg can be either of these bytes at 3rd index

           )
        {
            is_jpg = true;
        }

    }

    /* Read until end of file, rest of file will be jpg files in a row
     * 
     *  Check to see if the block read in is a jpg, if so close old file and then
     *  start writing new file.
     * 
     *  copy each 512 byte block of memory to the output .jpg file we are currently using.
     */
    while( !feof(inptr) )
    {
        // Check if we have read in a jpg, if so close old file and open up new file.
        if (
                // First 3 bytes are always the same
                buffer[0] == jpg_start[0] &&
                buffer[1] == jpg_start[1] &&
                buffer[2] == jpg_start[2] &&
                ( (buffer[3] == jpg_end[0]) || (buffer[3] == jpg_end[1]) ) // jpg can be eithr of these bytes at 3rd index

           )
        {
            // close previous file. If file_num is zero, there is no previous file
            // to be closed.
            if (!(file_num == 0))
            {
                fclose(outptr);
            }
            
            // set file name
            sprintf(out_file, "%03d.jpg", file_num);

            // open up a new file
            outptr = fopen(out_file, "a"); // keep appending data to new file

            // increment file number
            file_num++;
        }

        // Write block to outptr file
        fwrite(&buffer, BLOCK_SIZE, 1, outptr); 
        
        // read in next block of memory from input file
        fread(&buffer, BLOCK_SIZE, 1 , inptr);
    }
}
