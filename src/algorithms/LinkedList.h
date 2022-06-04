#ifndef SDIZO_2_LINKEDLIST_H
#define SDIZO_2_LINKEDLIST_H

#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node* next;
    Node* prev;

    Node(T object, Node* nextNode, Node* prevNode){
        data = object;
        next = nextNode;
        prev = prevNode;
    }
};

template <typename T>
class LinkedList {
private:
    // first node
    Node<T>* head;
    // last node
    Node<T>* tail;

public:
    LinkedList();

    ~LinkedList();

    // True if empty
    bool isEmpty();

    // Returns size (number of nodes)
    int size();

    // Adds element to the back
    void pushBack(T val);

    // Adds element to the front
    void pushFront(T val);

    // Inserts element on a given index
    bool insert(T val, int index);

    // Returns true if value is in list
    bool contains(T val);

    // Removes first element
    bool pop_head();

    // Removes last element
    bool pop_tail();

    // Clears all elements of the list
    void clear();

    // Returns true if object with index was deleted, false if index out of range
    bool remove(int index);

    // Removes first occurrence of a value. Returns true if value was deleted, false if value not found
    bool removeValue(T value);

    // Sets list from start to end
    void set(Node<T>* start, Node<T>* end);

    // Returns item T at a given index
    T get(int index);

    // Returns first node of the list
    Node<T>* getHeadNode();

    // String representation from head to tail
    std::string toString();
};

template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty(){
    return head == nullptr;
}

template <typename T>
int LinkedList<T>::size(){
    if(isEmpty()) return 0;

    int currentSize = 0;
    Node<T>* currentNode = head;
    do{
        currentNode = currentNode->next;
        currentSize++;
    }
    while(currentNode != nullptr);
    return currentSize;
}

template <typename T>
void LinkedList<T>::pushBack(T val){
    //Create new node if list is empty
    if(isEmpty()) {
        head = new Node<T>(val, nullptr, nullptr);
        tail = head;
    }
    else{
        //link new node to the last one
        tail->next = new Node<T>(val, nullptr, tail);
        tail = tail->next;
    }
}

template <typename T>
void LinkedList<T>::pushFront(T val) {
    if(isEmpty()){
        head = new Node<T>(val, nullptr, nullptr);
        tail = head;
    }
    else{
        head->prev = new Node<T>(val, head, nullptr);
        head = head->prev;
    }
}

template <typename T>
bool LinkedList<T>::insert(T val, int index) {
    if(index < 0) return false;
    if(index == 0) {
        pushFront(val);
        return true;
    }
    //return false if list is empty and given index != 0
    if(isEmpty()) return false;

    //search index
    int currentIndex = 1;
    Node<T>* currentNode = head;
    while(currentNode->next != nullptr){
        //if found node
        if(currentIndex == index){
            Node<T>* newNode = new Node<T>(val, currentNode->next, currentNode);
            //set nodes in next and prev nodes
            newNode->prev->next = newNode;
            newNode->next->prev = newNode;
            return true;
        }
        currentIndex++;
        currentNode = currentNode->next;
    }

    //if index==size (same as pushBack)
    if(currentNode == tail){
        //link new node to the last one
        tail->next = new Node<T>(val, nullptr, tail);
        tail = tail->next;
        return true;
    }

    //node not found
    cout << "index out of range" << std::endl;
    return false;
}

template <typename T>
bool LinkedList<T>::contains(T val) {
    if(isEmpty()) return false;

    Node<T>* currentNode = head;
    do{
        if(currentNode->data == val) return true;
        currentNode = currentNode->next;
    }
    while(currentNode != nullptr);
    //value not found
    return false;
}

template <typename T>
bool LinkedList<T>::pop_head() {
    if(isEmpty()){
        return false;
    }
    Node<T>* oldNode = head;
    head = head->next;
    delete oldNode;
    if(head != nullptr) head->prev = nullptr;
    else tail = head;
    return true;
}

template <typename T>
bool LinkedList<T>::pop_tail() {
    if(isEmpty()){
        return false;
    }

    Node<T>* oldNode = tail;
    tail = tail->prev;
    delete oldNode;
    if(tail != nullptr) tail->next = nullptr;
    else head = tail;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(int index){
    if(isEmpty() || index < 0) return false;
    if(index == 0) return pop_head();

    Node<T>* currentNode = head->next;
    int currentIndex = 1;
    while(currentNode != nullptr){
        if(index == currentIndex){
            Node<T>* nextNode = currentNode->next;
            Node<T>* prevNode = currentNode->prev;

            //if node to remove is the tail
            if(nextNode == nullptr) this->tail = prevNode;
                //else
            else nextNode->prev = prevNode;

            //if note to remove is the head
            if(prevNode == nullptr) this->head = nextNode;
                //else
            else prevNode->next = nextNode;

            delete currentNode;
            return true;
        }
        //next node and increment index
        currentNode = currentNode->next;
        currentIndex++;
    }
    //if index not found (out of range)
    return false;
}

template <typename T>
bool LinkedList<T>::removeValue(T value)  {

    Node<T>* currentNode = head;
    while(currentNode != nullptr){
        if(currentNode->data == value){
            Node<T>* nextNode = currentNode->next;
            Node<T>* prevNode = currentNode->prev;

            //if node to remove is the tail
            if(nextNode == nullptr) this->tail = prevNode;
                //else
            else nextNode->prev = prevNode;

            //if node to remove is the head
            if(prevNode == nullptr) this->head = nextNode;

                //else
            else prevNode->next = nextNode;

            delete currentNode;
            return true;
        }
        //next node and increment index
        currentNode = currentNode->next;
    }
    //if value not found (out of range)
    return false;
}

template <typename T>
void LinkedList<T>::clear(){
    Node<T>* currentNode = head;
    while(currentNode!= nullptr){
        Node<T>* toDelete = currentNode;
        currentNode = currentNode->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename T>
std::string LinkedList<T>::toString() {
    if(isEmpty()) {
        return "[ ]";
    }
    std::string array = "[ ";
    Node<T>* currentNode = head;
    while(currentNode != nullptr){
        array += std::to_string(currentNode->data) + ", ";
        currentNode = currentNode->next;
    }
    array.erase(array.end()-2);
    array += "]";
    return array;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
T LinkedList<T>::get(int index) {
    int i = 0;
    Node<T>* node = head;
    while (node != nullptr && i != index) {
        node = node->next;
        i++;
    }

    if (i != index) {
        cout << "Out of range";
        return T();
    }

    return node->data;
}

template<typename T>
Node<T> *LinkedList<T>::getHeadNode() {
    return head;
}

template<typename T>
void LinkedList<T>::set(Node<T> *start, Node<T> *end) {
    this->head = start;
    this->tail = end;
}

#endif //SDIZO_2_LINKEDLIST_H
