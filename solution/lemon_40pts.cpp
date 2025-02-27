#include "9.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Node *head;
struct Node *tail;
int node_count, removed_count;

struct Node *Next_Node(struct Node *node, struct Node *prev) {
  return (struct Node *)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

struct Node *New_XOR_Node(int data, struct Node *neighbors) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->neighbors = neighbors;
  return new_node;
}

/*
Finish your implementation for the 3 routines and 7 types of operations HERE
*/

void Insert_After(struct Node *node, struct Node *prev, int data) {
  // fprintf(stderr, "Insert_After: %d %d\n", (uintptr_t)node, (uintptr_t)prev);
  struct Node *next = Next_Node(node, prev);
  struct Node *newNode =
      New_XOR_Node(data, (struct Node *)((uintptr_t)next ^ (uintptr_t)node));
  if (next != NULL)
    next->neighbors = (struct Node *)((uintptr_t)next->neighbors ^
                                      (uintptr_t)node ^ (uintptr_t)newNode);
  node->neighbors = (struct Node *)((uintptr_t)prev ^ (uintptr_t)newNode);
  if (next == NULL) {
    tail = newNode;
    fprintf(stderr, "TEST\n");
  }
  // fprintf(stderr, "Head: %d, Tail: %d\n", (uintptr_t)head, (uintptr_t)tail);
}
void Remove_Here(struct Node *node, struct Node *prev) {
  struct Node *next = Next_Node(node, prev);
  if (node == tail)
    tail = prev;
  if (node == head)
    head = next;
  if (prev != NULL)
    prev->neighbors = (struct Node *)((uintptr_t)prev->neighbors ^
                                      (uintptr_t)node ^ (uintptr_t)next);
  if (next != NULL)
    next->neighbors = (struct Node *)((uintptr_t)next->neighbors ^
                                      (uintptr_t)node ^ (uintptr_t)prev);
  free(node);
}
void Reverse(struct Node *prev, struct Node *begin, struct Node *end,
             struct Node *next) {
  if (prev != NULL)
    prev->neighbors = (struct Node *)((uintptr_t)prev->neighbors ^
                                      (uintptr_t)begin ^ (uintptr_t)end);
  if (begin != NULL)
    begin->neighbors = (struct Node *)((uintptr_t)begin->neighbors ^
                                       (uintptr_t)prev ^ (uintptr_t)next);
  if (end != NULL)
    end->neighbors = (struct Node *)((uintptr_t)end->neighbors ^
                                     (uintptr_t)next ^ (uintptr_t)prev);
  if (next != NULL)
    next->neighbors = (struct Node *)((uintptr_t)next->neighbors ^
                                      (uintptr_t)end ^ (uintptr_t)begin);
  if (prev == NULL)
    head = end;
  if (next == NULL)
    tail = begin;
}

int type_0(int k) {
  struct Node *prev = NULL;
  struct Node *curr = head;
  for (int i = 1; i < k; ++i) {
    struct Node *temp = curr;
    curr = Next_Node(curr, prev);
    prev = temp;
  }
  return curr->data;
}
void type_1(int data) {
  struct Node *newNode = New_XOR_Node(data, (struct Node *)((uintptr_t)head));
  if (head != NULL)
    head->neighbors =
        (struct Node *)((uintptr_t)head->neighbors ^ (uintptr_t)newNode);
  head = newNode;
  if (tail == NULL)
    tail = newNode;
}
void type_2(int k, int data) {
  struct Node *prev = NULL;
  struct Node *curr = head;
  for (int i = 1; i < k; ++i) {
    struct Node *temp = curr;
    curr = Next_Node(curr, prev);
    prev = temp;
  }
  Insert_After(curr, prev, data);
}
void type_3(int k, int data) {
  --k;
  Reverse(NULL, head, tail, NULL);
  if (!k)
    type_1(data);
  else
    type_2(k, data);
  Reverse(NULL, head, tail, NULL);
}
void type_4(int k) {}
void type_5(int k) {}
void type_6(int k) {}
