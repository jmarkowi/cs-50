#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void box_blur(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE blurred[height][width]);
void sobel(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE edged[height][width]);
int new_value(int x, int y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over each element in the row
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the RBG values in each pixel
            avg = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);
            // Set each pixel to average value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the two RGBTRIPLEs (pixels)
            temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for temporary copy of image
    RGBTRIPLE(*blurred)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (blurred == NULL)
    {
        fprintf(stderr, "Not enough memory to blur image.\n");
        return;
    }

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            // Blur each pixel using box blur method
            box_blur(i, j, height, width, image, blurred);
        }
    }

    // Copy contents of blurred into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }

    // Free memory for blurred
    free(blurred);
    return;
}

// Detect edges using Sobel operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for temporary copy of image
    RGBTRIPLE(*edged)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (edged == NULL)
    {
        fprintf(stderr, "Not enough memory to blur image.\n");
        return;
    }

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            // Detect edges using Sobel operator
            sobel(i, j, height, width, image, edged);
        }
    }

    // Copy contents of edged into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edged[i][j];
        }
    }

    // Free memory for blurred
    free(edged);
    return;
}


// ~~ HELPER FUNCTIONS ~~ //

// Find box blur values of a RGBTRIPLE (pixel)
void box_blur(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE blurred[height][width])
{
    int r_avg = 0, g_avg = 0, b_avg = 0, pixels = 0;
    // Collect the RGB values of the surrounding pixels
    // From 1 row above through 1 row below
    for (int i = x - 1; i <= x + 1; i++)
    {
        // Prevent from trying to read above or below image boundaries
        if (i >= 0 && i < height)
        {
            // From 1 column left through 1 column right
            for (int j = y - 1; j <= y + 1; j++)
            {
                // Prevent from trying to read left or right of image boundaries
                if (j >= 0 && j < width)
                {
                    r_avg += image[i][j].rgbtRed;
                    g_avg += image[i][j].rgbtGreen;
                    b_avg += image[i][j].rgbtBlue;
                    // Count number of pixels averaged (usually 9, but not for edges or corners)
                    pixels++;
                }
            }
        }
    }

    // Calculate the averages
    r_avg = round((float) r_avg / pixels);
    g_avg = round((float) g_avg / pixels);
    b_avg = round((float) b_avg / pixels);

    // Assign the new values to the original pixel in blurred[][]
    blurred[x][y].rgbtRed = r_avg;
    blurred[x][y].rgbtGreen = g_avg;
    blurred[x][y].rgbtBlue = b_avg;

    return;
}

// Apply Sobel operator to RGBTRIPLE (pixel)
void sobel(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE edged[height][width])
{
    // Initialize x and y kernels
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int r_gx = 0, r_gy = 0, g_gx = 0, g_gy = 0, b_gx = 0, b_gy = 0;

    // Calculate total gx and gy channel values
    // From 1 row above through 1 row below
    for (int i = x - 1, k = 0; i <= x + 1; i++, k++)
    {
        // Prevent from trying to read above or below image boundaries
        if (i >= 0 && i < height)
        {
            // From 1 column left through 1 column right
            for (int j = y - 1, l = 0; j <= y + 1; j++, l++)
            {
                // Prevent from trying to read left or right of image boundaries
                if (j >= 0 && j < width)
                {
                    // Red channel values
                    r_gx += image[i][j].rgbtRed * gx[k][l];
                    r_gy += image[i][j].rgbtRed * gy[k][l];
                    // Green channel values
                    g_gx += image[i][j].rgbtGreen * gx[k][l];
                    g_gy += image[i][j].rgbtGreen * gy[k][l];
                    // Blue channel values
                    b_gx += image[i][j].rgbtBlue * gx[k][l];
                    b_gy += image[i][j].rgbtBlue * gy[k][l];
                }
            }
        }
    }

    // Assign new values to original pixel in edged[][]
    edged[x][y].rgbtRed = new_value(r_gx, r_gy);
    edged[x][y].rgbtGreen = new_value(g_gx, g_gy);
    edged[x][y].rgbtBlue = new_value(b_gx, b_gy);
    return;
}

// Calculate new edge value using sqrt(gx^2 + gy^2)
int new_value(int x, int y)
{
    // Cast as floats, then round to int
    int n = round(sqrt(pow((float) x, 2) + pow((float) y, 2)));
    // Value cannot exceed max possible channel value (255)
    if (n > 255)
    {
        return 255;
    }
    else
    {
        return n;
    }
}