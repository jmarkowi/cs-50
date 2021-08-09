#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

string validate(int argc, string s);
bool only_letters(string s);
bool no_repeats(string s);
string encipher(string plaintext, string key);

int main(int argc, string argv[])
{
    //Validate the user's key
    string validation = validate(argc, argv[1]);
    if (strcmp(validation, "validated") != 0)
    {
        printf("%s\n", validation);
        return 1;
    }

    //Get the plaintext
    string plaintext = get_string("plaintext: ");

    //Encipher plaintext
    string ciphertext = encipher(plaintext, argv[1]);

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
        return "Usage: ./substitution key";
    }

    //Check that key length is 26
    if (strlen(s) != 26)
    {
        return "Key must contain 26 distinct letters.";
    }

    //Check that key contains only letters
    if (!only_letters(s))
    {
        return "Key must contain only letters.";
    }

    //Check that key contains all 26 letters without repeats
    if (!no_repeats(s))
    {
        return "Key cannot contain repeated letters.";
    }

    //If the key satisfies the requirements
    else
    {
        return "validated";
    }
}

//Does key contain only letters?
bool only_letters(string s)
{
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

//Does key contain all 26 letters one time each?
//NOTE: This test assumes the key is exactly 26 characters.
bool no_repeats(string s)
{
    int n = strlen(s);
    //Set user's key to uppercase
    for (int i = 0; i < n; i ++)
    {
        s[i] = toupper(s[i]);
    }

    //Search the user's key for repeated letters
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j ++)
        {
            if (s[i] == s[j])
            {
                return false;
            }
        }
    }
    return true;
}

//Encipher the user's plaintext using the key
string encipher(string plaintext, string key)
{
    //Create a ciphertext char array (creating string => 'Segmentation fault')
    //int n = strlen(plaintext);
    //char ciphertext[n];

    //Iterate over each char of the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        //Only encode letters; ignore non-alphas
        if (isalpha(plaintext[i]) != 0)
        {
            //Read plaintext[i] to a char and standardize case for ease of enciphering
            char letter = toupper(plaintext[i]);
            //Translate the current letter into an int c (a=0 through z=25)
            int c = letter - 65;
            //Write enciphered letter, maintaining original case
            if (isupper(plaintext[i]) != 0)
            {
                plaintext[i] = toupper(key[c]);
            }
            if (islower(plaintext[i]) != 0)
            {
                plaintext[i] = tolower(key[c]);
            }
        }
        //Write non-alphas into ciphertext
        //else
        //{
        //    ciphertext[i] = plaintext[i];
        //}
    }
    //string result = ciphertext;
    return plaintext;
}