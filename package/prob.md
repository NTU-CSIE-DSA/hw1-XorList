## Problem Description

Doubly-linked lists are convenient, but come with two disadvantages. Firstly, two pointers are used per node instead of one, making it hard to fit small-cache/memory scenarios. Secondly, reversing a doubly-linked list typically requires swapping the `next` and `prev` pointers of every node, making it less efficient for applications with frequent reversal needs.

The XOR linked list is here for rescue! In this problem, we ask you to implement the usual doubly-linked list and the XOR linked list. The following description of the XOR linked list is quoted from [Wikipedia](https://en.wikipedia.org/wiki/XOR_linked_list): 

*An XOR linked list is a type of data structure used in computer programming. It takes advantage of the bitwise XOR operation to decrease storage requirements for doubly linked lists by storing the composition of both addresses in one field. While the composed address is not meaningful on its own, during traversal it can be combined with knowledge of the last-visited node address to deduce the address of the following node.*

### 9.h

Here is the defined header file `9.h`.

```c=
#ifndef XORLIST_H
#define XORLIST_H
struct Node {
    int data;
    struct Node* neighbors;
};

extern struct Node* head;
extern struct Node* tail;
extern int node_count, removed_count;

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
void type_6(## Problem Description

Doubly-linked lists are convenient, but come with two disadvantages. Firstly, two pointers are used per node instead of one, making it hard to fit small-cache/memory scenarios. Secondly, reversing a doubly-linked list typically requires swapping the `next` and `prev` pointers of every node, making it less efficient for applications with frequent reversal needs.

The XOR linked list is here for rescue! In this problem, we ask you to implement the usual doubly-linked list and the XOR linked list. The following description of the XOR linked list is quoted from [Wikipedia](https://en.wikipedia.org/wiki/XOR_linked_list): 

*An XOR linked list is a type of data structure used in computer programming. It takes advantage of the bitwise XOR operation to decrease storage requirements for doubly linked lists by storing the composition of both addresses in one field. While the composed address is not meaningful on its own, during traversal it can be combined with knowledge of the last-visited node address to deduce the address of the following node.*

### 9.h

Here is the defined header file `9.h`.

```c=
#ifndef XORLIST_H
#define XORLIST_H
struct Node {
    int data;
    struct Node* neighbors;
};

extern struct Node* head;
extern struct Node* tail;
extern int node_count, removed_count;

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
```

`Node` is a structure that stores the information of a node in XOR linked list. `head` and `tail` are the variables represent the head and the tail of the XOR linked list. `node_count` and `removed_count` are the variables students can utilize in the following implementation.

We provide 2 well-implemented functions for students to utilize.

```=
Next-Node(node, prev)
    return node.neighbors ⊕ prev
```

```=
New-XOR-Node(data, neighbors)
    initialize newNode
    return newNode
```

We assume `data` to be an integer that represents the number of `New-XOR-Node` calls so far. That is, the first new node will contain $data = 1$, the second new node will contain $data = 2$, and so on.

**In this problem, you need to implement 3 routines and 7 types of operations which are defined in the header file `9.h`.**

Here are the 3 routines that we ask you to implement:

```=
Insert-After(node, prev, data):
    next = Next-Node(node, prev)
    newNode = New-XOR-Node(data, next ⊕ node)
    next.neighbors = next.neighbors ⊕ node ⊕ newNode
    node.neighbors = prev ⊕ newNode
```

```=
Remove-Here(node, prev):
    next = Next-Node(node, prev)
    prev.neighbors = prev.neighbors ⊕ node ⊕ next
    next.neighbors = next.neighbors ⊕ node ⊕ prev
    Free(node)
```

```=
Reverse(prev, begin, end, next)
    prev.neighbors = prev.neighbors ⊕ begin ⊕ end
    begin.neighbors = begin.neighbors ⊕ prev ⊕ next
    end.neighbors = end.neighbors ⊕ next ⊕ prev
    next.neighbors = next.neighbors ⊕ end ⊕ begin
```

Here are 7 types of operations that we ask you to implement:

* `type_0(k)` is for printing out the $data$ field of the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_1(data)` is for calling `Insert-After` at the head of the XOR linked list, The new node will then become the first node of the linked list.
* `type_2(k, data)` is for calling `Insert-After` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $(k+1)$-th node of the linked list.
* `type_3(k, data)` is for calling `Insert-After` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $k$-th last node of the linked list.
* `type_4(k)` is for calling `Remove-Here` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_5(k)` is for calling `Remove-Here` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. 
* `type_6(k)` is for calling `Reverse` from the $k$-th node of the XOR linked list to the $k$-th last node of the XOR linked list.

----

**You should only upload the file `9.c` and do not output anything to stdout.** Otherwise, you may get unexpected error. In addition, we strongly recommend you not to modify any parts other than the annotation at the very bottom. 

### 9.c

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

struct Node* head;
struct Node* tail;
int node_count, removed_count;

struct Node* Next_Node(struct Node* node, struct Node* prev) {
    return (struct Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

struct Node* New_XOR_Node(int data, struct Node* neighbors) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->neighbors = neighbors;
    return new_node;
}

/*
Finish your implementation for the 3 routines and 7 types of operations HERE
*/
```

We will use the following command to compile your code:

`gcc 9.c main.c -std=c11 -static -O2`

We will run `main.c` to test your code.

### main.c

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

int main() {
    node_count = 1;
    removed_count = 0;
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
```


## Input

We assume initially the XOR linked list is empty. The first line includes one integers, $M$, representing the number of operation. The next $M$ lines include $2$ integers, $t$ and $k$. The first integer, $t$, represents the operation type. The second integer, $k$, represents the additional parameters for the operation.

## Output

For each type $0$ operation, print the value of the $data$ in the $k$-th node in one line.

## Constraints

* $1\leq M\leq 10^4$
* $t\in 0, 1, 2, 3, 4, 5, 6$
* if $t\in 0, 2, 3, 4, 5$, $1\leq k\leq |L|$, where $|L|$ is the current length of the XOR linked list
* if $t\in 1$, $k=0$
* if $t\in 6$, $1\leq k\leq \lceil{\frac{|L|}{2}}\rceil$, where $|L|$ is the current length of the XOR linked list
* It is ensured that if the XOR linked list is currently empty, $t\in 1$

## Subtasks

### Subtask 1 (10 pts)

* $t\in 0, 1$

### Subtask 2 (15 pts)

* $t\in 0, 1, 2$

### Subtask 3 (15 pts)

* $t\in 0, 1, 2, 3$

### Subtask 4 (20 pts)

* $t\in 0, 1, 2, 3, 4, 5$

### Subtask 5 (40 pts)

* $t\in 0, 1, 2, 3, 4, 5, 6$

## Sample Testcases

### Sample Input 1

```
6
1 0
1 0
0 1
0 2
1 0
0 3
```

### Sample Output 1


```
2
1
1
```

### Sample Input 2

```
10
1 0
2 1
3 2
2 3
3 1
0 1
0 2
0 3
0 4
0 5
```

### Sample Output 2

```
1 
3 
2 
4 
5
```

### Sample Input 3

```
11
1 0
2 1
3 2
2 3
3 1
6 2
4 1
5 3
0 1
0 2
0 3
```

### Sample Output 3

```
4
3
5
```

## Hints

### Sample 1 Explanation

After completing first two type_1 operations, the `data` of the XOR linked list's nodes are:

$2\rightarrow 1$

After completing the last type_1 operation, the `data` of the XOR linked list's become:

$3\rightarrow 2\rightarrow 1$

where the leftmost value refers to the `data` of the first node.

### Sample 3 Explanation

After completing the type_6 operation, , the `data` of the XOR linked list's become:

$1\rightarrow 4\rightarrow 2\rightarrow 3\rightarrow 5$

After completing the type_4 and type_6 operations, the `data` of the XOR linked list's become:

$4\rightarrow 3\rightarrow 5$int k);
#endif
```

`Node` is a structure that stores the information of a node in XOR linked list. `head` and `tail` are the variables represent the head and the tail of the XOR linked list. `node_count` and `removed_count` are the variables students can utilize in the following implementation.

We provide 2 well-implemented functions for students to utilize.

```=
Next-Node(node, prev)
    return node.neighbors ⊕ prev
```

```=
New-XOR-Node(data, neighbors)
    initialize newNode
    return newNode
```

We assume `data` to be an integer that represents the number of `New-XOR-Node` calls so far. That is, the first new node will contain $data = 1$, the second new node will contain $data = 2$, and so on.

**In this problem, you need to implement 3 routines and 7 types of operations which are defined in the header file `9.h`.**

Here are the 3 routines that we ask you to implement:

```=
Insert-After(node, prev, data):
    next = Next-Node(node, prev)
    newNode = New-XOR-Node(data, next ⊕ node)
    next.neighbors = next.neighbors ⊕ node ⊕ newNode
    node.neighbors = prev ⊕ newNode
```

```=
Remove-Here(node, prev):
    next = Next-Node(node, prev)
    prev.neighbors = prev.neighbors ⊕ node ⊕ next
    next.neighbors = next.neighbors ⊕ node ⊕ prev
    Free(node)
```

```=
Reverse(prev, begin, end, next)
    prev.neighbors = prev.neighbors ⊕ begin ⊕ end
    begin.neighbors = begin.neighbors ⊕ prev ⊕ next
    end.neighbors = end.neighbors ⊕ next ⊕ prev
    next.neighbors = next.neighbors ⊕ end ⊕ begin
```

Here are 7 types of operations that we ask you to implement:

* `type_0(k)` is for printing out the $data$ field of the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_1(data)` is for calling `Insert-After` at the head of the XOR linked list, The new node will then become the first node of the linked list.
* `type_2(k, data)` is for calling `Insert-After` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $(k+1)$-th node of the linked list.
* `type_3(k, data)` is for calling `Insert-After` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $k$-th last node of the linked list.
* `type_4(k)` is for calling `Remove-Here` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_5(k)` is for calling `Remove-Here` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. 
* `type_6(k)` is for calling `Reverse` from the $k$-th node of the XOR linked list to the $k$-th last node of the XOR linked list.

----

**You should only upload the file `9.c` and do not output anything to stdout.** Otherwise, you may get unexpected error. In addition, we strongly recommend you not to modify any parts other than the annotation at the very bottom. 

### 9.c

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

struct Node* head;
struct Node* tail;
int node_count, removed_count;

struct Node* Next_Node(struct Node* node, struct Node* prev) {
    return (struct Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev);
}

struct Node* New_XOR_Node(int data, struct Node* neighbors) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->neighbors = neighbors;
    return new_node;
}

/*
Finish your implementation for the 3 routines and 7 types of operations HERE
*/
```

We will use the following command to compile your code:

`gcc 9.c main.c -std=c11 -static -O2`

We will run `main.c` to test your code.

### main.c

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

int main() {
    node_count = 1;
    removed_count = 0;
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
```

## Input

We assume initially the XOR linked list is empty. The first line includes one integers, $M$, representing the number of operation. The next $M$ lines include $2$ integers, $t$ and $k$. The first integer, $t$, represents the operation type. The second integer, $k$, represents the additional parameters for the operation.

## Output

For each type $0$ operation, print the value of the $data$ in the $k$-th node in one line.

## Constraints

* $1\leq M\leq 10^4$
* $t\in 0, 1, 2, 3, 4, 5, 6$
* if $t\in 0, 2, 3, 4, 5$, $1\leq k\leq |L|$, where $|L|$ is the current length of the XOR linked list
* if $t\in 1$, $k=0$
* if $t\in 6$, $1\leq k\leq \lceil{\frac{|L|}{2}}\rceil$, where $|L|$ is the current length of the XOR linked list
* It is ensured that if the XOR linked list is currently empty, $t\in 1$

## Subtasks

### Subtask 1 (10 pts)

* $t\in 0, 1$

### Subtask 2 (15 pts)

* $t\in 0, 1, 2$

### Subtask 3 (15 pts)

* $t\in 0, 1, 2, 3$

### Subtask 4 (20 pts)

* $t\in 0, 1, 2, 3, 4, 5$

### Subtask 5 (40 pts)

* $t\in 0, 1, 2, 3, 4, 5, 6$

## Sample Testcases

### Sample Input 1

### Sample Output 1

### Sample Input 2

### Sample Output 2

### Sample Input 3

### Sample Output 3

## Hints

