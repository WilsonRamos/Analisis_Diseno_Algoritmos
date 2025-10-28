// ejercicio7.c
// Version iterativa correcta de DFS para listas de adyacencia

#include "graph.h"
#include "stack.h"

static int cnt;
static int pre[1000];

// DFS recursivo (version original para comparacion)
static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1)
            dfsR(G, w);
    }
}

// DFS iterativo correcto usando pila
// Esta version simula exactamente el comportamiento de la recursion
static void dfsIterative(Graph G, vertex v) {
    Stack *s = STACKinit();
    
    // Crear item inicial y apilar
    StackItem item;
    item.vertex = v;
    item.iterator = G->adj[v];
    
    pre[v] = cnt++;
    STACKpush(s, item);
    
    while (!STACKempty(s)) {
        StackItem current = STACKpop(s);
        vertex cv = current.vertex;
        link a = (link)current.iterator;
        
        // Buscar el siguiente vecino no visitado
        while (a != NULL && pre[a->w] != -1) {
            a = a->next;
        }
        
        if (a != NULL) {
            // Encontramos un vecino no visitado
            vertex w = a->w;
            
            // Re-apilar el vertice actual con el iterador actualizado
            StackItem resumeItem;
            resumeItem.vertex = cv;
            resumeItem.iterator = a->next;
            STACKpush(s, resumeItem);
            
            // Apilar el nuevo vertice
            pre[w] = cnt++;
            StackItem newItem;
            newItem.vertex = w;
            newItem.iterator = G->adj[w];
            STACKpush(s, newItem);
        }
        // Si a == NULL, hemos terminado con este vertice
    }
    
    STACKdestroy(s);
}

// Función principal de DFS iterativo
void GRAPHdfsIterative(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    
    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1)
            dfsIterative(G, v);
    }
}

// Funcion principal de DFS recursivo (para comparacion)
void GRAPHdfs(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    
    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1)
            dfsR(G, v);
    }
}

// Funcion para imprimir el vector pre[]
void printPre(Graph G, const char *label) {
    printf("\n%s:\n", label);
    printf("w:     ");
    for (vertex v = 0; v < G->V; v++) {
        printf(" %2d", v);
    }
    printf("\npre[w]:");
    for (vertex v = 0; v < G->V; v++) {
        printf(" %2d", pre[v]);
    }
    printf("\n");
}

// Funcion para copiar pre[] a otro array
void copyPre(int dest[], int V) {
    for (int i = 0; i < V; i++) {
        dest[i] = pre[i];
    }
}

// Funcion principal de prueba
int main() {
    // Crear grafo de ejemplo del Ejemplo A del laboratorio
    printf("=== PRUEBA 1: Ejemplo A del laboratorio ===\n");
    Graph G1 = GRAPHinit(6);
    GRAPHinsertArc(G1, 0, 1);
    GRAPHinsertArc(G1, 1, 2);
    GRAPHinsertArc(G1, 1, 3);
    GRAPHinsertArc(G1, 2, 4);
    GRAPHinsertArc(G1, 2, 5);
    
    printf("Grafo:\n");
    GRAPHshow(G1);
    
    // Ejecutar DFS recursivo
    GRAPHdfs(G1);
    int pre_recursive[1000];
    copyPre(pre_recursive, G1->V);
    printPre(G1, "DFS Recursivo");
    
    // Ejecutar DFS iterativo
    GRAPHdfsIterative(G1);
    int pre_iterative[1000];
    copyPre(pre_iterative, G1->V);
    printPre(G1, "DFS Iterativo");
    
    // Comparar resultados
    int igual = 1;
    for (int i = 0; i < G1->V; i++) {
        if (pre_recursive[i] != pre_iterative[i]) {
            igual = 0;
            break;
        }
    }
    printf("\nLos resultados son identicos? %s\n", igual ? "SI" : "NO");
    
    GRAPHdestroy(G1);
    
    // Crear grafo de ejemplo del Ejemplo C
    printf("\n\n=== PRUEBA 2: Ejemplo C del laboratorio ===\n");
    Graph G2 = GRAPHinit(6);
    GRAPHinsertArc(G2, 2, 0);
    GRAPHinsertArc(G2, 2, 3);
    GRAPHinsertArc(G2, 2, 4);
    GRAPHinsertArc(G2, 0, 1);
    GRAPHinsertArc(G2, 0, 4);
    GRAPHinsertArc(G2, 3, 4);
    GRAPHinsertArc(G2, 3, 5);
    GRAPHinsertArc(G2, 4, 1);
    GRAPHinsertArc(G2, 4, 5);
    GRAPHinsertArc(G2, 5, 1);
    
    printf("Grafo:\n");
    GRAPHshow(G2);
    
    // Ejecutar DFS recursivo
    GRAPHdfs(G2);
    copyPre(pre_recursive, G2->V);
    printPre(G2, "DFS Recursivo");
    
    // Ejecutar DFS iterativo
    GRAPHdfsIterative(G2);
    copyPre(pre_iterative, G2->V);
    printPre(G2, "DFS Iterativo");
    
    // Comparar resultados
    igual = 1;
    for (int i = 0; i < G2->V; i++) {
        if (pre_recursive[i] != pre_iterative[i]) {
            igual = 0;
            break;
        }
    }
    printf("\nLos resultados son identicos? %s\n", igual ? "SI" : "NO");
    
    GRAPHdestroy(G2);
    
    // Crear grafo no dirigido
    printf("\n\n=== PRUEBA 3: Grafo no dirigido ===\n");
    Graph G3 = GRAPHinit(5);
    GRAPHinsertEdge(G3, 0, 1);
    GRAPHinsertEdge(G3, 0, 2);
    GRAPHinsertEdge(G3, 1, 3);
    GRAPHinsertEdge(G3, 2, 3);
    GRAPHinsertEdge(G3, 3, 4);
    
    printf("Grafo:\n");
    GRAPHshow(G3);
    
    // Ejecutar DFS recursivo
    GRAPHdfs(G3);
    copyPre(pre_recursive, G3->V);
    printPre(G3, "DFS Recursivo");
    
    // Ejecutar DFS iterativo
    GRAPHdfsIterative(G3);
    copyPre(pre_iterative, G3->V);
    printPre(G3, "DFS Iterativo");
    
    // Comparar resultados
    igual = 1;
    for (int i = 0; i < G3->V; i++) {
        if (pre_recursive[i] != pre_iterative[i]) {
            igual = 0;
            break;
        }
    }
    printf("\nLos resultados son identicos? %s\n", igual ? "SI" : "NO");
    
    GRAPHdestroy(G3);
    
    printf("\n\n=== CONCLUSION ===\n");
    printf("La version iterativa produce exactamente los mismos resultados\n");
    printf("que la version recursiva, demostrando su correctitud.\n");
    
    return 0;
}