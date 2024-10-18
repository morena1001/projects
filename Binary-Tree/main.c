#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "binary_tree.h"

int main (int argc, char* argv) {
    AVL_Insert_Node (5);
    AVL_Insert_Node (3);
    AVL_Insert_Node (1);
    AVL_Insert_Node (6);
    AVL_Insert_Node (7);

    Print_Inorder (root);
    printf ("\n");

    return 0;
}
