#ifndef SDIZO_2_MERGESORT_H
#define SDIZO_2_MERGESORT_H

#include "LinkedList.h"

template <typename T>
Node<T>* sortedMerge(Node<T>* a, Node<T>* b);

template <typename T>
void split(Node<T>* source,
           Node<T>** front, Node<T>** back);

/* sorts the linked l
 * ist by changing next pointers (not data) */
template <typename T>
void mergeSort(Node<T>** headRef) {

    Node<T>* head = *headRef;

    // end recursion if len 0 or 1
    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    Node<T>* a;
    Node<T>* b;

    // split list into a and b
    split(head, &a, &b);

    // sort split lists
    mergeSort(&a);
    mergeSort(&b);

    // merge sorted lists
    *headRef = sortedMerge(a, b);
}

template <typename T>
Node<T>* sortedMerge(Node<T>* a, Node<T>* b) {
    if (a == nullptr)
        return (b);
    else if (b == nullptr)
        return (a);

    Node<T>* result;

    // recur for node with smaller data
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);
}

// TODO change comment, refactor
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
template <typename T>
void split(Node<T>* source, Node<T>** front, Node<T>** back) {
    Node<T>* fast;
    Node<T>* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

template <typename T>
void mergeSort(LinkedList<T>* list) {
    Node<T>* head = list->getHeadNode();

    // if empty or contains one return
    if (head == nullptr || head->next == nullptr) return;

    mergeSort(&head);

    // restore prev pointers and tail
    Node<T>* temp = head->next;
    Node<T>* prev = head;
    head->prev = nullptr;

    while (temp->next != nullptr) {
        temp->prev = prev;
        prev = temp;
        temp = temp->next;
    }

    list->set(head, temp);
}

#endif //SDIZO_2_MERGESORT_H
