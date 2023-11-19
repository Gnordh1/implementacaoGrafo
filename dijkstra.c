#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo(int v){
    int i;
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

    for(i = 0; i < v; i++){
        g->adj[i].cab = NULL;
    }
    return g;
}

ADJACENCIA *criaAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    if(!gr) return false;
    if((vf < 0) || (vf >= gr->vertices)) return false;
    if((vi < 0) || (vi >= gr->vertices)) return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

int dijkstra(GRAFO *gr, int origem, int destino){
    int *distancia = (int *)malloc(gr->vertices * sizeof(int));
    int *visitado = (int *)malloc(gr->vertices * sizeof(int));
    int i, j, menor, atual, peso;

    for(i = 0; i < gr->vertices; i++){
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }

    distancia[origem] = 0;

    for(i = 0; i < gr->vertices; i++){
        menor = INT_MAX;
        for(j = 0; j < gr->vertices; j++){
            if(!visitado[j] && distancia[j] < menor){
                menor = distancia[j];
                atual = j;
            }
        }

        visitado[atual] = true;

        ADJACENCIA *ad = gr->adj[atual].cab;
        while(ad){
            if(!visitado[ad->vertice]){
                peso = ad->peso;
                if(distancia[atual] + peso < distancia[ad->vertice]){
                    distancia[ad->vertice] = distancia[atual] + peso;
                }
            }
            ad = ad->prox;
        }
    }

    int resultado = distancia[destino];
    free(distancia);
    free(visitado);
    return resultado;
}

void imprimirCaminho(int *ant, int v) {
    if (ant[v] != -1) {
        imprimirCaminho(ant, ant[v]);
        printf("%d ", v);
    }
}

void imprimeMatrizAdjacencia(GRAFO *gr){
    int i, j;
    printf("Matriz de Adjacencia:\n");

    for(i = 0; i < gr->vertices; i++){
        for(j = 0; j < gr->vertices; j++){
            int adjacente = 0;
            ADJACENCIA *ad = gr->adj[i].cab;
            while(ad){
                if(ad->vertice == j){
                    adjacente = 1;
                    break;
                }
                ad = ad->prox;
            }
            printf("%d ", adjacente);
        }
        printf("\n");
    }
}

void imprimeListaAdjacencia(GRAFO *gr){
    printf("Vertices: %d. Arestas: %d. \n", gr->vertices, gr->arestas);
    printf("Lista de Adjacencia:\n");
    int i;
    for(i = 0; i < gr->vertices; i++){
        printf("v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int valorTotal(GRAFO *gr){
    if(!gr) return 0;

    int i;
    int peso = 0;

    for(i=0; i<gr->vertices; i++){
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){
           peso += ad->peso;
           ad = ad->prox;
        }
    }
    return peso;
}

int main(){
    GRAFO *gr = criaGrafo(6);

    criaAresta(gr, 0, 1, 1);
    criaAresta(gr, 0, 2, 4);
    criaAresta(gr, 1, 0, 1);
    criaAresta(gr, 1, 2, 4);
    criaAresta(gr, 1, 3, 2);
    criaAresta(gr, 1, 4, 7);
    criaAresta(gr, 2, 0, 4);
    criaAresta(gr, 2, 1, 4);
    criaAresta(gr, 2, 3, 3);
    criaAresta(gr, 2, 4, 5);
    criaAresta(gr, 3, 1, 2);
    criaAresta(gr, 3, 2, 3);
    criaAresta(gr, 3, 4, 4);
    criaAresta(gr, 3, 5, 6);
    criaAresta(gr, 4, 1, 7);
    criaAresta(gr, 4, 2, 5);
    criaAresta(gr, 4, 3, 4);
    criaAresta(gr, 4, 5, 7);
    criaAresta(gr, 5, 3, 6);
    criaAresta(gr, 5, 4, 7);

    imprimeMatrizAdjacencia(gr);
    printf("\n");
    imprimeListaAdjacencia(gr);
    printf("\n");

    int origem = 0;
    int destino = 5;
    int resultado = dijkstra(gr, origem, destino);

    printf("\nMenor caminho de v%d para v%d: %d\n", origem, destino, resultado);

    return 0;
}
