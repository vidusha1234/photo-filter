#include "helpers.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0.0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int orgred = 0;
    int orggreen = 0;
    int orgblue = 0;

    float red = 0;
    float green = 0;
    float blue = 0;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //need to save the original values
            orgred = image[i][j].rgbtRed;
            orggreen = image[i][j].rgbtGreen;
            orgblue = image[i][j].rgbtBlue;

            //sepia =
            blue = .272 * orgred + .534 * orggreen + .131 * orgblue;

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(blue);
            }

            green = .349 * orgred + .686 * orggreen + .168 * orgblue;

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(green);
            }

            red = .393 * orgred + .769 * orggreen + .189 * orgblue;

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(red);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy;
    copy.rgbtRed = 0;
    copy.rgbtBlue = 0;
    copy.rgbtGreen = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width) / 2; j++)
        {
            copy = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = copy;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of the image
    //Allocate memory for the copy of the image

    //RGBTRIPLE (*imagecopy)[height] = calloc(height, width * sizeof(RGBTRIPLE));
    //if (imagecopy == NULL)
    //{
    //printf("Not enough memory to store image.\n");
    //}
    RGBTRIPLE imagecopy[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            imagecopy[a][b] = image[a][b];
        }

    }

    float sum_red = 0.0;
    float sum_blue = 0.0;
    float sum_green = 0.0;
    int count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //pixcel is selected
            sum_red = 0;
            sum_blue = 0;
            sum_green = 0;
            count = 0;
            //lets go through the 9 squares
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k < 0 || k > height - 1 || l < 0 || l > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        sum_red = sum_red + imagecopy[k][l].rgbtRed;
                        sum_blue = sum_blue + imagecopy[k][l].rgbtBlue;
                        sum_green = sum_green + imagecopy[k][l].rgbtGreen;
                        count = count + 1;
                    }
                }
            }
            // now add calculate the avg
            image[i][j].rgbtRed = (int)round(sum_red / count);
            image[i][j].rgbtGreen = (int)round(sum_green / count);
            image[i][j].rgbtBlue = (int)round(sum_blue / count);
        }
    }
    //free(imagecopy);
    return;
}
