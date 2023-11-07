#include <stdio.h>
#include <stdlib.h>
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
    if((vi < 0) || (vf >= gr->vertices)) return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
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
    // Se o grafo nao existe
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
    GRAFO *gr = criaGrafo(5);

    criaAresta(gr, 0, 0, 0); // Aresta para ela mesma (v0 -> v0)
    criaAresta(gr, 0, 2, 0); // Aresta para v3 (v0 -> v3)
    criaAresta(gr, 1, 2, 0); // Aresta para v4 (v1 -> v2)
    criaAresta(gr, 1, 3, 0); // Aresta para v5 (v1 -> v3)
    criaAresta(gr, 1, 4, 0); // Aresta para v6 (v1 -> v4)
    criaAresta(gr, 2, 0, 0); // Aresta para v1 (v2 -> v0)
    criaAresta(gr, 2, 1, 0); // Aresta para v2 (v2 -> v1)
    criaAresta(gr, 2, 3, 0); // Aresta para v4 (v2 -> v3)
    criaAresta(gr, 3, 1, 0); // Aresta para v2 (v3 -> v1)
    criaAresta(gr, 3, 2, 0); // Aresta para v3 (v3 -> v2)
    criaAresta(gr, 3, 4, 0); // Aresta para v5 (v3 -> v4)
    criaAresta(gr, 4, 1, 0); // Aresta para v2 (v4 -> v1)
    criaAresta(gr, 4, 3, 0); // Aresta para v4 (v4 -> v3)

    imprimeMatrizAdjacencia(gr);
    printf("\n");
    imprimeListaAdjacencia(gr);
    printf("\n");

    GRAFO *gr2 = criaGrafo(5);
    printf("GRAFO PONDERADO - SEGUNDA SAIDA \n");
    int peso;

    printf("Digite o peso do caminho [1]->[1]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 0, 0, peso);

    printf("Digite o peso do caminho [1]->[3]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 0, 2, peso);

    printf("Digite o peso do caminho [3]->[2]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 2, 1, peso);

    printf("Digite o peso do caminho [3]->[4]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 2, 3, peso);

    printf("Digite o peso do caminho [2]->[4]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 1, 3, peso);

    printf("Digite o peso do caminho [2]->[5]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 1, 4, peso);

    printf("Digite o peso do caminho [4]->[5]: ");
    scanf("%d", &peso);
    criaAresta(gr2, 3, 4, peso);

    printf("\nValor total do caminho {1, 5}: %d\n", valorTotal(gr2));
    printf("\n");
    imprimeMatrizAdjacencia(gr2);
    printf("\n");
    imprimeListaAdjacencia(gr2);
    printf("\n");
    return 0;
}
