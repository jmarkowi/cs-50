#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string key = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string plaintext = get_string("Plaintext: ");
    int n = strlen(plaintext);
    char ciphertext[n+1];

    //Iterate over each char of the plaintext
    for (int i = 0; i < n; i++)
    {
        //Only encode letters; ignore non-alphas
        if (isalpha(plaintext[i]) != 0)
        {
            //Read plaintext[i] to a char and standardize case
            char letter = toupper(plaintext[i]);
            //Translate the current letter into an int c (a=0 through z=25)
            int c = letter - 65;
            //Write the enciphered letter, maintaining original case
            if (isupper(plaintext[i]) != 0)
            {
                ciphertext[i] = toupper(key[c]);
            }
            if (islower(plaintext[i]) != 0)
            {
                ciphertext[i] = tolower(key[c]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("Ciphertext: %s\n", ciphertext);
}