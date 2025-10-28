// ejercicio5.c
// DFS con impresión de rastreo y lectura desde archivo

#include "graph.h"
#include <string.h>

// Variables globales
static int cnt;
static int pre[1000];
static int indent = 0;  // Variable para controlar la sangría

// Función auxiliar para imprimir sangría
void printIndent() {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

// Función dfsR con rastreo
static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    
    // Imprimir vértice actual con sangría
    printIndent();
    printf("%d\n", v);
    
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        
        // Imprimir arco que se está explorando
        printIndent();
        printf("%d-%d", v, w);
        
        if (pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            indent++;  // Incrementar sangría antes de la recursión
            dfsR(G, w);
            indent--;  // Decrementar sangría después de la recursión
        } else {
            printf("\n");
        }
    }
}

// Función GRAPHdfs con rastreo
void GRAPHdfs(Graph G) {
    cnt = 0;
    indent = 0;
    
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    
    printf("v-w   dfsR(G,w)\n");
    
    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            printf("%d dfsR(G,%d)\n", v, v);
            indent++;
            dfsR(G, v);
            indent--;
            printf("\n");
        }
    }
}

// Función para leer grafo desde archivo de adyacencia
Graph readGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return NULL;
    }
    
    int V;
    if (fscanf(file, "%d", &V) != 1) {
        printf("Error: Formato de archivo invalido\n");
        fclose(file);
        return NULL;
    }
    
    Graph G = GRAPHinit(V);
    
    // Leer cada línea de lista de adyacencia
    for (int v = 0; v < V; v++) {
        int vertex_num;
        if (fscanf(file, "%d", &vertex_num) != 1) {
            printf("Error: Falta informacion del vertice %d\n", v);
            GRAPHdestroy(G);
            fclose(file);
            return NULL;
        }
        
        if (vertex_num != v) {
            printf("Advertencia: Esperaba vertice %d pero encontro %d\n", v, vertex_num);
        }
        
        // Leer vecinos hasta fin de línea
        int neighbor;
        char line[1024];
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }
        
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            neighbor = atoi(token);
            if (neighbor >= 0 && neighbor < V) {
                GRAPHinsertArc(G, v, neighbor);
            }
            token = strtok(NULL, " \t\n");
        }
    }
    
    fclose(file);
    return G;
}

// Función para imprimir el vector pre[]
void printPre(Graph G) {
    printf("\nVector pre[]:\n");
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

// Función principal de prueba
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_grafo>\n", argv[0]);
        printf("\nFormato del archivo:\n");
        printf("Primera linea: numero de vertices V\n");
        printf("Siguientes V lineas: v vecino1 vecino2 ...\n");
        printf("\nEjemplo:\n");
        printf("6\n");
        printf("0 1 4\n");
        printf("1 2 5\n");
        printf("2 3\n");
        printf("3 7\n");
        printf("4 8\n");
        printf("5 4\n");
        return 1;
    }
    
    Graph G = readGraphFromFile(argv[1]);
    if (G == NULL) {
        return 1;
    }
    
    printf("Grafo cargado desde archivo:\n");
    GRAPHshow(G);
    printf("\n");
    
    printf("Ejecutando DFS con rastreo:\n");
    printf("================================\n");
    GRAPHdfs(G);
    
    printPre(G);
    
    GRAPHdestroy(G);
    return 0;
}