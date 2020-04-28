// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 50000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{

unsigned int hashv = 0;
    for (int i=0, n=strlen(word); i<n; i++) {
        hashv = (hashv << 2) ^ tolower(word[i]);
    }
    return hashv % N;
}

//for usage in size()
int sum=0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node *new_word= malloc(sizeof(node));
        if(new_word==NULL)
        {
            unload();
            return false;
        }
        strcpy(new_word->word, word);
        new_word->next=NULL;

        int index=hash(word);
        if(index<0 || index>=N)
        {
            return false;
        }
        else
        {
            if(hashtable[index]==NULL)
            {
                //make the head point to new_word//
                hashtable[index]= new_word;
                new_word->next=NULL;
            }
            else
            {
                //create temp(malloc too) pointing to wherever head points.
                //make new_word->next point to where temp points. make head point to new_word. free temp.
                node*temp;
                temp=hashtable[index];
                new_word->next= temp;
                hashtable[index]=new_word;
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO- create for loop which runs until eof. initialise to 0, keep ++ing. store in the variable.
    //however many times the word is successfully added to the LL, variable gets +ed.
    int x=0;
    for(int p=0; p<N; p++)
    {
        node*ptr;
        ptr=hashtable[p];
        if(hashtable[p]==NULL)
        {
            sum=0;
        }
        else
        {
            sum=1;
            while(ptr->next!=NULL)
            {
                sum++;
                ptr=ptr->next;
            }

        }
       x=x+sum;
    }


    bool loaded=false;
    for(int i=0;i<N;i++)
    {
        if(hashtable[i]!=NULL)
        {
            loaded=true;
            break;
        }
    }
    if(loaded==true)
    return x;
    else
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO: hashfunc word. go to corresponding index. go thru ll. if word found via strcasecmp, return true. else false.
    node*ptr= hashtable[hash(word)];
    if(ptr==NULL)
    {
        return false;
    }
    else
    {
        while(ptr!=NULL)
        {
            if(strcasecmp(word, ptr->word)==0)
            {
                return true;
                break;
            }
                ptr=ptr->next;
        }
        // if(strcasecmp(word, ptr->word)==0)
        //     {
        //         return true;
        //     }

    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO: go to every index. traverse thru ll to find null. free the entire ll. (use for loop to go to every index)
    node*ptr;
    bool found=false;
    for(int i=0; i<N; i++)
    {
        if(hashtable[i]==NULL)
        {
            found= true;
        }
        else
        {
            ptr=hashtable[i];
            while(ptr->next!=NULL)
            {
                node*temp= ptr;
                hashtable[i]=ptr->next;
                ptr=ptr->next;
                free(temp);
            }
            free(ptr);
            hashtable[i]=NULL;
            found= true;
        }
    }
   if(found==true)
   return true;
   else
   return false;
}
