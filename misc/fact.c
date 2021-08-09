#include <stdio.h>
#include <cs50.h>

int fact(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Starting number: ");
    } while (n < 1);

    printf("%i\n", fact(n));
}

int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n-1);
}