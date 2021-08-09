// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Count size of dictionary
unsigned int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word
    unsigned int h = hash(word);
    // If there isn't anything table[h], return false (word not in dictionary)
    if (!table[h])
    {
        return false;
    }
    // If table[h] is occupied, search for the word in the linked list
    for (node *cursor = table[h]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// Using FNV-1a hash (http://isthe.com/chongo/tech/comp/fnv/#FNV-1a
// and some additional info from https://eternallyconfuzzled.com/hashing-c-introduction-to-hashing)
unsigned int hash(const char *word)
{
    // "Magic numbers" given as recommendations for FNV-1a hash
    unsigned int h = 2166136261;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Set the word to lowercase to hash it correctly
        int c = tolower(word[i]);
        // Apply algorithm to each letter of the word
        h = (h * 16777619) ^ c;
    }
    // Use h % N to get actual array index
    h %= N;
    return h;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *fdict = fopen(dictionary, "r");
    if (fdict == NULL)
    {
        return false;
    }

    // Initialize table[]
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read strings from dictionary...
    char new_word[LENGTH + 1];
    // ...until reach end of dictionary
    while (fscanf(fdict, "%s", new_word) != EOF)
    {
        // Count number of words in dictionary
        num_words++;

        // Create new node for each word
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }
        // Add word to node and set n->next to NULL
        strcpy(tmp->word, new_word);
        tmp->next = NULL;

        // Hash word to get index
        unsigned int h = hash(new_word);

        // Insert node in table
        // If there's no node yet at table[hash], set to new node n
        if (!table[h])
        {
            table[h] = tmp;
        }
        // If there's already a node at table[hash], add the new node to the top of the list
        else
        {
            tmp->next = table[h]->next;
            table[h]->next = tmp;
        }
    }
    // Close the dictionary file
    fclose(fdict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Cursor will traverse the list
    node *cursor = NULL;
    // Temp will maintain place at the head of a list
    node *temp = NULL;

    // Iterate over hash table
    for (unsigned int i = 0; i < N; i++)
    {
        // Set cursor to head of list
        cursor = table[i];
        // Until you reach the end of the linked list...
        while (cursor != NULL)
        {
            // ...move along the list, freeing previous node as you go
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }
    return true;
}
