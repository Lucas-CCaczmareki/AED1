#include <stdio.h>
#include <stdlib.h>

//Definition of a node in the queue
typedef struct Node {
    int data;               // The value of the node
    struct Node *next;      // A pointer to the next node in the queue
} Node;

//Definition of the queue structure
typedef struct Queue {
    Node *front;            // Pointer to the first element (front) of the queue
    Node *rear;             // Pointer to the last element (back/rear) of the queue
} Queue;

// A function that creates an empty queue
Queue* createQueue() {
    Queue *newQueue = (Queue *) malloc(sizeof(Queue));

    if( newQueue == NULL ) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    newQueue->front = NULL;
    newQueue->rear  = NULL;
    return newQueue; //oq ta sendo retornado? um ponteiro pro espaço alocado?
}

//Function to check if the queue is empy
int isEmpty(Queue *queue){
    return (queue->front == NULL);
}

//Function no enqueue (add) an element
void enqueue(Queue *queue, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    if( newNode == NULL ) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    //Sets the values for the new node to be added.
    newNode->data = value;
    newNode->next = NULL;

    if( isEmpty(queue) ) {
        //If the queue was empty, the new node is both the front and the rear
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // If the queue is not empty, add to the rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("%d enqueued.\n", value);
}

//Function to dequeue (remove) and element
int dequeue(Queue *queue) {
    if( isEmpty(queue) ) {
        printf("The queue is empty. Cannot dequeue.\n");
        return -1; //any value that can indicates an error
    }
    Node *nodeToRemove = queue->front;
    int value = nodeToRemove->data;
    queue->front = queue->front->next; //the next node becomes the new front

    if( queue->front == NULL ) {
        // If the queue became empty after removal, the rear is also null
        queue->rear = NULL;
    }

    free(nodeToRemove); // Free the memory of the removed node
    printf("%d dequeued.\n", value);
    return value;
}

// Function to peek at the front element of the queue
int peek(Queue *queue) {
    if( isEmpty(queue) ) {
        printf("The queue is empty.\n");
        return -1;
    }
    return queue->front->data;
}

// Function to free the memoru used by the queue
void freeQueue(Queue *queue) {
    while( !isEmpty(queue) ) { //while is not empty
        dequeue(queue);
    }
    free(queue); //free the queue structure itself
    printf("Queue freed.\n");
}

int main() {
    Queue *myQueue = createQueue();

    enqueue(myQueue, 1);
    enqueue(myQueue, 2);
    enqueue(myQueue, 3);

    printf("Element at the front: %d\n", peek(myQueue));

    dequeue(myQueue);
    dequeue(myQueue);

    printf("Element at the front: %d\n", peek(myQueue));

    enqueue(myQueue, 4);

    dequeue(myQueue);
    dequeue(myQueue); // Trying to dequeue from an empty queue

    freeQueue(myQueue);

    return 0;
}