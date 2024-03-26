#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.c"



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
    return str++;
}


int main(void)
{
    char* str = "this is a long string with a story to tell many words have been etched here though there is no punctuation or capitalization to satisfy the trie structures requirements so it goes right I dont know if this makes any sense but oh well";

    // initialize trie.
    trieNode* trie = malloc(sizeof(trieNode));
    trie->parent = NULL;
    trie->visits = 0;
    for(int i = 0; i< children_count; i++)
    {
        trie->children[i]=NULL;
    }

    char* next;
    while((next = split(str)))
    {
        visitNode(str, trie);
        str = next;
    }

    printTrie(stdout, trie);
    return 0;

}


