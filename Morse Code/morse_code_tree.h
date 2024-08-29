// A dot is the first child, or the left branch
// A dash is the second child, or the right branch

#define CHILD_COUNT 2

typedef struct Tree_Node tree_node;
tree_node* root; 

struct Tree_Node {
    char letter;
    tree_node* children[CHILD_COUNT];
    bool is_leaf;
};

tree_node* Make_Tree_Node (char data, bool is_leaf);
void Free_Tree_Node (tree_node* node);

void Tree_Init();
void Print_Tree();

void Tree_Node_Letters(tree_node* node, char** output);
