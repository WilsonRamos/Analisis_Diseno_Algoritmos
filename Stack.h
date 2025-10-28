// stack.h
// Implementación de pila para DFS iterativo

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

// Estructura para almacenar vértice con su iterador
typedef struct {
    int vertex;
    void *iterator;  // Puntero al nodo actual en la lista de adyacencia
} StackItem;

// Nodo de la pila
typedef struct stackNode {
    StackItem item;
    struct stackNode *next;
} *StackNode;

// Estructura de la pila
typedef struct {
    StackNode top;
    int size;
} Stack;

// Funciones de la pila
Stack* STACKinit();
void STACKpush(Stack *s, StackItem item);
StackItem STACKpop(Stack *s);
StackItem STACKtop(Stack *s);
int STACKempty(Stack *s);
int STACKsize(Stack *s);
void STACKdestroy(Stack *s);

// Implementaciones
Stack* STACKinit() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void STACKpush(Stack *s, StackItem item) {
    StackNode new = malloc(sizeof(struct stackNode));
    new->item = item;
    new->next = s->top;
    s->top = new;
    s->size++;
}

StackItem STACKpop(Stack *s) {
    if (s->top == NULL) {
        StackItem empty = {-1, NULL};
        return empty;
    }
    StackNode temp = s->top;
    StackItem item = temp->item;
    s->top = temp->next;
    free(temp);
    s->size--;
    return item;
}

StackItem STACKtop(Stack *s) {
    if (s->top == NULL) {
        StackItem empty = {-1, NULL};
        return empty;
    }
    return s->top->item;
}

int STACKempty(Stack *s) {
    return s->top == NULL;
}

int STACKsize(Stack *s) {
    return s->size;
}

void STACKdestroy(Stack *s) {
    while (!STACKempty(s)) {
        STACKpop(s);
    }
    free(s);
}

#endif // STACK_H