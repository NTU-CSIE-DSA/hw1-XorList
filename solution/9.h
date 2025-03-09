#ifndef XORLIST_H
#define XORLIST_H
#include <stdint.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* neighbors;
};

extern struct Node* head;
extern struct Node* tail;
extern int next_node_id;

static inline struct Node* Next_Node(struct Node* node, struct Node* prev) {
    return (struct Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

static inline struct Node* New_XOR_Node(struct Node* neighbors) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = next_node_id++;
    new_node->neighbors = neighbors;
    return new_node;
}

void Insert_After(struct Node* node, struct Node* prev);
void Remove_Here(struct Node* node, struct Node* prev);
void Reverse(struct Node* prev, struct Node* begin, struct Node* end, struct Node* next);

int type_0(int k);
void type_1();
void type_2(int k);
void type_3(int k);
void type_4(int k);
void type_5(int k);
void type_6(int k);

#endif