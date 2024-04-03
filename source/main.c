/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#ifndef triePUBLISHED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include <ctype.h>
#endif



/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

trieNode* indexPage(const char* url);

int addWordOccurrence(const char* word, const int wordLength, trieNode* root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

int main(int argc, char** argv) {
    // Check if the URL argument is provided
    if (argc < 2) {
        fprintf(stderr, "Use: %s <URL>\n", argv[0]);
        return -1; // Return non-zero to indicate failure
    }

    // Call a function that indexes the web page and returns a pointer to the root of the trie
    trieNode* root = indexPage(argv[1]);
    if (root == NULL) {
        fprintf(stderr, "Failed to index the web page\n");
        return -1; // Return non-zero to indicate failure
    }

    // Call a function that prints out the counts of all the words in the trie
    printTrie(stdout, root);

    // Call a function to destroy the trie (i.e., free any allocated memory) when it is no longer needed
    freeNode(root);

    return 0; // Return zero to indicate success
}


/* TODO: define the functions corresponding to the above prototypes */


/*
indexPage function:
-struct node *indexPage(const char *url);
-get the content of a page(getText());	//if zero there is no content
-create a root node
-analyze the content(loop)
	.find a word		//calculate_sum.c
	.addWordOccurrence(...); //recursive 
-return to root
*/

trieNode* indexPage(const char* url) {


    // Store only first 300000 char 
    char buffer[300001]; // +1 for null terminator

    // check for text
    int bytesRead = getText(url, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        fprintf(stderr, "Failed to retrieve text from URL: %s\n", url);
        return NULL; // Return NULL to indicate failure
    }

    // create root node
    trieNode* root = malloc(sizeof(trieNode));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed for trie root\n");
        return NULL; // Return NULL to indicate failure
    }
    root->parent = NULL;
    root->visits = 0;
    for (int i = 0; i < children_count; i++) {
        root->children[i] = NULL;
    }

    // Analyze the content and add words to the trie
    char* word = strtok(buffer, " \t\n\r.,;:!?'\"()[]{}0123456789");
    while (word != NULL) {
        // Clean the word and convert it to lowercase
        char* cleanWord = malloc(strlen(word) + 1);
        printf("\t%s\n", cleanWord);
        if (cleanWord == NULL) {
            fprintf(stderr, "Memory allocation failed for cleanWord\n");
            freeNode(root); // Free allocated memory before returning
            return NULL;
        }
        int j = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            if (isalpha(word[i])) {
                cleanWord[j++] = tolower(word[i]);
            }
        }
        cleanWord[j] = '\0';

        // add the clean word to the trie
        addWordOccurrence(cleanWord, strlen(cleanWord), root);

        // free memory allocated for cleanWord
        free(cleanWord);

        // next word
        word = strtok(NULL, " \t\n\r.,;:!?'\"()[]{}0123456789");
    }

    return root; // Return the root node of the trie
}


int addWordOccurrence(const char* word, const int wordLength, trieNode* root){
  
  // is word empty
    if (word == NULL || wordLength == 0) {
        return 0; // fail
    }

    // Add the word to the trie
    visitNode(word, root);

    return 1;

}


/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
