#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_tree.h"

node_t* root;
queue_t* head;
queue_t* tail;

//
// BST FUNCTIONS
//

node_t* Make_Node (int value) {
    node_t* node = (node_t*) calloc (1, sizeof (node_t));
    node->value = value;
    
    node->left  = (node_t*) calloc (1, sizeof (node_t));
    node->right = (node_t*) calloc (1, sizeof (node_t));

    node->left = NULL;
    node->right = NULL;

    return node; 
}

void Free_Node (node_t* node) {
    free (node->left);
    free (node->right);
    free (node);
}

void Assign_Root (node_t* node) {
    root = (node_t*) calloc (1, sizeof (node_t));
    root = node;
}

void BST_Insert_Node (int value) {
    node_t* node = Make_Node (value);
    
    if (root == NULL) {
        Assign_Root (node);
    } else {
        node_t* temp = root;
        bool left = false;

        while (1) {
            if (temp == NULL) {
                break;
            } 
            
            left = node->value < temp->value;
            if (left && temp->left == NULL) {
                temp->left = node;
                break;
            } else if (!left && temp->right == NULL) {
                temp->right = node;
                break;
            } else {
                temp = left ? temp->left : temp->right;
            }
        }
    }
}

void BST_Remove_Node (node_t* node) {
    node_t* parent = Find_Parent (node->value);

    if (node == root) {
        if (node->left == NULL && node->right == NULL) {
            root = NULL;
            free (node);
            return;
        }

        root = node->right;
        parent = root->left;

        while (parent->left != NULL) {
            parent = parent->left;
        }
        parent->left = node->left;

        free (node);
        return;
    }
    if (parent == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        if (parent->left == node)   parent->left  = NULL;
        else                        parent->right = NULL;
        
        free (node);
    } else if (node->left == NULL) {
        if (parent->left == node)   parent->left  = node->right;
        else                        parent->right = node->right;

        free (node);
    } else if (node->right == NULL) {
        if (parent->left == node)   parent->left  = node->left;
        else                        parent->right = node->left;

        free (node);
    } else {
        if (parent->left == node) {
            parent->left  = node->right;
            parent = parent->left;
        } else {
            parent->right = node->right;
            parent = parent->right;
        }

        while (parent->left != NULL) {
            parent = parent->left;
        }
        parent->left = node->left;

        free (node);
    }
}

node_t* Find_Parent(int value) {
    // Assumes that every node has a unique value
    
    if (root->value == value)       return NULL;
    
    node_t* parent = root;
    node_t* child = value < parent->value ? parent->left : parent->right;

    if (child == NULL)              return NULL;
    
    while (child->value != value) {
        parent = child;
        child = value < parent->value ? parent->left : parent->right;

        if (child == NULL)          return NULL;
    }

    free (child);
        
    return parent;
}

node_t* Find_Parent_Node (node_t* child) {
    if (root == child)          return NULL;

    node_t* parent = root;
    node_t* temp_child = child->value < parent->value ? parent->left : parent->right;

    if (temp_child == NULL)          return NULL;

    while (temp_child != child) {
        parent = temp_child;
        temp_child = child->value < parent->value ? parent->left : parent->right;

        if (temp_child == NULL)      return NULL;
    }

    return parent;
}

//
// AVL FUNCTIONS
//

void AVL_Insert_Node (int value) {
    node_t* node = Make_Node (value);
    
    if (root == NULL) {
        Assign_Root (node);
    } else {
        node_t* temp = root;
        bool left = false;

        while (1) {
            if (temp == NULL) {
                break;
            } 
            
            left = node->value < temp->value;
            if (left && temp->left == NULL) {
                temp->left = node;
                break;
            } else if (!left && temp->right == NULL) {
                temp->right = node;
                break;
            } else {
                temp = left ? temp->left : temp->right;
            }
        }

        node_t* parent = Find_Parent_Node (node);

        while (parent != NULL) {
            if (Depth (parent->right) - Depth (parent->left) > 1) {
                if  (parent->right->right != NULL)          Left_Rotation (parent);
                else if (parent->right->left != NULL)       Right_Left_Rotation (parent);
                parent = Find_Parent_Node (parent);
                
            } else if (Depth (parent->left) - Depth (parent->right) > 1) {
                if (parent->left->left != NULL)             Right_Rotation (parent);
                else if (parent->left->right != NULL)       Left_Right_Rotation (parent);
                parent = Find_Parent_Node (parent);
            } 
            
            if (parent == root)     break;

            parent = Find_Parent_Node (parent);
        }
    }
}

