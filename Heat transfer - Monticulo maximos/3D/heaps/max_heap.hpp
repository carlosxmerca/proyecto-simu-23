// MAX HEAP

#include <cmath>

int left(int i) {
    return 2*i + 1;
}

int right(int i) {
    return 2*i + 2;
}

void swap(Node **A, int i, int j) {
    Node* temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
        
void max_heapify(Node **A, int i, int heap_size) {
    int largest;
    int l = left(i);
    int r = right(i);
    if( l < heap_size && A[ l ]->get_ID() > A[ i ]->get_ID() )
        largest = l;
    else
        largest = i;
    if( r < heap_size && A[ r ]->get_ID() > A[ largest ]->get_ID() )
        largest = r;
    if( largest != i ){
        swap(A, i, largest);
        max_heapify(A, largest, heap_size);
    }
}

void build_max_heap(Node** A, int heap_size){
    for(int i = floor(heap_size/2)-1; i >= 0; i--)
        max_heapify(A, i, heap_size);
}
