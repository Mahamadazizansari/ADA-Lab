#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
struct Graph {
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES];
};
void initGraph(struct Graph* g, int V) {
    g->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = 0;
        }
    }
}
void addEdge(struct Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}
void topologicalSort(struct Graph* g) {
    int in_degree[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int top_order[MAX_VERTICES];
    int count = 0;
    for (int i = 0; i < g->V; i++) {
        for (int j = 0; j < g->V; j++) {
            if (g->adj[i][j] == 1) {
                in_degree[j]++;
            }
        }
    }
    for (int i = 0; i < g->V; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }
    while (front != rear) {
        int u = queue[front++];

        top_order[count++] = u;

        for (int v = 0; v < g->V; v++) {
            if (g->adj[u][v] == 1) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
    if (count < g->V) {
        printf("Graph has a cycle. Topological sort is not possible.\n");
    } else {
        printf("Topological Sort: ");
        for (int i = 0; i < g->V; i++) {
            printf("%d ", top_order[i] + 1);
        }
        printf("\n");
    }
}
int main() {
    struct Graph g;
    int V, E, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    initGraph(&g, V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (u v) for directed edges:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        addEdge(&g, u - 1, v - 1);
    }
    topologicalSort(&g);
    return 0;
}
