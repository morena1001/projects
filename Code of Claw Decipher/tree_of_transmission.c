#include <stdlib.h>
#include <stdio.h>
#include "tree_of_transmission.h"



trie_node* Make_Trie_Node (char data) {
    // Allocate memory for a trie node
    trie_node* node = (trie_node*) calloc(1, sizeof(trie_node)); 
    for (int i = 0; i < N; i++)     node->children[i] = NULL;
    // node -> is_leaf = false;
    node->data = data;

    return node;
}



void Free_Trie_Node (trie_node* node) {
    // Free the trie node sequence
    for (int i = 0; i < N; i++) {
        if (node->children[i])  Free_Trie_Node(node->children[i]);
        else    continue;
        
    }

    free(node);
}



trie_node* Trie_Init (trie_node* root) {
    // Base layer : no input 
    root = Make_Trie_Node('-');

    trie_node* temp = root;

    // First layer : single input
    temp->children[0] = Make_Trie_Node('e');
    temp->children[1] = Make_Trie_Node('a');
    temp->children[2] = Make_Trie_Node('i');

    // Second layer, click first input : two inputs
    temp = root->children[0];
    temp->children[0] = Make_Trie_Node('p');
    temp->children[1] = Make_Trie_Node('q');
    temp->children[2] = Make_Trie_Node('r');

    // Second layer, tap first input : two inputs
    temp = root->children[2];
    temp->children[0] = Make_Trie_Node('s');
    temp->children[1] = Make_Trie_Node('t');
    temp->children[2] = Make_Trie_Node('u');

    // Second layer, scratch first input: two inputs
    temp = root->children[1];
    temp->children[0] = Make_Trie_Node('b');
    temp->children[1] = Make_Trie_Node('c');
    temp->children[2] = Make_Trie_Node('d');

    // Third layer, scratch first input, click second input : three inputs
    trie_node* scratch_temp = temp;
    temp = scratch_temp->children[0];
    temp->children[0] = Make_Trie_Node('j');
    temp->children[1] = Make_Trie_Node('k');
    temp->children[2] = Make_Trie_Node('l');

    // Third layer, scratch first input, tap second input : three inputs
    temp = scratch_temp->children[2];
    temp->children[0] = Make_Trie_Node('m');
    temp->children[1] = Make_Trie_Node('n');
    temp->children[2] = Make_Trie_Node('o');

    // Third layer, scratch first and second input : three inputs
    temp = scratch_temp->children[1];
    temp->children[0] = Make_Trie_Node('f');
    temp->children[1] = Make_Trie_Node('g');
    temp->children[2] = Make_Trie_Node('h');

    // Fourth layer, scratch first and second input, click third input : four inputs
    temp->children[0]->children[0] = Make_Trie_Node('v');

    // Fourth layer, scratch first and second input, tap third input : four inputs
    temp->children[0]->children[2] = Make_Trie_Node('w');

    // Fourth layer, scratch fist, second and third inputs : four inputs
    temp = temp->children[1];
    temp->children[0] = Make_Trie_Node('x');
    temp->children[1] = Make_Trie_Node('z');
    temp->children[2] = Make_Trie_Node('y');

    return root;
}



void Print_Trie_Tree(trie_node* root) {
    trie_node* click = root->children[0];
    trie_node* scratch = root->children[1];
    trie_node* tap = root->children[2];

    trie_node* scratch_click = root->children[1]->children[0];
    trie_node* scratch_scratch = root->children[1]->children[1];
    trie_node* scratch_tap = root->children[1]->children[2];

    trie_node* scratch_scratch_scratch = root->children[1]->children[1]->children[1];


    printf("               %c\n\n", scratch_scratch_scratch->children[1]->data);
    printf("            %c  |  %c\n", scratch_scratch_scratch->children[0]->data, scratch_scratch_scratch->children[2]->data);
    printf("             \\   /\n");
    printf("          %c    %c    %c\n", scratch_scratch->children[0]->children[0]->data, scratch_scratch_scratch->data, scratch_scratch->children[0]->children[2]->data);
    printf("           \\       /\n");
    printf("            %c  |  %c\n", scratch_scratch->children[0]->data, scratch_scratch->children[2]->data);
    printf("             \\   /\n");
    printf("     %c  %c  %c   %c   %c  %c  %c\n", scratch_click->children[0]->data, scratch_click->children[1]->data, scratch_click->children[2]->data, 
        scratch_scratch->data, scratch_tap->children[0]->data, scratch_tap->children[1]->data, scratch_tap->children[2]->data);
    printf("      \\ | /         \\ | /\n");
    printf("        %c      |      %c\n", scratch_click->data, scratch_tap->data);
    printf("         \\           /\n");
    printf("%c  %c  %c        %c        %c  %c  %c\n", click->children[0]->data, click->children[1]->data, click->children[2]->data, scratch->data, 
        tap->children[0]->data, tap->children[1]->data, tap->children[2]->data);
    printf(" \\ | /                   \\ | /\n");
    printf("   %c           |           %c\n", click->data, tap->data);
    printf("    \\                     /\n");
    printf("-------------------------------\n");

    free(click);
    free(scratch);
    free(tap); 
    free(scratch_click); 
    free(scratch_scratch);
    free(scratch_tap); 
    free(scratch_scratch_scratch);
}
