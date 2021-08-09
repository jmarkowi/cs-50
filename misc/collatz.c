#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main (void)
{
    int n;
    do
    {
        n = get_int("Starting number: ");
    } while (n < 1);

    int steps = collatz(n);
    printf("%i steps to get back to 1.\n", steps);
}

int collatz(int n)
{
    // Base case
    if (n == 1)
        return 0;
    // Odd numbers
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    // Even numbers
    else
        return 1 + collatz(3 * n + 1);
}