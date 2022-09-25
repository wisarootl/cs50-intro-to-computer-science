#include "helpers.h"
#include <math.h>

int cap(int color, int upperbound);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    float averageColors;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            averageColors = round((originalRed +
                                   originalGreen +
                                   originalBlue) /
                                  3.0);

            image[i][j].rgbtRed = averageColors;
            image[i][j].rgbtGreen = averageColors;
            image[i][j].rgbtBlue = averageColors;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    int originalRed, originalGreen, originalBlue;
    int sephiaRed, sephiaGreen, sephiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            sephiaRed = round(.393 * originalRed +
                              .769 * originalGreen +
                              .189 * originalBlue);

            sephiaGreen = round(.349 * originalRed +
                                .686 * originalGreen +
                                .168 * originalBlue);

            sephiaBlue = round(.272 * originalRed +
                               .534 * originalGreen +
                               .131 * originalBlue);

            sephiaRed = cap(sephiaRed, 255);
            sephiaGreen = cap(sephiaGreen, 255);
            sephiaBlue = cap(sephiaBlue, 255);

            image[i][j].rgbtRed = sephiaRed;
            image[i][j].rgbtGreen = sephiaGreen;
            image[i][j].rgbtBlue = sephiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp_image[h][w] = image[h][w];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // is valid row?
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // is valid columns?
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    sumRed += temp_image[i + k][j + l].rgbtRed;
                    sumGreen += temp_image[i + k][j + l].rgbtGreen;
                    sumBlue += temp_image[i + k][j + l].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int)round(sumRed / count);
            image[i][j].rgbtGreen = (int)round(sumGreen / count);
            image[i][j].rgbtBlue = (int)round(sumBlue / count);
        }
    }
    return;
}

int cap(int color, int upperbound)
{
    if (color > upperbound)
    {
        return 255;
    }
    else
    {
        return color;
    }
}