#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    // Open input file
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    // Set up a buffer array, JPEG counter, and new file name/pointer
    BYTE buffer[512];
    int num_jpegs = 0;
    char filename[10] = {0};
    FILE *img = NULL;

    while (fread(buffer, 512, 1, raw) == 1)
    {
        if (num_jpegs > 0)
        {
            // Close current image file...
            fclose(img);
            // ...because you found another JPEG!
            //num_jpegs++;
        }

        // Name the new JPEG file in sequential order
        sprintf(filename, "%03i.jpg", num_jpegs);
        // Open a new file with that name to write
        img = fopen(filename, "w");
        // Write buffer to the new file
        fwrite(buffer, 512, 1, img);
        // If the block is NOT the start of a new JPEG and at least 1 JPEG has already been found
        num_jpegs++;
    }
    fclose(img);
    fclose(raw);
    return 0;
}
