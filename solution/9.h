#ifndef XORLIST_H
#define XORLIST_H
struct Node {
    int data;
    struct Node* neighbors;
};

extern struct Node* head;
extern struct Node* tail;
extern int node_count;

struct Node* Next_Node(struct Node* node, struct Node* prev);
struct Node* New_XOR_Node(int data, struct Node* neighbors);

void Insert_After(struct Node* node, struct Node* prev, int data);
void Remove_Here(struct Node* node, struct Node* prev);
void Reverse(struct Node* prev, struct Node* begin, struct Node* end, struct Node* next);

int type_0(int k);
void type_1(int data);
void type_2(int k, int data);
void type_3(int k, int data);
void type_4(int k);
void type_5(int k);
void type_6(int k);
#endif
