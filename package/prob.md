## Problem Description

Doubly-linked lists are convenient, but come with two disadvantages. Firstly, two pointers are used per node instead of one, making it hard to fit small-cache/memory scenarios. Secondly, reversing a doubly-linked list typically requires swapping the `next` and `prev` pointers of every node, making it less efficient for applications with frequent reversal needs.

The XOR linked list is here for rescue! In this problem, we ask you to implement the usual doubly-linked list and the XOR linked list. The following description of the XOR linked list is quoted from [Wikipedia](https://en.wikipedia.org/wiki/XOR_linked_list): 

*An XOR linked list is a type of data structure used in computer programming. It takes advantage of the bitwise XOR operation to decrease storage requirements for doubly linked lists by storing the composition of both addresses in one field. While the composed address is not meaningful on its own, during traversal it can be combined with knowledge of the last-visited node address to deduce the address of the following node.*

### Provided Files

* Header file `9.h`:

```c=
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
```

* Skeleton source file `9.c`:

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

struct Node* head;
struct Node* tail;
int next_node_id;

/*
Finish your implementation for the 3 routines and 7 types of operations HERE
*/
```

* Main source file `main.c`:

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "9.h"

int main() {
    next_node_id = 1;
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

Your goal is to complete `9.c`. Then, we will use the following command to compile your code:

`gcc 9.c main.c -std=c11 -static -O2`

where `9.c` is your submitted code, and `main.c` and `9.h` are the exact same ones that you fetched from NTU COOL or judge. Note that you should only push `9.c` to the judge system.

The header file `9.h` contains the implementation of 2 utility functions as well as the signatures of 3 routines and 7 types of operations. All functions are based on the `Node` structure that stores the information of a node in the XOR linked list. The external variables `head` and `tail` represent the head and the tail of the XOR linked list, respectively. Their actual declarations are given in `9.c`. 

The two utility functions that are implemented and can be directly used are

```=
Next-Node(node, prev)
    return node.neighbors ⊕ prev
```

```=
New-XOR-Node(neighbors)
    initialize newNode with data and neighbors
    return newNode
```

To simplify the implementation logistics, we assume that $data$ will be assigned to a sequential ID that represents the number of calls to `New-XOR-Node` calls so far. The next ID is stored in an external variable called $next\_node\_id$, whose actual declaration is given in `9.c`.

We assume $data$ to be an integer that represents the number of `New-XOR-Node` calls so far. That is, the first new node will contain $data = 1$, the second new node will contain $data = 2$, and so on.

In `9.c`, you need to implement 3 routines and 7 types of operations, as declared in `9.h`. The 3 routines are

* The $O(1)$-time `Insert-After(node, prev)` is for inserting a node `newNode` after the node `node`, where `prev` is the previous node of `node`.

```=
Insert-After(node, prev):
    next = Next-Node(node, prev)
    newNode = New-XOR-Node(next ⊕ node)
    next.neighbors = next.neighbors ⊕ node ⊕ newNode
    node.neighbors = prev ⊕ newNode
```

* The $O(1)$-time `Remove-Here(node, prev)` is for removing the node `node`, where `prev` is the previous node of `node`.

```=
Remove-Here(node, prev):
    next = Next-Node(node, prev)
    prev.neighbors = prev.neighbors ⊕ node ⊕ next
    next.neighbors = next.neighbors ⊕ node ⊕ prev
    Free(node)
```

* The $O(1)$-time `Reverse(prev, begin, end, next)` is for reversing all the nodes in range `[begin, end]`, where `prev` is the previous node of `begin` and `next` is the next node of `end`.

```=
Reverse(prev, begin, end, next)
    prev.neighbors = prev.neighbors ⊕ begin ⊕ end
    begin.neighbors = begin.neighbors ⊕ prev ⊕ next
    end.neighbors = end.neighbors ⊕ next ⊕ prev
    next.neighbors = next.neighbors ⊕ end ⊕ begin
```

After completing the 3 routines, you can then use them to implement the 7 types of operations below.

* `type_0(k)` prints out the $data$ field of the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_1()` calls `Insert-After` at the head of the XOR linked list, The new node will then become the first node of the linked list.
* `type_2(k)` calls `Insert-After` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $(k+1)$-th node of the linked list.
* `type_3(k)` calls `Insert-After` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. The new node will then become the $k$-th last node of the linked list.
* `type_4(k)` calls `Remove-Here` at the $k$-th node of the XOR linked list, where $k$ is $1$-indexed.
* `type_5(k)` calls `Remove-Here` at the $k$-th last node of the XOR linked list, where $k$ is $1$-indexed. 
* `type_6(k)` calls `Reverse` from the $k$-th node of the XOR linked list to the $k$-th last node of the XOR linked list.

The file `main.c` is the actual program entrance that will be used to test your code. It contains input processing and calls to the 7 types of operations. You do not need to change anything in `main.c`. 

We will only use the `9.c` that you pushed to the judge system to test your code. Therefore, you are strongly suggested not to change `9.h` and `main.c` at all. In addition, you do not need to do any outputting within `9.c`. Otherwise you risk being misjudged by the system.

## Input

We assume initially the XOR linked list is empty. The first line includes one integers, $M$, representing the number of operation. The next $M$ lines include $2$ integers, $t$ and $k$. The first integer, $t$, represents the operation type. The second integer, $k$, represents the additional parameters for the operation.

## Output

For each type $0$ operation, print the value of the $data$ in the $k$-th node in one line.

## Constraints

* $1\leq M\leq 5\times 10^5$
* $t\in \{0, 1, 2, 3, 4, 5, 6\}$
* For all $t\in \{0, 2, 3, 4, 5\}$, $1\leq k\leq |L|$, where $|L|$ is the current length of the XOR linked list
* For all $t\in \{1\}$, $k=0$
* For all $t\in \{6\}$, $1\leq k\leq \lceil{\frac{|L|}{2}}\rceil$, where $|L|$ is the current length of the XOR linked list
* We ensure that if the XOR linked list is currently empty, $t\in 1$
* $\sum k\leq 5\times 10^7$

## Subtasks

### Subtask 1 (10 pts)

* $t\in$ {$0, 1$}

### Subtask 2 (15 pts)

* $t\in$ {$0, 1, 2$}

### Subtask 3 (15 pts)

* $t\in$ {$0, 1, 2, 3$}

### Subtask 4 (20 pts)

* $t\in$ {$0, 1, 2, 3, 4, 5$}

### Subtask 5 (40 pts)

No other constraints.

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

After completing first two `type_1` operations, the `data` of the XOR linked list's nodes are:

$2\rightarrow 1$

After completing the last `type_1` operation, the `data` of the XOR linked list's become:

$3\rightarrow 2\rightarrow 1$

where the leftmost value refers to the `data` of the first node.

### Sample 3 Explanation

After completing the `type_6` operation, the `data` of the XOR linked list's become:

$1\rightarrow 4\rightarrow 2\rightarrow 3\rightarrow 5$

After completing the `type_4` and `type_6` operations, the `data` of the XOR linked list's become:

$4\rightarrow 3\rightarrow 5$