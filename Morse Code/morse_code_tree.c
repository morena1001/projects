#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "morse_code_tree.h"

tree_node* Make_Tree_Node (char data, bool is_leaf) {
    // Allocate memory for a trie node
    tree_node* node = (tree_node*) calloc(1, sizeof(tree_node)); 
    for (int i = 0; i < CHILD_COUNT; i++)     node->children[i] = NULL;
    node -> is_leaf = is_leaf;
    node->letter = data;

    return node;
}

void Free_Tree_Node (tree_node* node) {
    // Free the trie node sequence
    for (int i = 0; i < CHILD_COUNT; i++) {
        if (node->children[i])  Free_Tree_Node(node->children[i]);
        else    continue;
    }

    free(node);
}



void Tree_Init() {
    root = Make_Tree_Node(' ', false);
    tree_node* temp = root;

    temp->children[0] = Make_Tree_Node('E', true);
    temp->children[1] = Make_Tree_Node('T', true);

    tree_node* temp_2 = temp->children[0];

    temp_2->children[0] = Make_Tree_Node('I', true);
    temp_2->children[1] = Make_Tree_Node('A', true);

    temp = temp_2->children[0];

    temp->children[0] = Make_Tree_Node('S', true);
    temp->children[1] = Make_Tree_Node('U', true);

    temp_2 = temp->children[0];

    temp_2->children[0] = Make_Tree_Node('H', true);
    temp_2->children[1] = Make_Tree_Node('V', true);

    temp_2 = temp_2->children[0];

    temp_2->children[0] = Make_Tree_Node('5', true);
    temp_2->children[1] = Make_Tree_Node('4', true);

    temp_2 = temp->children[0]->children[1];
    temp_2->children[1] = Make_Tree_Node('3', true);

    temp_2 = temp->children[1];

    temp_2->children[0] = Make_Tree_Node('F', true);
    temp_2->children[1] = Make_Tree_Node(' ', false);

    temp_2 = temp_2->children[1];

    temp_2->children[0] = Make_Tree_Node(' ', false);
    temp_2->children[1] = Make_Tree_Node('2', true);

    temp_2 = temp_2->children[0];

    temp_2->children[0] = Make_Tree_Node('?', true);

    temp = root->children[0]->children[1];

    temp->children[0] = Make_Tree_Node('R', true);
    temp->children[1] = Make_Tree_Node('W', true);

    temp_2 = temp->children[0];

    temp_2->children[0] = Make_Tree_Node('L', true);
    temp_2->children[1] = Make_Tree_Node(' ', false);

    temp_2 = temp_2->children[1];
    temp_2->children[0] = Make_Tree_Node(' ', false);

    temp_2->children[0]->children[1] = Make_Tree_Node('.', true);

    temp_2 = temp->children[1];

    temp_2->children[0] = Make_Tree_Node('P', true);
    temp_2->children[1] = Make_Tree_Node('J', true);

    temp_2->children[1]->children[1] = Make_Tree_Node('1', true);

    temp = root->children[1];

    temp->children[0] = Make_Tree_Node('N', true);
    temp->children[1] = Make_Tree_Node('M', true);

    temp_2 = temp->children[0];

    temp_2->children[0] = Make_Tree_Node('P', true);
    temp_2->children[1] = Make_Tree_Node('K', true);

    temp_2 = temp_2->children[0];

    temp_2->children[0] = Make_Tree_Node('B', true);
    temp_2->children[1] = Make_Tree_Node('X', true);

    temp_2->children[0]->children[0] = Make_Tree_Node('6', true);

    temp_2 = temp->children[0]->children[1];
    
    temp_2->children[0] = Make_Tree_Node('C', true);
    temp_2->children[1] = Make_Tree_Node('Y', true);

    temp = temp->children[1];

    temp->children[0] = Make_Tree_Node('G', true);
    temp->children[1] = Make_Tree_Node('O', true);

    temp_2 = temp->children[0];

    temp_2->children[0] = Make_Tree_Node('Z', true);
    temp_2->children[1] = Make_Tree_Node('Q', true);

    temp_2 = temp_2->children[0];

    temp_2->children[0] = Make_Tree_Node('7', true);
    temp_2->children[1] = Make_Tree_Node(' ', false);

    temp_2->children[1]->children[1] = Make_Tree_Node(',', true);

    temp_2 = temp->children[1];

    temp_2->children[0] = Make_Tree_Node(' ', false);
    temp_2->children[1] = Make_Tree_Node(' ', false);

    temp_2->children[0]->children[0] = Make_Tree_Node('8', true);
    temp_2->children[1]->children[0] = Make_Tree_Node('9', true);
    temp_2->children[1]->children[1] = Make_Tree_Node('0', true);
}

void Print_Tree() {
    char* letters = malloc(sizeof(char) * 45);
    Tree_Node_Letters(root, &letters);
    printf("%s\r\n", letters);
}

void Tree_Node_Letters(tree_node* node, char** output) {
    if (node == NULL) {
        return;
    } else {
        if (node->is_leaf)  strcat(*output, (char*) &(node->letter));

        Tree_Node_Letters(node->children[0], output);
        Tree_Node_Letters(node->children[1], output);
    }
}
