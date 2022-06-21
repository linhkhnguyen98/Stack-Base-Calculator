#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * You might want to declare some global variables to
 * help you maintain the stack, and the state of the stack.
 * Once you have implemented push and pop here and corresponding
 * parts in operate.c - we highly recommend checking out
 * tests/stack_test and running it to see if you are getting expected
 * output - to check basic stack functionality. You could write similar
 * tests for other functionalities.
 */
int count = 0;
node_t *head = NULL;
node_t *tail;
//node_t *new_node;
//node_t *temp;
/* push a value to the stack */
void push(int val) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->val = val;
    if(head == NULL){
        new_node->next = NULL;
        head = new_node;
        tail = new_node;
    }
    else{
        new_node->next = head;
        head = new_node;
    }
    count++;
}
/* pop a value from the stack
 * return 0 if pop failed, else return 1 and set *v
 */
int pop(int* v) {
    if(head == NULL){
        return 0;
    }
    *v = head->val;
    node_t* tmp = head->next;
    free(head);
    head = tmp;
    count--;
    return 1;
}

/* print the entire stack */
void printstack() {
    node_t* temp = head;
    int index = count - 1;

    while(temp != NULL){
        printf("\tS%d:\t%d\n", index--, temp->val);
        temp = temp->next;
    }
}

/* the topmost entry becomes the lowest entry in the stack */
void rot() {
    int tmp;

    tmp = head->val;
    head->val = tail->val;
    tail->val = tmp;
}

/* returns the size of the stack */
unsigned int get_stack_size() {
    return count;
}

/* delete all entries in the stack, free all memory associated with it */
void delete_stack() {
    node_t* tmp = head;
    node_t* tmp2;
    while (tmp != NULL){
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    head = NULL;
    tail = NULL;
}
