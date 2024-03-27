#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

char* sring = "this is a long string with a story to tell many words have been etched here though there is no punctuation or capitalization to satisfy the trie structures requirements so it goes right i dont know if this makes any sense but oh well";

static char* split(char* str)
{
    while(*str != ' ')
    {
       
        if(*str == '\0')
        {
            return NULL;
        }
        str++;
    }
    *str = '\0';
   
    return ++str;
}


int main(void)
{
    char* newstr = malloc(sizeof(char)*strlen(sring)+1);
    newstr = strncpy(newstr, sring, strlen(sring)+1);
    char* toFree = newstr;
    printf("Start!\n");
    // initialize trie.
    trieNode* trie = malloc(sizeof(trieNode));
    trie->parent = NULL;
    trie->visits = 0;
    for(int i = 0; i< children_count; i++)
    {
        trie->children[i]=NULL;
    }

 
    char* next;
    while((next = split(newstr)))
    {
        //printf("submit: %s\n",newstr);
        visitNode(newstr, trie);
        newstr = next;
    }

    //printf("submit: %s\n","this");
    //visitNode("this", trie);
    //printf("submit: %s\n","the");
    //visitNode("the", trie);

    printf("\n\nPrinting...\n");
    printTrie(stdout, trie);

    trieNode* node = getNode("is", trie);
    if(node != NULL)
    {
         printf("visits for is: %d\n", node->visits);
    }
    else
    {

        printf("node 'is' not found...\n");
    }
   
    freeNode(trie);
    free(toFree);
    return 0;

}


