#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float index(int letters, int words, int sentences);

int main(void)
{
    //Get the text from the user
    string text = get_string("Text: ");

    //Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //Calculate the index
    float raw_index = index(letters, words, sentences);
    int index = round(raw_index);

    //Print the index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//Count the number of letters in a string
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

//Count the number of words in a string
int count_words(string text)
{
    int words = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    //This accounts for no space after last word in sentence
    words++;

    return words;
}

//Count the number of sentences in a string
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

//Calculate the Coleman-Liau reading level index
float index(int letters, int words, int sentences)
{
    float l_avg = ((float) letters / (float) words) * 100;
    float s_avg = ((float) sentences / (float) words) * 100;

    return 0.0588 * l_avg - 0.296 * s_avg - 15.8;
}