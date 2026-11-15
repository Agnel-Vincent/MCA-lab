/*
 * Problem 15: Topological Sorting of Directed Acyclic Graph (DAG)
 * Implements both DFS-based and BFS-based (Kahn's Algorithm) methods.
 */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int n; // Number of vertices

void addEdge(int u, int v) {
    if (u >= 0 && u < n && v >= 0 && v < n) {
        adj[u][v] = 1; // Directed edge u -> v
        printf("Directed Edge (%d -> %d) added successfully.\n", u, v);
    } else {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", n - 1);
    }
}

// 1. DFS-based Topological Sort
// visited: 0 = unvisited, 1 = visiting (on stack), 2 = visited
int dfsTopo(int u, int visited[], int stack[], int *top) {
    visited[u] = 1; // Mark as currently visiting

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (visited[v] == 1) {
                return 0; // Found back-edge! Cycle detected, not a DAG!
            }
            if (visited[v] == 0) {
                if (!dfsTopo(v, visited, stack, top))
                    return 0;
            }
        }
    }

    visited[u] = 2; // Mark as completely processed
    stack[++(*top)] = u; // Push to finish stack
    return 1;
}

void runDFSTopologicalSort() {
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            if (!dfsTopo(i, visited, stack, &top)) {
                printf("\nError: Graph CONTAINS A CYCLE! Topological sort is not possible on cyclic graphs.\n");
                return;
            }
        }
    }

    printf("\n--- Topological Sort Result (DFS Method) ---\nOrder: ");
    while (top >= 0) {
        printf("%d%s", stack[top], (top > 0) ? " -> " : "\n");
        top--;
    }
}

// 2. BFS-based Topological Sort (Kahn's Algorithm)
void runBFSTopologicalSort() {
    int inDegree[MAX] = {0};
    int q[MAX], front = 0, rear = 0;
    int topoOrder[MAX], topoCount = 0;

    // Step 1: Calculate in-degree of all vertices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j]) {
                inDegree[j]++;
            }
        }
    }

    // Step 2: Enqueue all vertices with in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q[rear++] = i;
        }
    }

    // Step 3: Process queue
    while (front < rear) {
        int u = q[front++];
        topoOrder[topoCount++] = u;

        // Reduce in-degree of neighbors
        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q[rear++] = v;
                }
            }
        }
    }

    // Step 4: Check if cycle exists
    if (topoCount < n) {
        printf("\nError: Graph CONTAINS A CYCLE! Kahn's algorithm processed only %d of %d vertices.\n", topoCount, n);
        return;
    }

    printf("\n--- Topological Sort Result (BFS / Kahn's Algorithm) ---\nOrder: ");
    for (int i = 0; i < topoCount; i++) {
        printf("%d%s", topoOrder[i], (i < topoCount - 1) ? " -> " : "\n");
    }
}

void displayAdj() {
    printf("\n--- Directed Adjacency Matrix (%d x %d) ---\n    ", n, n);
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
    int choice, u, v;

    printf("===================================================\n");
    printf("   TOPOLOGICAL SORTING (DFS & KAHN'S BFS) PROGRAM  \n");
    printf("===================================================\n");
    printf("Enter number of vertices in DAG (max %d): ", MAX);
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Directed Edge (u -> v)\n");
        printf("2. Run Topological Sort using DFS\n");
        printf("3. Run Topological Sort using BFS (Kahn's Algorithm)\n");
        printf("4. Display Adjacency Matrix\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directed edge endpoints (u v for u -> v): ");
                scanf("%d %d", &u, &v);
                addEdge(u, v);
                break;

            case 2:
                runDFSTopologicalSort();
                break;

            case 3:
                runBFSTopologicalSort();
                break;

            case 4:
                displayAdj();
                break;

            case 5:
                printf("Exiting. Good luck with your exam!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1 to 5.\n");
        }
    }
    return 0;
}

