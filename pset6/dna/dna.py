# A program to match a DNA sequence to its owner

from sys import argv, exit
import csv
import string

# Check for correct number of command-line arguments (3)
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Open and read CSV file
data = csv.DictReader(open(argv[1]))
# Create a list of the PRTs from the CSV
bases = []
for fieldname in data.fieldnames:
    bases.append(fieldname)
bases.pop(0)

# Open and read DNA sequence
sequence = open(argv[2]).read()

# Recursively count consecutive matching STRs (bases)
def find_match(counter, seq, j):
    k = j + len(seq)
    # Check if next set of bases in sequence is seq
    if seq in sequence[j:k] and k < len(sequence):
        counter += 1
        return find_match(counter, seq, k)
    else:
        return counter

# Iterate over bases in data to find consecutive STR repeats in sequence
# Keep track of consecutive repeats of each type
repeats = []
# Iterate over each STR
for i in range(len(bases)):
    repeats.append(0)
    # Iterate over each letter in the sequence .txt
    for j in range(len(sequence)):
        counter = 0
        counter = find_match(counter, bases[i], j)
        if counter > repeats[i]:
            repeats[i] = counter

# Check if the repeats list matches any of the names in data (csv)
# Iterate over each row in the data CSV
for row in data:
    frequencies = []
    for i in range(len(data.fieldnames)):
        # Get the name of the person
        if i < 1:
            person = row[data.fieldnames[i]]
        # Get that person's STR frequences
        else:
            frequencies.append(int(row[data.fieldnames[i]]))
    # Compare person's STR frequencies to repeats from DNA sequence
    if repeats == frequencies:
        print(person)
        exit(0)
print("No match")