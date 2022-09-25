// https://cs50.harvard.edu/x/2022/psets/2/readability/

#include <cs50.h>
#include <stdio.h>

// Function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_index(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = calculate_index(letters, words, sentences);

    // Print result
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Create function to count letters
int count_letters(string text)
{
    int letter_count = 0;
    // Loop through each element in array until it reaches end (NUL)
    for (int i = 0; text[i] != 0; i++)
    {
        // Check if element is between a-z or A-Z
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            // Increment letter count
            letter_count++;
        }
    }
    return letter_count;
}

// Create function to count words
int count_words(string text)
{
    // Initialize word count with at least 1 word
    int word_count = 1;
    // Loop through each element in array until it reaches end (NUL)
    for (int i = 0; text[i] != 0; i++)
    {
        // Check if element is a space (ASCII `sp` = 32)
        if (text[i] == 32)
        {
            word_count++;
        }
    }
    return word_count;
}

// Create function to count sentences
int count_sentences(string text)
{
    int sentence_count = 0;
    // Loop through each element in array until it reaches end (NUL)
    for (int i = 0; text[i] != 0; i++)
    {
        // Check if element is a ! OR . OR ? using ASCII values
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence_count++;
        }
    }
    return sentence_count;
}

// Calculate Coleman-Liau index
int calculate_index(int letters, int words, int sentences)
{
    // Typecast int letters into float
    float L = (float) letters / words * 100;
    // Typecast int sentences into float
    float S = (float) sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // Check if index has decimal value > 0.5
    if (index - (int) index > 0.5)
    {
        // Round up
        index++;
    }
    return index;
}
