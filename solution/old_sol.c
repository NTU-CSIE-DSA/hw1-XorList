#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node {
    int data;
    struct Node* neighbors;
};

struct Node* head = NULL;
struct Node* tail = NULL;
int node_counter = 0;

struct Node* Next_Node(struct Node* node, struct Node* prev) {
    return (struct Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

struct Node* New_XOR_Node(struct Node* npx) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) return NULL;
    new_node->data = ++node_counter;
    new_node->neighbors = npx;
    return new_node;
}

void Insert_After(struct Node* node, struct Node* prev, int data) {
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
    if (!node) return;
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
    if (!begin || !end || begin == end) return;
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

struct Node* get_kth_node(struct Node* start, int k) {
    if (k < 1 || !start) return NULL;
    
    struct Node* curr = start;
    struct Node* prev = NULL;
    struct Node* next;
    int count = 1;
    
    while (curr && count < k) {
        next = Next_Node(curr, prev);
        prev = curr;
        curr = next;
        count++;
    }
    
    return curr;
}

struct Node* get_kth_last_node(struct Node* start, int k) {
    if (k < 1 || !start) return NULL;
    
    int length = 0;
    struct Node* curr = start;
    struct Node* prev = NULL;
    struct Node* next;
    
    while (curr != NULL) {
        length++;
        next = Next_Node(curr, prev);
        prev = curr;
        curr = next;
    }
    
    if (k > length) return NULL;
    return get_kth_node(start, length - k + 1);
}

int main() {
    int M;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        int t, k;
        scanf("%d %d", &t, &k);
        switch(t) {
            case 0: {
                struct Node* node = get_kth_node(head, k);
                if (node) printf("%d\n", node->data);
                break;
            }
            
            case 1: {
                if (!head) {
                    head = New_XOR_Node(NULL);
                    tail = head;
                } else {
                    struct Node* old_head = head;
                    head = New_XOR_Node((struct Node*)(uintptr_t)old_head);
                    old_head->neighbors = (struct Node*)((uintptr_t)old_head->neighbors ^ (uintptr_t)head);
                }
                break;
            }
            
            case 2: {
                if(k==0) {
                    if (!head) {
                        head = New_XOR_Node(NULL);
                        tail = head;
                    } else {
                        struct Node* old_head = head;
                        head = New_XOR_Node((struct Node*)(uintptr_t)old_head);
                        old_head->neighbors = (struct Node*)((uintptr_t)old_head->neighbors ^ (uintptr_t)head);
                    }
                }
                else {
                    struct Node* node = get_kth_node(head, k);
                    if (node) {
                        struct Node* prev = k == 1 ? NULL : get_kth_node(head, k-1);
                        Insert_After(node, prev, 0);
                    }
                }
                break;
            }
            
            case 3: {
                struct Node* node = get_kth_last_node(head, k);
                if (node) {
                    struct Node* prev = get_kth_last_node(head, k+1);
                    Insert_After(node, prev, 0);
                }
                break;
            }
            
            case 4: {
                if (k == 1) {
                    Remove_Here(head, NULL);
                } else {
                    struct Node* prev = get_kth_node(head, k-1);
                    if (prev) {
                        struct Node* node = Next_Node(prev, get_kth_node(head, k-2));
                        if (node) Remove_Here(node, prev);
                    }
                }
                break;
            }
            
            case 5: {
                struct Node* node = get_kth_last_node(head, k);
                if (node) {
                    struct Node* prev = get_kth_last_node(head, k+1);
                    Remove_Here(node, prev);
                }
                break;
            }
            
            case 6: {
                struct Node* begin = get_kth_node(head, k);
                struct Node* end = get_kth_last_node(head, k);
                if (begin && end) {
                    struct Node* prev = k == 1 ? NULL : get_kth_node(head, k-1);
                    struct Node* next = Next_Node(end, get_kth_last_node(head, k+1));
                    Reverse(prev, begin, end, next);
                }
                break;
            }
        }
        struct Node* curr=head;
        struct Node* prev=NULL;
        struct Node* next;
        while(curr!=NULL) {
            printf("%d ", curr->data);
            next=Next_Node(curr, prev);
            prev=curr;
            curr=next;
        }
        printf("\n");
    }
    
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;
    
    while (curr != NULL) {
        next = Next_Node(curr, prev);
        free(curr);
        prev = curr;
        curr = next;
    }
    
    return 0;
}
