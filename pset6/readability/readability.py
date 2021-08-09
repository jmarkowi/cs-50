# A program to determine the grade level of a given text

from cs50 import get_string
import string
import math


# Get text from user
text = get_string("Text: ")

# Count the number of letters, words, and sentences in text
letters, words, sentences = 0, 1, 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace():
        words += 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Calculate the Coleman-Liau index
l_avg = (letters / words) * 100
s_avg = (sentences / words) * 100
index = round(0.0588 * l_avg - 0.296 * s_avg - 15.8)

# Print the index
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")