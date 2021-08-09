#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string validate(int argc, string s);
bool only_int(string s);
string encipher(string plaintext, int key);

int main(int argc, string argv[])
{
    //Validate the user's key
    string validation = validate(argc, argv[1]);
    if (strcmp(validation, "validated") != 0)
    {
        printf("%s\n", validation);
        return 1;
    }
    //Convert the user's key from a string to an int
    int key = atoi(argv[1]);

    //Get the plaintext
    string plaintext = get_string("plaintext: ");

    //Encipher plaintext
    string ciphertext = encipher(plaintext, key);

    //Print ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

//Validate the user's key
string validate(int argc, string s)
{
    //Check for command line argument
    if (argc != 2)
    {
        return "Usage: ./caesar key";
    }

    //Check that key is a positive integer
    if (!only_int(s))
    {
        return "Key must be a positive integer.";
    }

    //If the key satisfies the requirements
    else
    {
        return "validated";
    }
}

//Does key contain only numbers?
bool only_int(string s)
{
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

//Encipher the user's plaintext using the key
string encipher(string plaintext, int key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        //Only encode letters; ignore non-alphas
        if (isalpha(plaintext[i]) != 0)
        {
            //Read plaintext[i] to a char and standardize case for ease of enciphering
            char letter = toupper(plaintext[i]);
            //Convert char into int so A = 1 ... Z = 26
            int c = letter - 64;

            //Shift each letteer according to the key
            if ((c + key) > 26)
            {
                c = (c + key) % 26;
            }
            else

            {
                c = c + key;
            }

            //Write enciphered letter, maintaining original case
            if (isupper(plaintext[i]) != 0)
            {
                plaintext[i] = (char) toupper(c + 64);
            }
            if (islower(plaintext[i]) != 0)
            {
                plaintext[i] = (char) tolower(c + 64);
            }
        }
    }
    return plaintext;
}