// Spec: https://cs50.harvard.edu/x/2022/psets/1/mario/more/
#include <cs50.h>
#include <stdio.h>

// Declare variables
int height;
int min = 1;
int max = 8;

// Declare functions
int get_height(void);
void build_pyramid(int height1);

int main(void)
{
    // Run get_height function to ask for `height` parameter
    get_height();
    // If `height` is out of bounds, repeat get_height function
    while (height > max || height < min)
    {
        printf("Whoops! Try any number from 1 through 8.\n");
        get_height();
    }
    // if `height` is within bounds, run build_pyramid function
    build_pyramid(height);

}

int get_height(void)
{
    height = get_int("Height = ");
    return height;
}

void build_pyramid(int height1)
{
    int i; // #s for row
    int j; // #s for column
    int k; // spacing before each row
    int l; // # for rows AFTER space
    for (i = 1; i <= height1; i++)
    {
        // must invert `k` to add height1-i spaces before #
        for (k = height1 - i; k >= 1; k--)
        {
            printf(" ");
        }
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        // Add space between both sets of #s
        printf("  ");
        for (l = 1; l <= i; l++)
        {
            printf("#");
        }
        // Break line after each loop to start next set of #
        printf("\n");
    }
}
