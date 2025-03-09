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
