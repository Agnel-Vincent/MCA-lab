/*
 * Problem 6: Prim's Algorithm for Minimum Spanning Tree (MST)
 * Uses a Priority Queue (Min-Heap) for efficient vertex selection.
 */

#include <stdio.h>

#define MAX 20
#define INF 999999

int n; // Number of vertices
int adj[MAX][MAX];

// Min-Heap Node
struct HeapNode {
    int v;
    int key;
};

// Priority Queue (Min-Heap) Implementation
struct HeapNode heap[MAX * MAX];
int heapSize = 0;

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(int v, int key) {
    int i = heapSize++;
    heap[i].v = v;
    heap[i].key = key;

    // Sift Up
    while (i > 0 && heap[(i - 1) / 2].key > heap[i].key) {
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

        if (left < heapSize && heap[left].key < heap[smallest].key)
            smallest = left;
        if (right < heapSize && heap[right].key < heap[smallest].key)
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

void addEdge(int u, int v, int w) {
    if (u >= 0 && u < n && v >= 0 && v < n) {
        adj[u][v] = w;
        adj[v][u] = w; // Undirected graph
        printf("Edge (%d - %d, weight: %d) added successfully.\n", u, v, w);
    } else {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", n - 1);
    }
}

// Prim's Algorithm using Min-Heap
void primMST(int start) {
    if (start < 0 || start >= n) {
        printf("Invalid starting vertex!\n");
        return;
    }

    int key[MAX];
    int parent[MAX];
    int inMST[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        parent[i] = -1;
        inMST[i] = 0;
    }

    heapSize = 0; // Reset priority queue
    key[start] = 0;
    push(start, 0);

    int totalWeight = 0;
    int edgesCount = 0;

    printf("\n--- Prim's MST Execution Steps ---\n");
    while (!isEmpty()) {
        struct HeapNode minNode = pop();
        int u = minNode.v;

        // Skip if already in MST (handles lazy heap entries)
        if (inMST[u]) continue;

        inMST[u] = 1;

        if (parent[u] != -1) {
            printf("Included Edge in MST: (%d - %d) with Weight %d\n", parent[u], u, key[u]);
            totalWeight += key[u];
            edgesCount++;
        }

        // Check all adjacent vertices of u
        for (int v = 0; v < n; v++) {
            int weight = adj[u][v];
            if (weight > 0 && !inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                push(v, key[v]);
            }
        }
    }

    if (edgesCount < n - 1) {
        printf("\nWarning: Graph is DISCONNECTED! MST only connects %d of %d vertices.\n", edgesCount + 1, n);
    }

    printf("\n========================================\n");
    printf("     MINIMUM SPANNING TREE (MST) RESULT  \n");
    printf("========================================\n");
    printf("Edge \t\t Weight\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d - %d \t\t %d\n", parent[i], i, adj[i][parent[i]]);
        }
    }
    printf("----------------------------------------\n");
    printf("Total Minimum Cost (Weight) = %d\n", totalWeight);
}

void displayAdj() {
    printf("\n--- Weighted Adjacency Matrix (%d x %d) ---\n    ", n, n);
    for (int i = 0; i < n; i++) printf("%3d ", i);
    printf("\n   ");
    for (int i = 0; i < n; i++) printf("----");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == 0) printf("  . ");
            else printf("%3d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int choice, u, v, w, start;

    printf("===================================================\n");
    printf("   PRIM'S MINIMUM SPANNING TREE (MST) PROGRAM      \n");
    printf("===================================================\n");
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Weighted Edge (u, v, weight)\n");
        printf("2. Run Prim's MST Algorithm\n");
        printf("3. Display Adjacency Matrix\n");
        printf("4. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter endpoints and weight (u v weight): ");
                scanf("%d %d %d", &u, &v, &w);
                addEdge(u, v, w);
                break;

            case 2:
                printf("Enter starting vertex for Prim's (default 0): ");
                scanf("%d", &start);
                primMST(start);
                break;

            case 3:
                displayAdj();
                break;

            case 4:
                printf("Exiting. Good luck with your exam!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1 to 4.\n");
        }
    }
    return 0;
}

