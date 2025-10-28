#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;
struct node {
    int v;
    link next;
};

typedef struct {
    int V;
    link *adj;
} *Graph;

int *pre;
int cnt = 0;
int indent = 0;  // sangría global


// Crear nuevo nodo

link NEW(int v, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}


// Crear grafo con V vértices

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->adj = malloc(V * sizeof(link));
    for (int v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}


// Insertar arista (no dirigida)

void GRAPHinsertE(Graph G, int v, int w) {
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);
}


// Imprimir sangría

void printIndent() {
    for (int i = 0; i < indent; i++) printf("  ");
}


void dfsR(Graph G, int v) {
    printIndent();
    printf("Entrando a dfsR(%d)\n", v);
    indent++;

    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        int w = a->v;
        if (pre[w] == -1) {
            printIndent();
            printf("(%d,%d)\n", v, w);
            dfsR(G, w);
        } else {
            printIndent();
            printf("(%d,%d)\n", v, w);
        }
    }

    indent--;
    printIndent();
    printf("Saliendo de dfsR(%d)\n", v);
}


void GRAPHdfs(Graph G) {
    pre = malloc(G->V * sizeof(int));
    for (int v = 0; v < G->V; v++)
        pre[v] = -1;

    for (int v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, v);

    free(pre);
}


// Leer grafo desde archivo

Graph GRAPHreadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: no se puede abrir el archivo.\n");
        exit(1);
    }

    int V;
    fscanf(fp, "%d", &V);
    Graph G = GRAPHinit(V);

    int v, w;
    while (fscanf(fp, "%d", &v) == 1) {
        int c;
        char line[256];
        fgets(line, sizeof(line), fp);
        char *p = line;
        while (sscanf(p, "%d%n", &w, &c) == 1) {
            GRAPHinsertE(G, v, w);
            p += c;
        }
    }

    fclose(fp);
    return G;
}


int main() {
    Graph G = GRAPHreadFromFile("grafo.txt");
    printf("Rastreo de GRAPHdfs()\n");
    GRAPHdfs(G);
    return 0;
}
