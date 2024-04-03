// If you've not encountered a header file, it's essentially a way to seperate the 'interface' of a system from it's implementation.
// it will contain the definition of our struct, which I've named trieNode, as well as the function declarions (but not definitions) we expect indexPage.c may need.
// we will have another file, probably trie.c, to implement these functions. 
// we can include this file in our file with main, and have access to all of the functions definied by it.
// trie.c will also include this file to get access to the struct trieNode.
// this means this file will be included multiple times. the compiler doesn't like this, so there's a common
// set of preprocessor directives called the 'include guard' that prevents the contents of the header from being included more than once.

#ifndef TRIE_H  // TRIE_H is just a name we're making up. It doesn't matter, so long as it's unique.
#define TRIE_H  // I think we can access it from C code though. it's a constant though. not sure what it's value would be, but it doesn't really matter.

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define children_count 26
// this allows us to refer to the struct as simply 'trieNode' instead of 'struct trieNode'
// we can totally talk about what this struct should look like, but this is what made sense to me. If you've got another idea you prefer, we can totally do that.
typedef struct trieNode trieNode;

struct trieNode 
{
    trieNode* children[children_count];     // we are only dealing with lower-case alphabetical elements, so we can use a definite sized buffer.
                                // this also allows us to represent the links between nodes without specifying the character.
                                // we can get the character prefix of a node by adding 'a' to it's index within its parent.
                                // note that each element in the array should be set to NULL when a trieNode is initialized.

    trieNode* parent;           // the parent node. this would be NULL for the root node. This is not strictly neccesary, but may be convienent.

    unsigned int visits;        // the number of times that visitNode has been called with the name of this trieNode.

};


// note: this just has the functions that the main file needs to use. We can totally discuss whether these are the functions we want to be here, 
// but this is just what I thought was a good idea.
// if you see any flaws with anything, point them out! I'd rather not waste time writing functions that are pointless or don't make sense or whatever.
// You can definitely create more functions to break up tasks into smaller pieces in trie.c, though, if the main file won't need to use them directly.
// if you do, you should make these functions static, which in C, makes functions 'private' to a particular source file. 




trieNode* visitNode(const char* key, trieNode* root);
// find or create a trieNode with a particular name, key, and increment its visits member by one.
// key is a null termimnated string and should consist of only lower-case alphabetic characters.
// returns a pointer to the node on success, or NULL on failure.
// may create one or more nodes (with malloc) if key does not represent an existing node.
// In this case, the only new node whose name matches key will have a nonzero visits member. Its value will be 1.
// nodes that are created should should be freed with freeNode when they are no longer needed.


trieNode* getNode(const char* key, trieNode* root);
// gets an existing node without modifying the trie.
// key is a null termimnated string and should consist of only lower-case alphabetic characters.
// returns a pointer to the node if it exists. Otherwise returns NULL.
// if key is an empty string, the function returns root.


void freeNode(trieNode* node);
// frees a node and all of its children.
// node is a pointer to the node to be freed.
// node may be NULL, in which case, no action is taken.
// probably the only time this will be called is to free the root node, freeing the entire Trie.


char* getKeyOfNode(const trieNode* node);
// returns a null terminated string of lower-case alpheberic characters such that
// getNode would return node on this string.
// this function requires a trieNode to know it's parent. If we decide to remove that from the struct,
// then code to print the trie becomes more complicated, and this function ceases to be.
// this string should be freed.


void printTrie(FILE* stream, const trieNode* root);
// prints a node and all of it's children to stream.
// you can use fprintf to implement this
// can be invoked 'printTrie(stdout, root_name)' for printing to console.
// should only print notes with nonzero visits.
// nodes should be displayed in the form 'key: visits'


#endif  // this is the end of our include gaurd.
