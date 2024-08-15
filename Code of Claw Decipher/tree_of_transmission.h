// A click , or move left, is the first child of a trie node
// A scratch, or move up, is the second child of a trie node
// A tap, or move right, is the third child of a trie node

#define N 3


typedef struct Trie_Node trie_node;

struct Trie_Node {
    char data;
    trie_node* children[N];
    // bool is_leaf;
};

// Memory Functions
trie_node* Make_Trie_Node (char data);
void Free_Trie_Node (trie_node* node);

trie_node* Trie_Init(trie_node* root);
void Print_Trie_Tree(trie_node* root);


/*
#include <stdlib.h>

#define LETTER_A "|"
#define LETTER_B "|\\"
#define LETTER_C "||"
#define LETTER_D "|/"
#define LETTER_E "\\"
#define LETTER_F "||\\"
#define LETTER_G "|||"
#define LETTER_H "||/"
#define LETTER_I "/"
#define LETTER_J "|\\\\"
#define LETTER_K "|\\|"
#define LETTER_L "|\\/"
#define LETTER_M "|/\\"
#define LETTER_N "|/|"
#define LETTER_O "|//"
#define LETTER_P "\\\\"
#define LETTER_Q "\\|"
#define LETTER_R "\\/"
#define LETTER_S "/\\"
#define LETTER_T "/|"
#define LETTER_U "//"
#define LETTER_V "||\\\\"
#define LETTER_W "||//"
#define LETTER_X "|||\\"
#define LETTER_Y "|||/"
#define LETTER_Z "||||"

char** All_Possible_Combinations(char* letters);
*/