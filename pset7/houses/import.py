# A program to load a CSV file into a SQL database

from cs50 import SQL
import csv
from sys import argv

# Create SQL database object
db = SQL("sqlite:///students.db")

# Check for correct number of CL arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Open and access the CSV fille
characters = csv.DictReader(open(argv[1]))

# Iterate over rows in CSV to get info
for row in characters:
    name = row['name'].split()
    house = row['house']
    birth = row['birth']

    # If no middle name, assign None
    if len(name) == 2:
        name.insert(1, None)
    # Extract first, middle, and last names from name
    first = name[0]
    middle = name[1]
    last = name[2]

    # Add info to SQL table
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)