#include <stdio.h>
#include <cs50.h>

void print_space(int n);
void print_hash(int n);

int main(void)
{
    //First, ask the user for the height of the pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //Make the pyramid
    for (int i = 1; i <= n; i++)
    {
        print_space(n - i);
        print_hash(i);
        print_space(2);
        print_hash(i);
        printf("\n");
    }
}
//Method to print " " n times
void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}
//Method to print a "#" n times
void print_hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}