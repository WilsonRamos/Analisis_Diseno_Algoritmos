// graph.h
// Definiciones de estructuras para representación de grafos

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// Definición de tipos
typedef int vertex;

// Nodo de lista de adyacencia
typedef struct node {
    vertex w;
    struct node *next;
} *link;

// Estructura de grafo
typedef struct graph {
    int V;           // Número de vértices
    int A;           // Número de arcos
    link *adj;       // Array de listas de adyacencia
} *Graph;

// Funciones básicas de grafos
Graph GRAPHinit(int V);
void GRAPHinsertArc(Graph G, vertex v, vertex w);
void GRAPHinsertEdge(Graph G, vertex v, vertex w);
void GRAPHdestroy(Graph G);
void GRAPHshow(Graph G);

// Implementación de funciones básicas
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    // Insertar arco v->w
    link new = malloc(sizeof *new);
    new->w = w;
    new->next = G->adj[v];
    G->adj[v] = new;
    G->A++;
}

void GRAPHinsertEdge(Graph G, vertex v, vertex w) {
    // Insertar arista v-w (dos arcos)
    GRAPHinsertArc(G, v, w);
    GRAPHinsertArc(G, w, v);
}

void GRAPHdestroy(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link temp = a;
            a = a->next;
            free(temp);
        }
    }
    free(G->adj);
    free(G);
}

void GRAPHshow(Graph G) {
    printf("Grafo con %d vértices y %d arcos:\n", G->V, G->A);
    for (vertex v = 0; v < G->V; v++) {
        printf("%d:", v);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf(" %d", a->w);
        printf("\n");
    }
}

#endif // GRAPH_H