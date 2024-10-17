#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_tree.h"

node_t* root;
queue_t* head;
queue_t* tail;

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

void Insert_Node (int value) {
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

void Remove_Node (node_t* node) {
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

    if (child == NULL)      return NULL;
    
    while (child->value != value) {
        parent = child;
        child = value < parent->value ? parent->left : parent->right;

        if (child == NULL)      return NULL;
    }
        
    return parent;
}

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
