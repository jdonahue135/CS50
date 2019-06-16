// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//maximum elements of hash table
#define SIZE 1000

// Create struct for node
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;

//Create hash table
node *hashtable[1001];

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
