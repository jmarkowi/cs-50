#include <stdio.h>
#include <cs50.h>

bool luhn(long n);
string which_card(long n);
int count(long n);
int first_two(long n);

int main(void)
{
    long n = get_long("Number: ");

    if (luhn(n) == true)
    {
        string result = which_card(n);
        printf("%s\n", result);
    }
    else
    {
        printf("INVALID\n");
    }
}

//Functions defined below

//Use Luhn's algorithm to test the card number
bool luhn(long n)
{
    //Initialize variables
    long num = n;
    int count = 1, odds = 0, evens = 0, next_digit;

    //Deconstruct num and add the digits according to Luhn's algorithm
    while (num)
    {
        //Get the last digit of the current value of num
        next_digit = num % 10;

        //Start w/last digit of num, then every other (odds)
        if (count % 2 != 0)
        {
            odds += next_digit;
        }

        //Start w/penultimate digit of num, then every other (evens)
        else
        {
            int d = 2 * next_digit;

            if (d >= 10)
            {
                while (d)
                {
                    evens += (d % 10);
                    d /= 10;
                }
            }
            else
            {
                evens += d;
            }
        }
        num /= 10;
        count++;
    }

    //Find the sum
    int check = odds + evens;
    //Check if the last digit of the sum is 0
    if (check % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Which credit card company is the card from?
string which_card(long n)
{
    long num = n;
    int digits = count(num);
    int first = first_two(n);

    //Check the number by its first digit AND its length
    if ((first == 34 || first == 37) && digits == 15)
    {
        return "AMEX";
    }
    else if ((first >= 40 && first <= 49) && (digits == 13 || digits == 16))
    {
        return "VISA";
    }
    else if ((first > 50 && first < 56) && digits == 16)
    {
        return "MASTERCARD";
    }
    else
    {
        return "INVALID";
    }
}

//Count the digits in the number
int count(long n)
{
    long num = n;
    int digits = 0;
    while (num > 0)
    {
        digits++;
        num /= 10;
    }
    return digits;
}

//Get the first two digits of the number
int first_two(long n)
{
    long num = n;
    int first = 0;
    while (num > 10)
    {
        first = num;
        num /= 10;
    }
    return first;
}