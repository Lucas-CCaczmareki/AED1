//Final version of leetcode 1717. Made in home
//Using stacks

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//Creating stack structure
typedef struct {
    char* data;     //Array of chars
    int top;        //The index of the top element in the stack
    int capacity;   //The maximum size of the stack
} Stack;

//Stack usage functions
//Receiving the address of the original stack to modify the original one.
void initStack(Stack* stack, int stack_size);
bool isEmpty(Stack* stack);
bool isFull(Stack *stack);
void push(Stack *stack, char value);
char pop(Stack *stack);
char peek(Stack *stack);
void freeStack(Stack* stack);

//Other functions
int maximumGain(char* s, int x, int y);

/* MAIN
Calls the maximum gain function and prints the maximum gain in the terminal
*/
int main( void ) {
    //Variables
    char *s = {"aabbabkbbbfvybssbtaobaaaabataaadabbbmakgabbaoapbbbbobaabvqhbbzbbkapabaavbbeghacabamdpaaqbqabbjbababmbakbaabajabasaabbwabrbbaabbafubayaazbbbaababbaaha"};
    
    int x       = 1926,
        y       = 4320,
        score   = 0;

    score = maximumGain(s, x, y);
    printf("%d", score);
    
    return 0;
}

/* MAXIMUM GAIN
Calculates the maximum gain removing the subwords "ab" and "ba"
X indicates the pontuation for removing 1 ab
Y indicates the pontuation for removing 1 ba
Returns the total pontuation
*/
int maximumGain(char* s, int x, int y) {
    //Local variables
    int score = 0,
        stack_size = strlen(s);

    Stack s_pass1;
    initStack(&s_pass1, stack_size);

    //Variables for better legibility
    int high_score, low_score;

    //1 is the first letter of a pair (In "ab", 1 is a, for example)
    char high_prio_1, high_prio_2;
    char low_prio_1, low_prio_2;

    //Does only one test to see which pair should have a highest priority
    //This minimazes the amount of tests made in comparison with the old version
    if( x > y ) {
        high_prio_1 = 'a';
        high_prio_2 = 'b';
        
        low_prio_1 = 'b';
        low_prio_2 = 'a';

        high_score = x;
        low_score = y;
    } else {
        high_prio_1 = 'b';
        high_prio_2 = 'a';
        
        low_prio_1 = 'a';
        low_prio_2 = 'b';

        high_score = y;
        low_score = x;
    }

    //1st pass
    //Here we put the string without the highest priority pairs in the stack. Forming a new string
    for( int i = 0; s[i] != '\0'; i++) { 
        /* IMPLEMENTATION DIFFERENCES
        Unlike the old program, we will check the top with the current character of the string (and only it)
        Checking with the s[i+1] is considered a bad practice and confusing.
        It also caused some bugs, trying to access inexistent spaces of memory (when it was not linear) or comparing with the \0
        All these stuff caused a lot of segmentation faults and errors which I don't have a clue of what was happening

        Eu também incrementava o i dentro de um if, o que podia causar uns erros sinistros
        */
        
        //If the stack is not empty, checks the rest
        //If the top and the current char in the string forms a pair, pops the top and continues the loop (discarding the pair)
        if(!isEmpty(&s_pass1) && peek(&s_pass1) == high_prio_1 && s[i] == high_prio_2) {
            pop(&s_pass1);
            score += high_score;
        } else {
            //If it's empty or the current char didn't form a pair. Put it in the top of stack
            push(&s_pass1, s[i]);
        }
    }

    //2nd pass
    //Here, we have the string without the highest priority pairs in the stack
    //We will check the other pars in reverse order. (just like the old version)
    
    Stack s_pass2;
    initStack(&s_pass2, s_pass1.top + 1); //top +1

    //This will loop the entire new string
    while(!isEmpty(&s_pass1)) {

        if(!isEmpty(&s_pass2) && peek(&s_pass2) == low_prio_2 && peek(&s_pass1) == low_prio_1) {
            pop(&s_pass1);
            pop(&s_pass2);
            score += low_score;
        } else {
            //It's empty or was not a pair
            push(&s_pass2, pop(&s_pass1));
        }

    }

    //End (freeing dynamic allocated memory)
    freeStack(&s_pass1);
    freeStack(&s_pass2);

    return score;
}

//Stack functions

/* INITSTACK
Initializes the pile based on the string s size
*/
void initStack(Stack *stack, int stack_size) {
    stack->capacity = stack_size;
    stack->data = (char *)malloc(stack->capacity * sizeof(char));
    
    if(stack->data == NULL) {
        printf("Error while alocating memory!");
        exit(1);
    }

    stack->top = -1; //generic unused value to indicate the stack is empty
}

/* ISEMPTY
Returns true or false, based on the value of the top of a stack
*/
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

/* ISFULL
Returns true or false if the top value is equal to capacity or not
*/
bool isFull(Stack *stack) {
    //Initial index == 0, so capacity goes until index capacity - 1
    return stack->top == stack->capacity - 1;
}

/* PUSH
Puts a value into the top of the stack
*/
void push(Stack *stack, char value) {
    if(isFull(stack)) {
        printf("Erro. Push em pilha CHEIA!");
        exit(1);
    }

    //This ++ puts the top into the next free index
    stack->data[++(stack->top)] = value;
}

/* POP
Decreases the top value, mading the valid itens in the pile decreases by one at the end
Mainting the FIFO property
*/
char pop(Stack *stack) {
    if(isEmpty(stack)) {
        printf("Erro. Pop em pilha VAZIA");
        exit(1);
    }

    //This -- decreses the top value after returning the actual top
    return stack->data[(stack->top)--];
}

/* PEEK
Simply returns the value of the item at the top
*/
char peek(Stack *stack) {
    if(isEmpty(stack)) {
        printf("ERRO. Peek em pilha vazia");
        exit(1);
    }
    return stack->data[stack->top];
}

/* FREESTACK
Frees the dynnamic allocated memory
*/
void freeStack(Stack* stack) {
    free(stack->data);  //frees the array of chars
    stack->data = NULL; //Makes it points to nothing
}


