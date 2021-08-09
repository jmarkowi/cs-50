#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Get the user's input in dollars.cents
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    //Convert input into cents
    int cents = round(dollars * 100);

    //Start by adding number of quarters
    int quarters = cents / 25;
    printf("Quarters = %i\n", quarters);
    cents -= quarters * 25;

    //Then add number of dimes
    int dimes = cents / 10;
    printf("Dimes = %i\n", dimes);
    cents -= dimes * 10;

    //Nickels next
    int nickels = cents / 5;
    printf("Nickels = %i\n", nickels);
    cents -= nickels * 5;

    //Finally, add in the pennies
    printf("Pennies = %i\n", cents);
    int coins = quarters + dimes + nickels + cents;
    printf("%i\n", coins);
}