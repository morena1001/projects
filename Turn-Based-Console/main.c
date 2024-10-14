#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree_of_transmission.h"



int main(void) {
    trie_node* root;

    root = Trie_Init(root);
    Print_Trie_Tree(root);
    
    return 0;
}
