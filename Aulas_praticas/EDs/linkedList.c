//Implementação do gemini. Vou fazer a minha outra hora quando eu tiver mais tempo

#include <stdio.h>
#include <stdlib.h> // For malloc, free, exit

// --- Structure Definitions ---

// 1. Define the Node structure
// Each node contains data and a pointer to the next node
typedef struct Node {
    int data;           // The data the node holds
    struct Node *next;  // Pointer to the next node in the list
} Node;

// 2. Define the List structure
// The list itself needs a pointer to its head (first node)
typedef struct List {
    Node *head; // Pointer to the first node of the list
    int size;   // To keep track of the number of elements (optional but useful)
} List;

// --- List Operations ---

// 1. Create a new empty List
List* createList() {
    List *newList = (List*) malloc(sizeof(List));
    if (newList == NULL) {
        perror("Memory allocation error for List structure");
        exit(EXIT_FAILURE);
    }
    newList->head = NULL; // An empty list has its head pointing to NULL
    newList->size = 0;
    printf("List created.\n");
    return newList;
}

// 2. Check if the List is empty
int isListEmpty(List *list) {
    // Also good to check if the list pointer itself is NULL for safety,
    // though typically you'd assume a valid list pointer is passed after createList.
    if (list == NULL) return 1;
    return (list->head == NULL);
}

// 3. Add an element to the front of the list (Head Insertion)
void addFront(List *list, int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation error for new Node");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = list->head; // New node points to the current head
    list->head = newNode;       // New node becomes the new head
    list->size++;
    printf("Added %d to the front.\n", value);
}

// 4. Add an element to the end of the list (Tail Insertion)
void addEnd(List *list, int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation error for new Node");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL; // New node will be the last, so its next is NULL

    if (isListEmpty(list)) {
        list->head = newNode; // If list was empty, new node is also the head
    } else {
        Node *current = list->head;
        while (current->next != NULL) { // Traverse to the last node
            current = current->next;
        }
        current->next = newNode; // Last node points to the new node
    }
    list->size++;
    printf("Added %d to the end.\n", value);
}

// 5. Insert an element at a specific position (0-indexed)
void insertAt(List *list, int value, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position %d. List size is %d.\n", position, list->size);
        return;
    }

    if (position == 0) {
        addFront(list, value); // Use addFront if inserting at the beginning
        return;
    }

    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation error for new Node");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;

    Node *current = list->head;
    // Traverse to the node *before* the desired position
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next; // New node points to what 'current' used to point to
    current->next = newNode;       // 'current' now points to the new node
    list->size++;
    printf("Inserted %d at position %d.\n", value, position);
}

// 6. Remove an element from the front of the list (Head Deletion)
int removeFront(List *list) {
    if (isListEmpty(list)) {
        printf("List is empty. Cannot remove from front.\n");
        return -1; // Indicate error
    }
    Node *nodeToRemove = list->head;
    int value = nodeToRemove->data;
    list->head = list->head->next; // The second node becomes the new head
    free(nodeToRemove);             // Free the removed node's memory
    list->size--;
    printf("Removed %d from the front.\n", value);
    return value;
}

// 7. Remove an element from the end of the list (Tail Deletion)
int removeEnd(List *list) {
    if (isListEmpty(list)) {
        printf("List is empty. Cannot remove from end.\n");
        return -1; // Indicate error
    }

    if (list->head->next == NULL) { // Only one element in the list
        return removeFront(list);   // Use removeFront logic
    }

    Node *current = list->head;
    Node *previous = NULL;
    while (current->next != NULL) { // Traverse to the last node
        previous = current;
        current = current->next;
    }
    // 'current' is now the last node, 'previous' is the second to last
    int value = current->data;
    previous->next = NULL; // Second to last node now points to NULL
    free(current);         // Free the last node's memory
    list->size--;
    printf("Removed %d from the end.\n", value);
    return value;
}

// 8. Remove an element at a specific position (0-indexed)
int removeAt(List *list, int position) {
    if (isListEmpty(list)) {
        printf("List is empty. Cannot remove from position %d.\n", position);
        return -1;
    }
    if (position < 0 || position >= list->size) {
        printf("Invalid position %d. List size is %d.\n", position, list->size);
        return -1;
    }

    if (position == 0) {
        return removeFront(list); // Use removeFront if removing the first element
    }

    Node *current = list->head;
    Node *previous = NULL;
    // Traverse to the node *before* the desired position
    for (int i = 0; i < position; i++) {
        previous = current;
        current = current->next;
    }
    // 'current' is the node to remove, 'previous' is the node before it
    int value = current->data;
    previous->next = current->next; // Skip the 'current' node
    free(current);                  // Free the removed node's memory
    list->size--;
    printf("Removed %d from position %d.\n", value, position);
    return value;
}


// 9. Get the element at a specific position without removing it
int getAt(List *list, int position) {
    if (isListEmpty(list) || position < 0 || position >= list->size) {
        printf("Invalid position %d or list is empty. Size is %d.\n", position, list->size);
        return -1; // Indicate error
    }
    Node *current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

// 10. Display all elements in the list
void displayList(List *list) {
    if (isListEmpty(list)) {
        printf("List: [Empty]\n");
        return;
    }
    Node *current = list->head;
    printf("List (size %d): ", list->size);
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 11. Free all memory used by the list
void freeList(List *list) {
    if (list == NULL) return;
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next; // Save pointer to the next node
        free(current);        // Free the current node
        current = next;       // Move to the next node
    }
    free(list); // Free the List structure itself
    printf("List freed.\n");
}

// --- Main function for testing ---
int main() {
    List *myList = createList();

    displayList(myList);

    addFront(myList, 10);
    addEnd(myList, 30);
    addFront(myList, 5);
    addEnd(myList, 40);
    displayList(myList); // Expected: 5 -> 10 -> 30 -> 40 -> NULL

    insertAt(myList, 20, 2); // Insert 20 at index 2
    displayList(myList);     // Expected: 5 -> 10 -> 20 -> 30 -> 40 -> NULL

    printf("Element at position 3: %d\n", getAt(myList, 3)); // Expected: 30

    removeFront(myList);
    displayList(myList); // Expected: 10 -> 20 -> 30 -> 40 -> NULL

    removeEnd(myList);
    displayList(myList); // Expected: 10 -> 20 -> 30 -> NULL

    removeAt(myList, 1); // Remove 20 (at index 1)
    displayList(myList); // Expected: 10 -> 30 -> NULL

    freeList(myList);

    // Demonstrate with an empty list and single element list
    printf("\n--- Testing Edge Cases ---\n");
    List *edgeCaseList = createList();
    removeFront(edgeCaseList); // Try to remove from empty
    addFront(edgeCaseList, 100);
    displayList(edgeCaseList);
    removeEnd(edgeCaseList); // Remove the only element
    displayList(edgeCaseList);
    freeList(edgeCaseList);


    return 0;
}
