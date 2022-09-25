// https://cs50.harvard.edu/x/2022/psets/2/substitution/

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    int key_length = strlen(argv[1]);
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return (1);
    }
    // Check for duplicates or invalid keys
    for (int i = 0; i < key_length; i++)
    {
        // Check for invalid characters
        if (argv[1][i] < 65 || (argv[1][i] > 90 && argv[1][i] < 97) || argv[1][i] > 122)
        {
            printf("Key must only contain letters.\n");
            return (1);
        }
        // Check to see if character repeats. j = i + 1, otherwise j will check againts its own position and always return true
        for (int j = i + 1; j < key_length; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key may not repeat characters.\n");
                return (1);
            }
        }
    }

    // Create array for all chars in key as lowercase
    char lower_key[key_length];
    // Create array for all chars in key as uppercase
    char upper_key[key_length];
    for (int i = 0; i < key_length; i++)
    {
        // Recall that an array of string is a 2D array of chars
        lower_key[i] = tolower(argv[1][i]);
    }
    for (int i = 0; i < key_length; i++)
    {
        upper_key[i] = toupper(argv[1][i]);
    }

    string plaintext = get_string("Plaintext: ");
    int text_length = strlen(plaintext);
    char ciphertext[text_length + 1];

    // Map plaintext array elements to respective key
    for (int i = 0; i < text_length; i++)
    {
        // If lowercase, compare against lower_key
        if (islower(plaintext[i]))
        {
            int lower_index = plaintext[i] - 97;
            // Store to element i in ciphertext
            ciphertext[i] = lower_key[lower_index];
        }
        // If uppercase, compare against upper_key
        else if (isupper(plaintext[i]))
        {
            int upper_index = plaintext[i] - 65;
            ciphertext[i] = upper_key[upper_index];
        }
        // If neither, then not a letter
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    // Signify end of array with NUL
    ciphertext[text_length] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return (0);
}