void AVL_Remove_Node (node_t* node) {

}

int Depth (node_t* node) {
    if (node == NULL) {
        return 0;
    } else if (node->left == NULL && node->right == NULL) {
        return 1;
    } else {
        int left_subtree = Depth (node->left) + 1;
        int right_subtree = Depth (node->right) + 1;

        return left_subtree > right_subtree ? left_subtree : right_subtree;
    }
}

void Left_Rotation (node_t* top_node) {
    if (top_node == NULL) {
        return;
    }

    if (top_node == root) {
        root = top_node->right;
        root->left = top_node;
        root->left->right = NULL;
    } else {
        node_t* parent = Find_Parent_Node (top_node);

        if (parent->left == top_node) {
            parent->left = top_node->right;
            parent->left->left = top_node;
            parent->left->left->right = NULL;
        } else {
            parent->right = top_node->right;
            parent->right->left = top_node;
            parent->right->left->right = NULL;
        }
    }
}

void Right_Rotation (node_t* top_node) {
    if (top_node == NULL) {
        return;
    }

    if (top_node == root) {
        root = top_node->left;
        root->right = top_node;
        root->right->left = NULL;
    } else {
        node_t* parent = Find_Parent_Node (top_node);

        if (parent->left == top_node) {
            parent->left = top_node->left;
            parent->left->right = top_node;
            parent->left->right->left = NULL;
        } else {
            parent->right = top_node->left;
            parent->right->right = top_node;
            parent->right->right->left = NULL;
        }
    }
}

void Left_Right_Rotation (node_t* top_node) {
    Left_Rotation (top_node->left);
    Right_Rotation (top_node);
}

void Right_Left_Rotation (node_t* top_node) {
    Right_Rotation (top_node->right);
    Left_Rotation (top_node);
}

//
// PRINTING FUNCTIONS
//

void Print_Inorder (node_t* node) {
    Queue_Init ();

    node_t* temp = Make_Node (0);
    push (node);

    while (head != NULL) {
        push (head->node->left);
        push (head->node->right);

        temp = pop ();
        printf ("%d ", temp->value);
    }

    Queue_Deinit ();
}

void Print_Preorder (node_t* node) {
    if (node == NULL) {
        return;
    } else if (node->left == NULL && node->right == NULL) {
        printf ("%d ", node->value);
    } else { 
        printf ("%d ", node->value);
        Print_Preorder (node->left);
        Print_Preorder (node->right);
    }
}

void Print_Postorder (node_t* node) {
if (node == NULL) {
        return;
    } else if (node->left == NULL && node->right == NULL) {
        printf ("%d ", node->value);
    } else { 
        Print_Postorder (node->left);
        Print_Postorder (node->right);
        printf ("%d ", node->value);
    }
}

//
// QUEUE FUNCTIONS
//

void Queue_Init () {
    head = (queue_t*) calloc (1, sizeof (queue_t));
    head->node = (node_t*) calloc (1, sizeof (node_t));
    head->next = (queue_t*) calloc (1, sizeof (queue_t));

    head = NULL;

    tail = (queue_t*) calloc (1, sizeof (queue_t));
    tail->node = (node_t*) calloc (1, sizeof (node_t));
    tail->next = (queue_t*) calloc (1, sizeof (queue_t));

    tail = NULL;
}

void Queue_Deinit () {
    node_t* node = pop ();

    while (node != NULL) {
        node = pop ();
    }

    free (head);
    free (tail);
}

void push (node_t* node) {
    if (node == NULL) {
        return;
    }

    queue_t* item = (queue_t*) calloc (1, sizeof (queue_t));
    item->node = (node_t*) calloc (1, sizeof (node_t));
    item->next = (queue_t*) calloc (1, sizeof (queue_t));

    item->node = node;

    if (head == NULL) {
        item->next = NULL;  
        head = item;
        tail = item;     
    } else { 
        item->next = NULL;
        tail->next = item;
        tail = item;
    }
}

void push_simple (int value) {
    node_t* node = Make_Node (value);
    push (node);
}

node_t* pop () {
    if (head != NULL) {
        node_t* node = head->node;
        queue_t* prev_head = head;
        head = head->next;
        free (prev_head);

        return node;
    } else {
        return NULL;
    }
}
