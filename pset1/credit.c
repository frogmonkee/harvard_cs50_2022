// https://cs50.harvard.edu/x/2022/psets/1/credit/
#include <cs50.h>
#include <stdio.h>

// Define global variables
long length;

// Define functions
long check_length(long card_length); // Check card length
bool luhn(long card_luhn); // Pass through Luhn's Algo
string provider(long card_provider); // Identify which company the card belongs to

int main(void)
{
    long CC = get_long("Enter your card number: ");
    // Run `check_length` func to determine length of inputted CC
    length = check_length(CC);
    // If CC length is valid, execute luhn's algo, else print INVALID
    if (length == 13 || length == 15 || length == 16)
    {
        int valid = luhn(CC);
        // If CC passed luhn's algo as valid, run through provider func, else print INVALID
        if (valid == 1)
        {
            string company = provider(CC);
            printf("%s", company);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long check_length(long card_length)
{
    long i = 1;
    long j = 1;
    // Increment count for each power of 10 of card_length
    for (; card_length / j >= 10; i++)
    {
        // Move up by one power of ten
        j = j * 10;
    }
    return i;
}

bool luhn(long card_luhn)
{
    long input = card_luhn;
    int i = 1;
    // sum of digits that must be doubled
    int sum_even = 0;
    // sum of digits that must  not be doubled
    int sum_odd = 0;
    int sum_total;
    for (; i <= length; i++)
    {
        // Find digit in ones place
        int remainder = input % 10;
        // Branch if digit's place is even
        if (i % 2 == 0)
        {
            // Multiply digit by 2
            int remainder_mult = remainder * 2;
            // If remainder_mult is >= 10, it must be separate into ones and tens digits, then added
            if (remainder_mult >= 10)
            {
                // Find digit in ones place
                int sum3 = remainder_mult % 10;
                // Find digit in 10s place
                remainder_mult = remainder_mult / 10;
                // Add digit in ones and tens place
                sum3 = sum3 + remainder_mult;
                // Add to existing sum_even
                sum_even = sum_even + sum3;
            }
            // If remainder_mult < 10, then just add to sum_even
            else
            {
                sum_even = sum_even + (remainder_mult);
            }
        }
        // If digits place is odd
        else
        {
            sum_odd = sum_odd + remainder;
        }
        // Increment down a power of 10 to move to the next digit place and repeat
        input = (input - remainder) / 10;
    }
    sum_total = sum_odd + sum_even;
    // Check if last digit of sum_total is a 0
    bool valid = sum_total % 10 == 0;
    return valid;
}

string provider(long card_provider)
{
    string provider;
    // Pair down CC number until only the first two digits remain
    for (int i = 1; length - i >= 2; i++)
    {
        int remainder = card_provider % 10;
        card_provider = (card_provider - remainder) / 10;
    }
    if (card_provider >= 51 && card_provider <= 55)
    {
        provider = "MASTERCARD\n";
        return provider;
    }
    else if (card_provider == 34 || card_provider == 37)
    {
        provider = "AMEX\n";
        return provider;
    }
    else if (card_provider >= 40 && card_provider <= 49)
    {
        provider = "VISA\n";
        return provider;
    }
    else
    {
        provider = "INVALID\n";
        return provider;
    }
}
