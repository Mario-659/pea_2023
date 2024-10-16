#ifndef SDIZO_2_HEAP_H
#define SDIZO_2_HEAP_H

#include <utility>

/**
 * Priority queue minimum type
 */
template<typename T>
class Heap {
private:
    T* arr;
    int maxSize;
    int currSize;
    int getParent(int index) {
        return (index - 1) / 2; }
    int getLeft(int index) {
        return 2 * index + 1; }
    int getRight(int index) {
        return 2 * index + 2; }

    // Restores structure of heap from given index
    void heapify(int index);
public:
    // Makes new empty heap with maximum size of maxSize
    Heap(int maxSize);

    // Adds element
    void push(T value);

    // Removes and returns min (root) element from heap
    T extractMin();

    // Returns true if value in heap
    bool contains(T value);

    // Updates value
    void update(T prev, T newVal);

    // Returns current size
    int getSize() { return currSize; }

    ~Heap() { delete[] arr; }
};

template <typename T>
T Heap<T>::extractMin() {
    if (currSize == 0) return T();

    T minValue = arr[0];
    arr[0] = arr[currSize - 1];
    currSize--;
    heapify(0);
    return minValue;
}

template <typename T>
void Heap<T>::push(T value) {
    // Check if maximum size reached
    if (currSize == maxSize) return;

    arr[currSize] = value;
    currSize++;

    // Move to higher level if value is smaller than its parent
    int currInd = currSize - 1;
    while (currInd != 0 && arr[getParent(currInd)] > arr[currInd]) {
        std::swap(arr[currInd], arr[getParent(currInd)]);
        currInd = getParent(currInd);
    }
}

template <typename T>
Heap<T>::Heap(int maxSize) {
    arr = new T[maxSize];
    this->maxSize = maxSize;
    currSize = 0;
}

template <typename T>
void Heap<T>::heapify(int index) {
    int smallest = index;
    int l = getLeft(index);
    int r = getRight(index);

    if (l < currSize && arr[l] < arr[smallest]) {
        smallest = l;
    }
    if (r < currSize && arr[r] < arr[smallest]) {
        smallest = r;
    }
    if (smallest != index) {
        std::swap(arr[index], arr[smallest]);
        heapify(smallest);
    }
}

template<typename T>
bool Heap<T>::contains(T value) {
    for (int i = 0; i < currSize; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

template<typename T>
void Heap<T>::update(T prev, T newVal) {
    int indexElement;
    for (int i = 0; i < currSize; i++) {
        if (arr[i] == prev) {
            arr[i] = newVal;
            indexElement = i;
            break;
        }
    }

    if (newVal > prev) {
        heapify(indexElement);
    } else {
        while (indexElement != 0 && arr[getParent(indexElement)] > newVal) {
            std::swap(arr[indexElement], arr[getParent(indexElement)]);
            indexElement = getParent(indexElement);
        }
    }
}

#endif // SDIZO_2_HEAP_H
