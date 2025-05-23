#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node {
    int data;
    struct Node* neighbors;
};

struct Node* head = NULL;
struct Node* tail = NULL;
int next_node_id=1;

struct Node* Next_Node(struct Node* node, struct Node* prev) {
    return (struct Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

struct Node* New_XOR_Node(struct Node* neighbors) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = next_node_id++;
    new_node->neighbors = neighbors;
    return new_node;
}

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

int main() {
    int M;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        int t, k;
        scanf("%d %d", &t, &k);
        switch(t) {
            case 0: {
				printf("%d\n", type_0(k));
				break;
            }
            case 1: {
                type_1();
                break;
            }
            case 2: {
				type_2(k);
                break;
            }
            case 3: {
				type_3(k);
                break;
            }
            case 4: {
				type_4(k);
                break;
            }
            case 5: {
				type_5(k);
                break;
            }
            case 6: {
				type_6(k);
                break;
            }
        }
		/*struct Node* curr = tail;
		struct Node* next = NULL;
		struct Node* prev;
		if(tail!=NULL) printf("%d\n", tail->data);
		while (curr != NULL) {
			printf("%d ", curr->data);
			prev = Next_Node(curr, next);
			next = curr;
			curr = prev;
		}
		printf("\n");*/
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
