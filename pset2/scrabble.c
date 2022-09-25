// https://cs50.harvard.edu/x/2022/labs/2/
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void convert_to_lower(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Convert input words to lowercase
    convert_to_lower(word1);
    convert_to_lower(word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

void convert_to_lower(string word)
{
    for(int i = 0; word[i] != 0; i++)
    {
        word[i] = tolower(word[i]);
    }
}

int compute_score(string word)
{
    // Compute and return score for string
    int sum = 0;
    for(int i = 0; word[i] != 0; i++)
    {
        // Find ASCII Value for each element in char array of word
        int ASCII_val = word[i];
        // If var represents ASCII value between `a` and `z`
        if (ASCII_val >= 97 && ASCII_val <= 122)
        {
            // Subtract 97 to find POINTS array index value (so a = 0, b = 1, etc.)
            int POINTS_index = ASCII_val - 97;
            // Query POINTS array using letter's index value to find Scrabble point value
            sum += POINTS[POINTS_index];
        }
    }
    return sum;
}
