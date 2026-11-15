/*
 * Problem 7: Dijkstra's Single Source Shortest Path (SSSP)
 * Uses a Priority Queue (Min-Heap) for single-source shortest path finding.
 */

#include <stdio.h>

#define MAX 20
#define INF 999999

int n; // Number of vertices
int adj[MAX][MAX];

// Min-Heap Node
struct HeapNode {
    int v;
    int dist;
};

// Priority Queue (Min-Heap) Implementation
struct HeapNode heap[MAX * MAX];
int heapSize = 0;

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(int v, int dist) {
    int i = heapSize++;
    heap[i].v = v;
    heap[i].dist = dist;

    // Sift Up
    while (i > 0 && heap[(i - 1) / 2].dist > heap[i].dist) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct HeapNode pop() {
    struct HeapNode minNode = heap[0];
    heap[0] = heap[--heapSize];

    // Sift Down
    int i = 0;
    while (2 * i + 1 < heapSize) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heapSize && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right < heapSize && heap[right].dist < heap[smallest].dist)
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return minNode;
}

int isEmpty() {
    return heapSize == 0;
}

void addEdge(int u, int v, int w, int isDirected) {
    if (u >= 0 && u < n && v >= 0 && v < n) {
        adj[u][v] = w;
        if (!isDirected) adj[v][u] = w;
        printf("Edge (%d -> %d, weight: %d) added successfully.\n", u, v, w);
    } else {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", n - 1);
    }
}

// Print path from source to target recursively
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Dijkstra's Shortest Path Algorithm
void dijkstra(int src) {
    if (src < 0 || src >= n) {
        printf("Invalid source vertex!\n");
        return;
    }

    int dist[MAX];
    int parent[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    heapSize = 0; // Reset heap
    dist[src] = 0;
    push(src, 0);

    while (!isEmpty()) {
        struct HeapNode minNode = pop();
        int u = minNode.v;

        if (visited[u]) continue; // Skip already finalized vertex
        visited[u] = 1;

        // Relax neighbors of u
        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                    push(v, dist[v]);
                }
            }
        }
    }

    printf("\n=======================================================\n");
    printf("   DIJKSTRA'S SHORTEST PATHS FROM SOURCE VERTEX %d    \n", src);
    printf("=======================================================\n");
    printf("Dest \t Distance \t Shortest Path\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%2d \t ", i);
        if (dist[i] == INF) {
            printf("UNREACHABLE \t No Path\n");
        } else {
            printf("%8d \t ", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
    printf("-------------------------------------------------------\n");
}

int main() {
    int choice, u, v, w, src, isDir;

    printf("===================================================\n");
    printf("   DIJKSTRA'S SHORTEST PATH (MIN-HEAP) PROGRAM     \n");
    printf("===================================================\n");
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("Graph type: 1 for Directed, 0 for Undirected: ");
    scanf("%d", &isDir);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Weighted Edge (u, v, weight)\n");
        printf("2. Run Dijkstra's Algorithm from Source\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter endpoints and weight (u v weight): ");
                scanf("%d %d %d", &u, &v, &w);
                addEdge(u, v, w, isDir);
                break;

            case 2:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                dijkstra(src);
                break;

            case 3:
                printf("Exiting. Good luck with your exam!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1 to 3.\n");
        }
    }
    return 0;
}

