#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Trie{

    int terminal; //check if the word ends or not
    struct Trie* children[26]; //size 26 bc 26 letters in alphabet

}Trie;

struct Trie* init() {
    //creating the structure without inserting any words
    //aka the frame per se

    struct Trie* tree = malloc(sizeof(Trie));
    tree->terminal = 0; //no words yet, so 0

    int i;
    for(i = 0; i < 26; i++)
        tree->children[i] = NULL; //make the children NULL so that insert has a place to insert letters
        
    return tree;

}  

void insert(struct Trie **ppTrie, char *word){

    if(ppTrie == NULL || word == NULL) //gotta check the existence to move forward
        return;

    Trie* trie = *ppTrie;

    for(int i = 0; i < strlen(word); i++){
        char c = word[i];

    if(trie->children[c - 'a'] == NULL) // c - 'a' is so the value is a number between 0-26
        trie->children[c - 'a'] = init(); //new node is created if no room

    trie = trie->children[c - 'a'];
    }

    trie->terminal = 1; //bc end of the word is reached
}
int numberOfOccurances(struct Trie *pTrie, char *word){

    if(pTrie == NULL || word == NULL)
        return 0; //bc not found or DNE

    int i, ind;

    struct Trie *current = pTrie; //to traverse

    for(i = 0; i < strlen(word); i++){
        ind = word[i] - 'a'; // - 'a' to get index between 0-26
    
        if(current->children[ind] == NULL) //if reach NULL, then the word is not in the tree
            return 0;

        current = current->children[ind];
    //if iterates with no problem, then it exits loop and returns the terminal, indicating if the word was found or not
    }

    return current->terminal; //terminal is 1 so return 1 if word is found
}
struct Trie *deallocateTrie(struct Trie *pTrie){

    if(pTrie != NULL){
        for(int i = 0; i < 26; i++) //going through the nodes and freeing them
            deallocateTrie(pTrie->children[i]);
    
        free(pTrie);
    }

    return NULL;
}

int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    Trie* trie = init();

    for (int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < 5; i++)
    {

        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    }

    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
