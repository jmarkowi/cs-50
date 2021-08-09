# A program to determine if a given credit card number is valid,
# and if so, which company it originates from.

from cs50 import get_int
from math import trunc


def main():
    # Get card number from user
    number = get_int("Number: ")

    # Apply Luhn's algorithm and card rules to determine company
    if luhn(number):
        print(which_card(number))
    else:
        print("INVALID")

# Use Luhn's algorithm to test the card number
def luhn(n):
    count, odds, evens = 1, 0, 0

    # Deconstruct the number and add digits as per Luhn's algorithm
    while n:
        # Get last digit of current value of n
        next_digit = n % 10

        # Start w/last digit, then every other (odds)
        if (count % 2) != 0:
            odds += next_digit

        # Start w/penultimate digit, then every other (evens)
        else:
            d = 2 * next_digit
            # If d is more than 1 digit, add the sum of the digits to even
            if d >= 10:
                while d:
                    evens += trunc(d % 10)
                    d = trunc(d / 10)
            else:
                evens += d

        # Remove the final digit from n and increment the count
        n = trunc(n / 10)
        count += 1

    # Find the sum
    check = odds + evens
    # Check if last digit of sum is 0
    if (check % 10) == 0:
        return True
    else:
        return False

# Which credit card company is the card from?
def which_card(n):
    digits = len(str(n))
    first = first_two(n)

    # Check number by first 2 digits AND length
    if (first == 34 or first == 37) and digits == 15:
        return "AMEX"
    elif (first >= 40 and first <= 49) and (digits == 13 or digits == 16):
        return "VISA"
    elif (first > 50 and first < 56) and digits == 16:
        return "MASTERCARD"
    else:
        return "INVALID"

# Get the first two digits of the number
def first_two(n):
    while n > 10:
        first = n
        n = trunc(n / 10)
    return first

# Run the program
main()