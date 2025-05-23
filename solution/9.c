#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

struct Node* head;
struct Node* tail;
int next_node_id;

void Insert_After(struct Node* node, struct Node* prev) {
    struct Node* next = Next_Node(node, prev);
    struct Node* newNode = New_XOR_Node((struct Node*)((uintptr_t)next ^ (uintptr_t)node));
    if (next) {
        next->neighbors = (struct Node*)((uintptr_t)next->neighbors ^ (uintptr_t)node ^ (uintptr_t)newNode);
    } else {
        tail = newNode;
    }
    node->neighbors = (struct Node*)((uintptr_t)prev ^ (uintptr_t)newNode);
}

void Remove_Here(struct Node* node, struct Node* prev) {
    struct Node* next = Next_Node(node, prev);
    if (node == head) {
        head = next;
    }
    if (node == tail) {
        tail = prev;
    }
    if (prev) {
        prev->neighbors = (struct Node*)((uintptr_t)prev->neighbors ^ (uintptr_t)node ^ (uintptr_t)next);
    }
    if (next) {
        next->neighbors = (struct Node*)((uintptr_t)next->neighbors ^ (uintptr_t)node ^ (uintptr_t)prev);
    }
    free(node);
}

void Reverse(struct Node* prev, struct Node* begin, struct Node* end, struct Node* next) {
    if (begin == end) return;
    if (begin == head) head = end;
    if (end == tail) tail = begin;
    if (prev) {
        prev->neighbors = (struct Node*)((uintptr_t)prev->neighbors ^ (uintptr_t)begin ^ (uintptr_t)end);
    }
    begin->neighbors = (struct Node*)((uintptr_t)begin->neighbors ^ (uintptr_t)prev ^ (uintptr_t)next);
    end->neighbors = (struct Node*)((uintptr_t)end->neighbors ^ (uintptr_t)next ^ (uintptr_t)prev);
    if (next) {
        next->neighbors = (struct Node*)((uintptr_t)next->neighbors ^ (uintptr_t)end ^ (uintptr_t)begin);
    }
}

int type_0(int k) {
	struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;
    int count = 1;
    
    while (curr && count < k) {
        next = Next_Node(curr, prev);
        prev = curr;
        curr = next;
        count++;
    }
	return curr->data;
}

void type_1() {
	if (!head) {
		head = New_XOR_Node(NULL);
		tail = head;
	} else {
		struct Node* old_head = head;
		head = New_XOR_Node((struct Node*)(uintptr_t)old_head);
		old_head->neighbors = (struct Node*)((uintptr_t)old_head->neighbors ^ (uintptr_t)head);
	}
}

void type_2(int k) {
	struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;
    int count = 1;
    while (curr && count < k) {
        next = Next_Node(curr, prev);
        prev = curr;
        curr = next;
        count++;
    }
	Insert_After(curr, prev);
}

void type_3(int k) {
	struct Node* curr = tail;
    struct Node* next = NULL;
    struct Node* prev;
    int count = 1;
    while (curr && count < k) {
        prev = Next_Node(curr, next);
        next = curr;
        curr = prev;
        count++;
    }
	prev = Next_Node(curr, next);
	Insert_After(curr, prev);
}

void type_4(int k) {
	struct Node* curr = head;
	struct Node* prev = NULL;
	struct Node* next;
	int count = 1;	
	while (curr && count < k) {
		next = Next_Node(curr, prev);
		prev = curr;
		curr = next;
		count++;
	}
	Remove_Here(curr, prev);
}

void type_5(int k) {
	struct Node* curr = tail;
    struct Node* next = NULL;
    struct Node* prev;
    int count = 1;
    while (curr && count < k) {
        prev = Next_Node(curr, next);
        next = curr;
        curr = prev;
        count++;
    }
	prev = Next_Node(curr, next);
	Remove_Here(curr, prev);
}

void type_6(int k) {
	struct Node* begin = head;
	struct Node* prev = NULL;
    struct Node* curr;
    int count = 1;
    while (begin && count < k) {
        curr = Next_Node(begin, prev);
        prev = begin;
        begin = curr;
        count++;
    }
	count = 1;
	struct Node* end = tail;
    struct Node* next = NULL;
    while (end && count < k) {
        curr = Next_Node(end, next);
        next = end;
        end = curr;
        count++;
    }
	Reverse(prev, begin, end, next);
}
