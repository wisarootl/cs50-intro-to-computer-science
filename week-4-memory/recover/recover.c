#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    // Check number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int image_count = 0;
    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    FILE *img;

    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Chaeck is JPEG by first three bytes?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous image if existed.
            if (image_count)
            {
                fclose(img);
            }

            // Open the new image file
            sprintf(filename, "%03i.jpg", image_count++);
            img = fopen(filename, "w");
            fwrite(&buffer, 1, BLOCK_SIZE, img);
        }
        else
        {
            // Found
            if (image_count > 0)
            {
                fwrite(&buffer, 1, BLOCK_SIZE, img);
            }
        }
    }

    fclose(img);
    fclose(file);
}