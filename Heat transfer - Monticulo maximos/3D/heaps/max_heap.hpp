// MAX HEAP

#include <cmath>

// Function to calculate the index of the left child of a node in a heap
int left(int i) {
    return 2 * i + 1;
}

// Function to calculate the index of the right child of a node in a heap
int right(int i) {
    return 2 * i + 2;
}

// Function to swap two nodes in an array
void swap(Node** A, int i, int j) {
    Node* temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

// Function to maintain the max heap property of a node in a heap
void max_heapify(Node** A, int i, int heap_size) {
    int largest;
    int l = left(i);
    int r = right(i);
    
    // Compare the node with its left child and right child to find the largest value
    if (l < heap_size && A[l]->get_ID() > A[i]->get_ID())
        largest = l;
    else
        largest = i;
    
    if (r < heap_size && A[r]->get_ID() > A[largest]->get_ID())
        largest = r;
    
    // If the largest value is not the current node, swap the values and recursively apply max_heapify
    if (largest != i) {
        swap(A, i, largest);
        max_heapify(A, largest, heap_size);
    }
}

// Function to build a max heap from an array of nodes
void build_max_heap(Node** A, int heap_size) {
    // Start from the last non-leaf node and repeatedly apply max_heapify to create a max heap
    for (int i = floor(heap_size / 2) - 1; i >= 0; i--)
        max_heapify(A, i, heap_size);
}
