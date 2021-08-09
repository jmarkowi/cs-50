from cs50 import get_int

# Get height from user
while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

# Make the pyramid!
for i in range(n):
    print(" " * (n-i-1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))