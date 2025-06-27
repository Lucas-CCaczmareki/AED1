//Fila com prioridade (heap)
/* Building a priority queue using the Min-Heap logic to 
organize my structure. This is going to be an array-based
heap with maximum capacity for the sake of my mind
*/

#include <stdio.h>
#include <stdlib.h>


//---------- Structure definitions ----------

//A struct for a "node" in the priority queue. A generic one
typedef struct {
    int value;      //Data
    int priority;   //The priority of the item
    //smaller number = higher priority (as we are using min heap)
} Item;

// Structure for the priority queue itself
// Using arrays
typedef struct {
    Item *array;    // Points to the array storing the heap nodes (elements)
    int capacity;   // Maximum number of elements the heap can hold
    int size;       // Current number of elements in the heap
} PriorityQueue;

// --------- Functions for heap operating ---------

// Get parent index
int parent(int i) {
    return (i - 1) / 2;
}

// Get left child index
int leftChild(int i) {
    return (2 * i) + 1;
} 

// Get right child index
int rightChild(int i) {
    return (2 * i) + 2;
}

// Swap two items in the heap array
void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// --- Core priority queue functions ---

//Creating a new empty priority queue
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if( pq == NULL ) {
        printf("Failed to allocate PriorityQueue structure");
        //como caralhos o malloc sabe o espaço certinho pro vetor?
        exit(EXIT_FAILURE);
    }

    pq->array = (Item *) malloc(sizeof(Item) *capacity);
    if(pq->array == NULL) {
        printf("Failed to allocate array for Priority Queue");
        free(pq); //frees the structure of the PQ if the array cannot be allocated
        exit(EXIT_FAILURE);
    }

    pq->capacity = capacity;
    pq->size = 0;
    printf("Priority queue created with capacity %d.\n", capacity);
    return pq;
}

//Chekgin if the Priority Queue is empty
int isPQEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Check if the priority list is full
int isPQFull(PriorityQueue *pq) {
    return pq->size == pq->capacity;
}

// Helper function to maintain min heap property after insertion
void heapifyUp(PriorityQueue *pq, int i) {
    //While the current node is not root and its priority is smaller than its parents
    while (i != 0 && pq->array[parent(i)].priority > pq->array[i].priority) {
        swap(&pq->array[i], &pq->array[parent(i)]);
        i = parent(i);  //move up to the parent index
    }
}

// Insert an item into the priority queue
void insert(PriorityQueue *pq, int value, int priority) {
    if (isPQFull(pq)) {
        printf("Priority queue is full. Cannot insert %d (priority %d).\n", value, priority);
        return;
    }

    // Create the new item
    Item newItem;
    newItem.value = value;
    newItem.priority = priority;

    // Insert the new item ate the end of the array
    int i = pq->size;
    pq->array[i] = newItem;
    pq->size++;

    // Maintain heap property by moving the new item up if needed
    heapifyUp(pq, i);
    printf("Inserted: %d (priority %d).\n", value, priority);
}

// Helper function to maintain Min-heap property after extraction
void heapifyDown(PriorityQueue *pq, int i) {
    int smallest = i;           // Assume the current node 'i' is the smallest (highest priority)
    int l = leftChild(i);
    int r = rightChild(i);

    //If the left child exists and its priority is smaller thatn current smallest (it means, in a min heap, that the smallest prioriy cames first)
    if ( l < pq->size && pq->array[l].priority < pq->array[smallest].priority) {
        // l < pq->size checks if the leftChild (estimated position) exists by comparing with the size (amount of elements in the heap)
        smallest = l;
    }

    //If right child exists and its priority is smaller than current smallest
    if ( r < pq->size && pq->array[r].priority < pq->array[smallest].priority) {
        smallest = r;
    }

    //If smallest is not the current node, swap and continue heapifying down
    if (smallest != i) {
        swap(&pq->array[i], &pq->array[smallest]);
        heapifyDown(pq, smallest);
    }
}

//Extract the item with the highest priority (smallest value in the priority queue)
Item extractMin(PriorityQueue *pq) {
    if (isPQEmpty(pq)) {
        printf("Priority Queue is empty. Cannot extract.\n");
        //Retrurn a sentinel value indicating an error
        return (Item){-1, -1}; //value -1, priority -1
    }

    // The root (first element) is always the min
    Item minItem = pq->array[0];

    // Move the last element to the root
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;

    //Maintain heap property by moving the new root down
    heapifyDown(pq, 0);

    printf("Extracted: %d (priority: %d).\n", minItem.value, minItem.priority);
    return minItem;
}

//Peek at the item with the highest priority without removing it
Item peekMin(PriorityQueue *pq) {
    if (isPQEmpty(pq)) {
        printf("Priority queue is empty. Nothing to peek.\n");
        return (Item){-1, -1};
    }
    return pq->array[0];
}

// Free the memory used by the priority queue
void freePriorityQueue(PriorityQueue *pq) {
    if (pq == NULL) return;
    free(pq->array);    //free the array
    free(pq);           //free the pq structure
    printf("Priority queue freed.\n");
}

// Main: used to test the priority queue
int main() {
    //Create a priority queue with a capacity of 10
    PriorityQueue *myPQ = createPriorityQueue(10);

    // Insert elements with different priorities
    insert(myPQ, 30, 3);
    insert(myPQ, 10, 1); //one with highest priority
    insert(myPQ, 50, 5);
    insert(myPQ, 20, 2);
    insert(myPQ, 40, 4);

    //Peek at the highest priority item
    Item top = peekMin(myPQ);
    if(top.value != -1) {
        printf("Highest priority item(peek): %d (priority %d)\n", top.value, top.priority);
    }

    //Extracting elements (they should come out in priority order, that means, lowest priority value first)
    while (!isPQEmpty(myPQ)) {
        extractMin(myPQ);
    }

    //Try to extract from an empty queue
    extractMin(myPQ);

    //Free the memory
    freePriorityQueue(myPQ);

    return 0;
}




