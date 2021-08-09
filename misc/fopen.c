#include <stdio.h>
#include <stdlib.h>

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
    // Set up a buffer array
    //unsigned char *buffer = malloc(512);
    //int num_jpegs = 2;

    // Read the first 512 bytes into the buffer
    //fread(buffer, 512, 1, raw);

    //char filename[10];
    //sprintf(filename, "%03i.jpg", num_jpegs);
    //FILE *temp = fopen(filename, "w");
    //fwrite(buffer, 512, 1, temp);

    printf("The contents of %s file are:\n", argv[1]);
    char ch;
    while((ch = fgetc(raw)) != EOF)
        printf("%c", ch);
    printf("\n");
    fclose(raw);
    //fclose(temp);
    //free(buffer);
    return 0;
}