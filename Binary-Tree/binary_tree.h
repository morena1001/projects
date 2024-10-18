
typedef struct Node node_t;
typedef struct Queue queue_t;
extern node_t* root;
extern queue_t* head;
extern queue_t* tail;

struct Node {
    int value;
    node_t* left;
    node_t* right;
};

struct Queue {
    node_t* node;
    queue_t* next; 
};

// BST FUNCTIONS
node_t* Make_Node (int value);
void Free_Node (node_t* node);

void Assign_Root (node_t* node);

void BST_Insert_Node (int value);
void BST_Remove_Node (node_t* node);

node_t* Find_Parent (int value);
node_t* Find_Parent_Node (node_t* child);

// AVL FUNCTIONS
void AVL_Insert_Node (int value);
void AVL_Remove_Node (node_t* node);

int Depth (node_t* node);

void Left_Rotation (node_t* top_node);
void Right_Rotation (node_t* top_node);
void Left_Right_Rotation (node_t* top_node);
void Right_Left_Rotation (node_t* top_node);

// PRINTING FUNCTIONS
void Print_Inorder (node_t* node);
void Print_Preorder (node_t* node);
void Print_Postorder (node_t* node);

// QUEUE FUNCTIONS
void Queue_Init ();
void Queue_Deinit ();
void push (node_t* node);
void push_simple (int value);
node_t* pop ();

