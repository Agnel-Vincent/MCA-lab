/*
 * Problem 5: Kruskal's Algorithm for Minimum Spanning Tree (MST)
 * Uses Disjoint Set Union (DSU) with Path Compression and Union by Rank.
 */

#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_EDGES 100

// Edge structure
struct Edge {
    int u;
    int v;
    int w;
};

struct Edge edges[MAX_EDGES];
int edgeCount = 0;
int numVertices = 0;

// Disjoint Set Union (DSU) Data Structure
int parent[MAX_VERTICES];
int rnk[MAX_VERTICES];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]); // Path compression
}

int unionSets(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);

    if (rootA == rootB) return 0; // Already in same set, union not performed

    if (rnk[rootA] < rnk[rootB]) {
        parent[rootA] = rootB;
    } else if (rnk[rootA] > rnk[rootB]) {
        parent[rootB] = rootA;
    } else {
        parent[rootB] = rootA;
        rnk[rootA]++;
    }
    return 1; // Successfully united
}

// Simple Bubble Sort to sort edges in non-decreasing order of weight
void sortEdges() {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Add edge to graph
void addEdge(int u, int v, int w) {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", numVertices - 1);
        return;
    }
    if (edgeCount >= MAX_EDGES) {
        printf("Maximum edge capacity reached!\n");
        return;
    }
    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].w = w;
    edgeCount++;
    printf("Edge (%d - %d, weight: %d) added successfully.\n", u, v, w);
}

// Kruskal's MST Algorithm
void kruskalMST() {
    if (edgeCount == 0) {
        printf("No edges in the graph! Please add edges first.\n");
        return;
    }

    sortEdges();
    makeSet(numVertices);

    struct Edge mst[MAX_VERTICES];
    int mstEdges = 0;
    int totalCost = 0;

    printf("\n--- Processing Edges in Kruskal's Algorithm ---\n");
    for (int i = 0; i < edgeCount && mstEdges < numVertices - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (unionSets(u, v)) {
            mst[mstEdges++] = edges[i];
            totalCost += w;
            printf("Selected Edge: (%d - %d) with Weight %d [Accepted]\n", u, v, w);
        } else {
            printf("Discarded Edge: (%d - %d) with Weight %d [Forms a Cycle]\n", u, v, w);
        }
    }

    if (mstEdges < numVertices - 1) {
        printf("\nWarning: Graph is DISCONNECTED! Spanning tree includes only %d of %d vertices.\n", mstEdges + 1, numVertices);
    }

    printf("\n========================================\n");
    printf("     MINIMUM SPANNING TREE (MST) RESULT  \n");
    printf("========================================\n");
    printf("Edge \t\t Weight\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < mstEdges; i++) {
        printf("%d - %d \t\t %d\n", mst[i].u, mst[i].v, mst[i].w);
    }
    printf("----------------------------------------\n");
    printf("Total Minimum Cost (Weight) = %d\n", totalCost);
}

void displayEdges() {
    printf("\n--- All Graph Edges (%d total) ---\n", edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        printf("Edge %2d: (%d - %d) weight = %d\n", i + 1, edges[i].u, edges[i].v, edges[i].w);
    }
}

int main() {
    int choice, u, v, w;

    printf("===================================================\n");
    printf("   KRUSKAL'S MINIMUM SPANNING TREE (MST) PROGRAM   \n");
    printf("===================================================\n");
    printf("Enter number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Weighted Edge (u, v, weight)\n");
        printf("2. Run Kruskal's MST Algorithm\n");
        printf("3. Display All Edges\n");
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
                kruskalMST();
                break;

            case 3:
                displayEdges();
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

