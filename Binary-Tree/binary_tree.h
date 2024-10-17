
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

node_t* Make_Node (int value);
void Free_Node (node_t* node);

void Assign_Root (node_t* node);

void Insert_Node (int value);
void Remove_Node (node_t* node);

node_t* Find_Parent(int value);

void Print_Inorder (node_t* node);
void Print_Preorder (node_t* node);
void Print_Postorder (node_t* node);

// QUEUE FUNCTIONS
void Queue_Init ();
void Queue_Deinit ();
void push (node_t* node);
void push_simple (int value);
node_t* pop ();

