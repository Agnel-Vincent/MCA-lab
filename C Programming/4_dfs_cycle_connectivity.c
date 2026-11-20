/*
 * Problem 4: Interactive DFS Traversal, Cycle Detection & Connectivity Checking
 * Allows examiner to add edges, run DFS, test for cycles, and verify connectivity.
 */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int n; // Number of vertices
int visited[MAX];

void addEdge(int u, int v) {
    if (u >= 0 && u < n && v >= 0 && v < n) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Undirected edge
        printf("Edge (%d - %d) added successfully.\n", u, v);
    } else {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", n - 1);
    }
}

// 1. Recursive DFS Traversal
void dfs(int u) {
    visited[u] = 1;
    printf("%d ", u);

    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

// 2. Cycle Detection in Undirected Graph
// Condition: Visited neighbor that is not the parent implies a back-edge (cycle).
int isCyclic(int u, int parent) {
    visited[u] = 1;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                if (isCyclic(v, u)) return 1;
            } else if (v != parent) {
                return 1; // Found back-edge
            }
        }
    }
    return 0;
}

void detectCycle() {
    for (int i = 0; i < n; i++) visited[i] = 0;

    int cycle_found = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (isCyclic(i, -1)) {
                cycle_found = 1;
                break;
            }
        }
    }

    if (cycle_found) {
        printf("\nResult: Graph CONTAINS a cycle.\n");
    } else {
        printf("\nResult: Graph DOES NOT contain any cycle (Acyclic / Forest).\n");
    }
}

// 3. Connectivity Checking & Component Enumeration
void checkConnectivity() {
    for (int i = 0; i < n; i++) visited[i] = 0;

    int components = 0;
    printf("\n--- Connected Components Inspection ---\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            printf("Component %d: ", components);
            dfs(i);
            printf("\n");
        }
    }

    if (components == 1) {
        printf("Result: Graph is CONNECTED (All vertices belong to 1 component).\n");
    } else {
        printf("Result: Graph is DISCONNECTED (Split into %d distinct components).\n", components);
    }
}

void displayAdj() {
    printf("\n--- Adjacency Matrix (%d x %d) ---\n    ", n, n);
    for (int i = 0; i < n; i++) printf("%d ", i);
    printf("\n   ");
    for (int i = 0; i < n; i++) printf("--");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        for (int j = 0; j < n; j++) printf("%d ", adj[i][j]);
        printf("\n");
    }
}

int main() {
    int choice, u, v, start;

    printf("===================================================\n");
    printf("   DFS, CYCLE DETECTION & CONNECTIVITY LAB PROGRAM \n");
    printf("===================================================\n");
    printf("Enter number of vertices in graph (max %d): ", MAX);
    scanf("%d", &n);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Edge (u, v)\n");
        printf("2. Run DFS Traversal from start vertex\n");
        printf("3. Check for Cycles\n");
        printf("4. Check Graph Connectivity\n");
        printf("5. Display Adjacency Matrix\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter edge endpoints (u v): ");
                scanf("%d %d", &u, &v);
                addEdge(u, v);
                break;

            case 2:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &start);
                if (start >= 0 && start < n) {
                    for (int i = 0; i < n; i++) visited[i] = 0;
                    printf("DFS Traversal from %d: ", start);
                    dfs(start);
                    printf("\n");
                } else {
                    printf("Invalid start vertex!\n");
                }
                break;

            case 3:
                detectCycle();
                break;

            case 4:
                checkConnectivity();
                break;

            case 5:
                displayAdj();
                break;

            case 6:
                printf("Exiting. Good luck with your exam!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1 to 6.\n");
        }
    }
    return 0;
}
