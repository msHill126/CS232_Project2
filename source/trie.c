#ifndef PUBLISHED     // the project requirements state that the entire program must be in a single source doc.
                      // I have setup a makefile target to concatenate all of the source files into a single file for this purpose.
                      // there's no need to have multiple includes in such a file, so they will not be included
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#endif

// function definitions (as outlined in the header) go here.    

trieNode* visitNode(char* key, trieNode* root)
{

}


// frees a node and all of its children.
// node is a pointer to the node to be freed.
// node may be NULL, in which case, no action is taken.
// probably the only time this will be called is to free the root node, freeing the entire Trie.
void freeNode(trieNode* node)
{
    for(int i = 0; i<children_count; i++)
    {
        if(node->children[i]!=NULL)
        {
            freeNode(node->children[i]);
        }

    }

    free(node);
}


// prints a node and all of it's children to stream.
// you can use fprintf to implement this
// can be invoked 'printTrie(stdout, root_name)' for printing to console.
// should only print notes with nonzero visits.
// nodes should be displayed in the form 'key: visits'
void printTrie(FILE* stream, trieNode* root)
{
    if(root->visits)
    {
        char* name = getKeyOfNode(root);
        fprintf(stream, "%s: %d\n", name, root->visits); 
        free(name);  
    }

    for(int i = 0; i<children_count; i++)
    {
        if(root->children[i]!=NULL)
        {
            printTrie(stream, root->children[i]);
        }

    }
}

// returns a null terminated string of lower-case alpheberic characters such that
// getNode would return node on this string.
// this function requires a trieNode to know it's parent. If we decide to remove that from the struct,
// then code to print the trie becomes more complicated, and this function ceases to be.
// this string must be freed if used.
char* getKeyOfNode(trieNode* node)
{
    const int sizeIncrement = 100;
    int size = 100;
    int remaining = size;
    char* reversed = malloc(sizeof(char)*size);

    if(reversed == NULL)
    {
        fprintf(stderr, "Malloc failed in getKeyOfNode...\n");
        exit(1);
    }


    while(node!=NULL)
    {
        reversed[size-remaining]=getCharOfNode(node);
        remaining--;
        node = node->parent;

        if(remaining == 0)
        {
            size += sizeIncrement;
            remaining +=sizeIncrement;
            reversed = realloc(reversed, sizeof(char)*size);
            if(reversed == NULL)
            {
                fprintf(stderr, "Realloc failed in getKeyOfNode...\n");
                exit(1);
            }
        }
    }

    // now, reverse the string.
    char* toReturn = malloc(sizeof(char)*size);
    if(toReturn == NULL)
    {
        fprintf(stderr, "Malloc failed in getKeyOfNode...\n");
        exit(1);
    }
    
    int lastIndex = size-remaining;
    toReturn[lastIndex]='\0';
    lastIndex--;

    for(int i=0; i<lastIndex+1; i++)
    {
        toReturn[i] = reversed[lastIndex-i];
    }

    free(reversed);
    return toReturn;

}

static char getCharOfNode(trieNode* node)
{
    if(node->parent == NULL)
    {
        return '\0';
    }

    for(int i = 0; i<children_count; i++)
    {
        if(node->parent->children[i]==node)
        {
          return 'a'+i;
        }

    }

    fprintf(stderr, "Couldn't get the character of a node. this indicates the trie is broken.\n");
    exit(1);
}


// gets an existing node without modifying the trie.
// key is a null termimnated string and should consist of only lower-case alphabetic characters.
// returns a pointer to the node if it exists. Otherwise returns NULL.
// if key is an empty string, the function returns root.
trieNode* getNode(char* key, trieNode* root)
{
    if(*key=='\0')
    {
        return root;
    }

    trieNode* next = root->children[(*key)-'a'];
    if(next==NULL)
    {
        return NULL;
    }

    return getNode(key++, next);
}

// find or create a trieNode with a particular name, key, and increment its visits member by one.
// key is a null termimnated string and should consist of only lower-case alphabetic characters.
// returns a pointer to the node on success, or NULL on failure.
// may create one or more nodes (with malloc) if key does not represent an existing node.
// In this case, the only new node whose name matches key will have a nonzero visits member. Its value will be 1.
// nodes that are created should should be freed with freeNode when they are no longer needed.
trieNode* visitNode(char* key, trieNode* root)
{
    trieNode* found = getNode(key, root);
    if(found!=NULL)
    {
        found->visits++;
        return found;
    }

    return getOrCreateNode(key, root);
}

static trieNode* getOrCreateNode(char* key, trieNode* root)
{
    
    if(*key=='\0')
    {
        return root;
    }

    trieNode* next = root->children[(*key)-'a'];
    if(next==NULL)
    {
        // create new node.
        next = malloc(sizeof(trieNode));
        if(next==NULL)
        {
             fprintf(stderr, "Malloc failed in getOrCreateNode...\n");
             exit(1);
        }
        next->parent = root;
        next->visits = 1;
        for(int i = 0; i<children_count; i++)
        {
            next->children[i]=NULL;
        }
        return next;
    }

    return getNode(key++, next);
}
