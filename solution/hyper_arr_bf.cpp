#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define uip uintptr_t

typedef struct Node {
    int data;
    struct Node* neighbors;
} Node;

Node* head = NULL;
Node* tail = NULL;
int node_count = 1, removed_count = 0;

Node* Next_Node(Node* node, Node* prev) {
    return (Node*)((uip)node->neighbors ^ (uip)prev);
}

Node* New_XOR_Node(int data, Node* neighbors) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->neighbors = neighbors;
    return new_node;
}

void Insert_After(Node* node, Node* prev, int data) {
    if (!head) {
        head = New_XOR_Node(data, NULL);
        tail = head;
        return;
    }
    if (!node) {
        Node* temp = head;
        head = New_XOR_Node(data, (Node*)((uip)temp));
        temp->neighbors = (Node*)((uip)temp->neighbors ^ (uip)head);
        return;
    }
    Node* next = Next_Node(node, prev);
    Node* newNode = New_XOR_Node(data, (Node*)((uip)next ^ (uip)node));
    if (next) {
        next->neighbors = (Node*)((uip)next->neighbors ^ (uip)node ^ (uip)newNode);
    } else {
        tail = newNode;
    }
    node->neighbors = (Node*)((uip)prev ^ (uip)newNode);
}

void Remove_Here(Node* node, Node* prev) {
    Node* next = Next_Node(node, prev);
    if (node == head) {
        head = next;
    }
    if (node == tail) {
        tail = prev;
    }
    if (prev) {
        prev->neighbors = (Node*)((uip)prev->neighbors ^ (uip)node ^ (uip)next);
    }
    if (next) {
        next->neighbors = (Node*)((uip)next->neighbors ^ (uip)node ^ (uip)prev);
    }
    free(node);
}

void Reverse(Node* prev, Node* begin, Node* end, Node* next) {
    if (begin == end) return;
    if (begin == head) head = end;
    if (end == tail) tail = begin;
    if (prev) {
        prev->neighbors = (Node*)((uip)prev->neighbors ^ (uip)begin ^ (uip)end);
    }
    begin->neighbors = (Node*)((uip)begin->neighbors ^ (uip)prev ^ (uip)next);
    end->neighbors = (Node*)((uip)end->neighbors ^ (uip)next ^ (uip)prev);
    if (next) {
        next->neighbors = (Node*)((uip)next->neighbors ^ (uip)end ^ (uip)begin);
    }
}

void Reverse_All() {
    Node* temp = head;
    head = tail;
    tail = temp;
}

void find_k(int k, Node** curr, Node** prev) {
    if (k == 0) {
        *curr = *prev = NULL;
        return;
    }
    *curr = head;
    *prev = NULL;
    Node* next;
    int count = 1;
    while (*curr && count < k) {
        next = Next_Node(*curr, *prev);
        *prev = *curr;
        *curr = next;
        count++;
    }
}

#define MN 1000005
int arr[MN], sz = 0;

int type_0(int k) {
    return arr[k];
}

void type_1(int data) {
    for(int i=sz; i>=1; --i) arr[i+1] = arr[i];
    arr[1] = data;
    ++sz;
}

void type_2(int k, int data) {
    for(int i=sz; i>=k+1; --i) arr[i+1] = arr[i];
    arr[k+1] = data;
    ++sz;
}

void type_3(int k, int data) {
    for(int i=0; i<k-1; ++i) arr[sz-i+1] = arr[sz-i];
    arr[sz-k+2] = data;
    ++sz;
}

void type_4(int k) {
    for(int i=k; i<sz; ++i) arr[i] = arr[i+1];
    --sz;
}

void type_5(int k) {
    for(int i=sz-k+1; i<sz; ++i) arr[i] = arr[i+1];
    --sz;
}

#define swap(a, b) {int t = a; a = b; b = t;}
void type_6(int k) {
    int temp[MN];
    for(int i=0; i<(sz-2*k+2)/2; ++i) swap(arr[k+i], arr[sz-k-i+1]);
}

int main() {
    int M;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        int t, k;
        scanf("%d %d", &t, &k);
        switch (t) {
            case 0: {
                printf("%d\n", type_0(k));
                break;
            }
            case 1: {
                type_1(node_count++);
                break;
            }
            case 2: {
                type_2(k, node_count++);
                break;
            }
            case 3: {
                type_3(k, node_count++);
                break;
            }
            case 4: {
                type_4(k);
                removed_count++;
                break;
            }
            case 5: {
                type_5(k);
                removed_count++;
                break;
            }
            case 6: {
                type_6(k);
                break;
            }
        }
    }
    Node* curr = head;
    Node* prev = NULL;
    Node* next;
    while (curr != NULL) {
        next = Next_Node(curr, prev);
        free(curr);
        prev = curr;
        curr = next;
    }
    return 0;
}
