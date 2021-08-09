# A program to list a Hogwarts House roster of students with birth year

from cs50 import SQL
from sys import argv

# Create SQL database object
db = SQL("sqlite:///students.db")

# Check for correct number of CL arguments
if len(argv) != 2:
    print("Usage: python roster.py House")
    exit(1)

# Get name of the House for the roster
house = argv[1]

# Get names and birth year of students in House
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)
# Iterate over students to print roster
for row in students:
    print(f"{row['first']}", end=" ")
    # Check for middle name
    if row['middle']:
        print(f"{row['middle']}", end=" ")
    print(f"{row['last']}, born {row['birth']}")

    # There has to be a more elegant way to do this printing--
    # maybe by iterating over each key:value in row?
    # That ", born" syntax makes it tricky--can't just print straight results