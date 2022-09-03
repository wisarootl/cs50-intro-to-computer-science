#include <cs50.h>
#include <stdio.h>

void printf_repeat(char c, int times)
{
    while (--times >= 0)
    {
        printf("%c", c);
    }
}


int main(void)
{
    int height, width;
    char block = '#';
    char space = ' ';

    do
    {
        height = get_int("Height: ");
        width = height;
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        int num_blocks = i;
        int num_spaces = width - num_blocks;

        // left blocks
        printf_repeat(space, num_spaces);
        printf_repeat(block, num_blocks);

        printf("  ");

        // right bloacks
        printf_repeat(block, num_blocks);

        printf("\n");
    }

}