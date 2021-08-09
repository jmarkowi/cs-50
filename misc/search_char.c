#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string input = get_string("Input: ");
    int a = 0;

    for (int i = 65; i <= 90; i++)
    {
        char c = (char) i;
        strstr(input, &c)
    }
    printf("%i missing letters found.\n", a);
}