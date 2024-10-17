#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "binary_tree.h"

int main (int argc, char* argv) {
    Insert_Node (5);
    Insert_Node (2);
    Insert_Node (3);
    Insert_Node (1);
    Insert_Node (7);
    Insert_Node (6);

    Print_Inorder (root);
    printf ("\n");
    
    Remove_Node (root);

    Print_Inorder (root);
    printf ("\n");

    return 0;
}
