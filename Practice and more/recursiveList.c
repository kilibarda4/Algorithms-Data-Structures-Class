#include <stdio.h>

//regular printing LL
// void printLL(nodePT L) {
//     nodePT curr = L;

//     while(curr != NULL) {
//         printf("%d", curr->data);
//         curr = curr->next;
//     }
// }


//printing Linked List recursively
void printLLRec(nodePT L) {
    if (L == NULL) return;

    printf("%d", L->data);

    printLLRec(L->next);
}

//printing Linked List in reverse
void printLLRec(nodePT L) {
    if (L == NULL) return;

    printLLRec(L->next);

    printf("%d", L->data);
}


// Linked List --- 4 - 5 - 6
// Output: 457
// Solution: get to the member which has the next field == NULL, then increment its data field

// void add1(nodePT L) {
//     nodePT curr = L;
//     while(curr->next != NULL) {
//         curr = curr->next;
//     }
//     curr->data = curr->data + 1;
//     return L;
// }