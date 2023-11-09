#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adjacencia {
    int vertice;
    struct adjacencia* prox;
} ADJACENCIA;

typedef struct vertice {
    ADJACENCIA* cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE* adj;
} GRAFO;

GRAFO* criaGrafo(int v) {
    int i;
    GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE*)malloc(v * sizeof(VERTICE));

    for (i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
    }
    return g;
}

ADJACENCIA* criaAdj(int v) {
    ADJACENCIA* temp = (ADJACENCIA*)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->prox = NULL;
    return temp;
}

void criaAresta(GRAFO* gr, int vi, int vf) {
    if (!gr) return;
    ADJACENCIA* novo = criaAdj(vf);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
}

void BFS(GRAFO* gr, int inicio) {
    int* visitados = (int*)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }

    int* fila = (int*)malloc(gr->vertices * sizeof(int));
    int frente = 0;
    int tras = 0;

    visitados[inicio] = 1;
    fila[tras++] = inicio;

    printf("Busca em Largura a partir do vertice %d: ", inicio);

    while (frente != tras) {
        int atual = fila[frente++];
        printf("%d ", atual);

        // Armazena os vértices adjacentes em um array
        int* adjacentes = (int*)malloc(gr->vertices * sizeof(int));
        int numAdjacentes = 0;

        ADJACENCIA* ad = gr->adj[atual].cab;
        while (ad) {
            int vizinho = ad->vertice;
            if (!visitados[vizinho]) {
                adjacentes[numAdjacentes++] = vizinho;
                visitados[vizinho] = 1;
            }
            ad = ad->prox;
        }

        // Ordena os vértices adjacentes (bubble sort para simplicidade)
        for (int i = 0; i < numAdjacentes - 1; i++) {
            for (int j = 0; j < numAdjacentes - i - 1; j++) {
                if (adjacentes[j] > adjacentes[j + 1]) {
                    int temp = adjacentes[j];
                    adjacentes[j] = adjacentes[j + 1];
                    adjacentes[j + 1] = temp;
                }
            }
        }

        // Adiciona os vértices adjacentes ordenados à fila
        for (int i = 0; i < numAdjacentes; i++) {
            fila[tras++] = adjacentes[i];
        }

        free(adjacentes);
    }

    printf("\n");

    free(visitados);
    free(fila);
}

void DFS(GRAFO* gr, int inicio) {
    int* visitados = (int*)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }

    printf("Busca em Profundidade a partir do vertice %d: ", inicio);
    DFSRecursivo(gr, inicio, visitados);
    printf("\n");

    free(visitados);
}

void DFSRecursivo(GRAFO* gr, int vertice, int* visitados) {
    visitados[vertice] = 1;
    printf("%d ", vertice);

    // Armazena os vértices adjacentes em um array
    int* adjacentes = (int*)malloc(gr->vertices * sizeof(int));
    int numAdjacentes = 0;

    ADJACENCIA* ad = gr->adj[vertice].cab;
    while (ad) {
        int vizinho = ad->vertice;
        if (!visitados[vizinho]) {
            adjacentes[numAdjacentes++] = vizinho;
        }
        ad = ad->prox;
    }

    // Ordena os vértices adjacentes (bubble sort para simplicidade)
    for (int i = 0; i < numAdjacentes - 1; i++) {
        for (int j = 0; j < numAdjacentes - i - 1; j++) {
            if (adjacentes[j] > adjacentes[j + 1]) {
                int temp = adjacentes[j];
                adjacentes[j] = adjacentes[j + 1];
                adjacentes[j + 1] = temp;
            }
        }
    }

    // Chama a recursão para os vértices adjacentes ordenados
    for (int i = 0; i < numAdjacentes; i++) {
        int vizinho = adjacentes[i];
        if (!visitados[vizinho]) {
            DFSRecursivo(gr, vizinho, visitados);
        }
    }

    free(adjacentes);
}

int main() {
    
    GRAFO* gr = criaGrafo(15);

    criaAresta(gr, 0, 1);
    criaAresta(gr, 0, 2);
    criaAresta(gr, 1, 3);
    criaAresta(gr, 1, 4);
    criaAresta(gr, 1, 5);
    criaAresta(gr, 3, 6);
    criaAresta(gr, 3, 7);
    criaAresta(gr, 5, 8);
    criaAresta(gr, 5, 9);
    criaAresta(gr, 7, 10);
    criaAresta(gr, 7, 11);
    criaAresta(gr, 7, 12);
    criaAresta(gr, 9, 13);
    criaAresta(gr, 9, 14);
    
    GRAFO* gr2 = criaGrafo(10);

    criaAresta(gr2, 0, 1);
    criaAresta(gr2, 1, 2);
    criaAresta(gr2, 1, 4);
    criaAresta(gr2, 2, 3);
    criaAresta(gr2, 2, 4);
    criaAresta(gr2, 2, 9);
    criaAresta(gr2, 3, 4);
    criaAresta(gr2, 4, 5);
    criaAresta(gr2, 4, 6);
    criaAresta(gr2, 4, 7);
    criaAresta(gr2, 5, 6);
    criaAresta(gr2, 7, 8);
    criaAresta(gr2, 7, 9);
    

    BFS(gr, 1);
    DFS(gr2, 0);

    return 0;
}

