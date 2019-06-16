// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int hash_func(const char* word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //gets length of word
    char lword[LENGTH+1];
    int n = strlen(word);

    //converts word to lowercase for hashing
    for (int i = 0; i < n + 1; i++)
    {
        lword[i] = tolower(word[i]);
    }
    //hashes word
    unsigned int hashbucket = hash_func(lword);
    if(!hashtable[hashbucket])
    {
        return false;
    }
    else
    {
        bool found = false;
        node *head = hashtable[hashbucket];
        node *ptr = head;
        while (ptr != NULL)
        {
            if (strcasecmp(ptr->word, word) == 0)
            {
                found = true;
                ptr = NULL;
                break;
            }
            else
            {
                ptr=ptr->next;
            }
        }
        return found;
    }
}

// Loads dictionary into memory, returning true if successful else false
//think I need to make this into a hash table. Needs to call hash function below
bool load(const char *dictionary)
{
    //Open dictionary
    FILE *file = fopen(dictionary, "r");

    //returns false if unsucessful
    if (file == NULL)
    {
        printf("Could not open %s\n.", dictionary);
        return false;
    }
    // hash each word into hash table until end of dictionary
    else
    {
        //declares an array for a word
        char aword[LENGTH+1];

        //scans file, searches file for a string, and makes a new word
        while(fscanf(file, "%s", aword) != EOF)
        {
            //get hashbucket for word
            unsigned int hashbucket = hash_func(aword);
            //check if another word is in this hashbucket
            if (hashtable[hashbucket] == NULL)
            {
                //put word in hashbucket
                //Allocate space for word
                node *new_word = malloc(sizeof(node));
                if (new_word == NULL)
                {
                    printf("Could not access memory\n");
                    unload();
                    return false;
                }
                new_word->next = NULL;
                strcpy(new_word->word, aword);
                hashtable[hashbucket] = new_word;
            }
            else
            {
                node *new_word = malloc(sizeof(node));
                if (new_word == NULL)
                {
                    printf("Could not access memory\n");
                    unload();
                    return false;
                }
                //sets new word at beginning of linked list and keeps track of next word (former beginning of linked list)
                strcpy(new_word->word, aword);
                new_word->next = hashtable[hashbucket];
                hashtable[hashbucket] = new_word;
            }
        }
    }
    fclose(file);
    //returns true if sucessful
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int string_count = 0;
    for(int hashbucket = 0; hashbucket < SIZE; hashbucket++)
    {
        node *cursor = hashtable[hashbucket];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            string_count++;
        }
    }
    return string_count;
}

// Unloads dictionary from memory, returning true if successful else false
//think I need to use recursion to delete list (singly-linked list short details how to do this with "destroy" function)
bool unload(void)
{
    for(int hashbucket = 0; hashbucket < SIZE; hashbucket++)
    {
        node *cursor = hashtable[hashbucket];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

//Hash function that I got online, no author mentioned
unsigned int hash_func(const char* word)
{
    unsigned int hash = 0;
    for (int i=0; word[i]!= '\0'; i++)
    {
        hash = 31*hash + word[i];
    }
    return hash % SIZE;
}