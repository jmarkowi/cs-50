#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <strings.h>

int main(int argc, string argv[])
{
    string first = argv[1];
    string second = argv[2];

    int result = strcasecmp(first, second);
    printf("%i\n", result);
    if (strcasecmp(first, second) == 0)
    {
        printf("They're the same!\n");
    }
    else
    {
        printf("They're different!\n");
    }
}