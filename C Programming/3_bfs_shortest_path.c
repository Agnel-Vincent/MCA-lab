/*
 * Problem 3: Interactive BFS Traversal & Shortest Path in Unweighted Graph
 * Allows examiner to enter vertices, edges, run BFS, and query shortest paths.
 */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int n; // Number of vertices

// Array-based Queue
int q[MAX], front = 0, rear = 0;

void addEdge(int u, int v) {
    if (u >= 0 && u < n && v >= 0 && v < n) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Undirected edge
        printf("Edge (%d - %d) added successfully.\n", u, v);
    } else {
        printf("Invalid vertices! Vertices must be between 0 and %d.\n", n - 1);
    }
}

// 1. BFS Traversal
void bfs(int start) {
    if (start < 0 || start >= n) {
        printf("Invalid start vertex!\n");
        return;
    }

    int visited[MAX] = {0};
    front = rear = 0; // Reset queue

    visited[start] = 1;
    q[rear++] = start;

    printf("\nBFS Traversal Order starting from %d: ", start);
    while (front < rear) {
        int u = q[front++];
        printf("%d ", u);

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                q[rear++] = v;
            }
        }
    }
    printf("\n");
}

// 2. Shortest Path using BFS
void shortestPath(int src, int dest) {
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        printf("Invalid source or destination vertex!\n");
        return;
    }

    int visited[MAX] = {0}, dist[MAX], parent[MAX];
    for (int i = 0; i < n; i++) dist[i] = -1, parent[i] = -1;

    front = rear = 0;
    visited[src] = 1;
    dist[src] = 0;
    q[rear++] = src;

    while (front < rear) {
        int u = q[front++];
        if (u == dest) break;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q[rear++] = v;
            }
        }
    }

    if (dist[dest] == -1) {
        printf("\nNo path exists between vertex %d and vertex %d.\n", src, dest);
        return;
    }

    printf("\nShortest Distance from %d to %d: %d edge(s)\n", src, dest, dist[dest]);
    printf("Reconstructed Path: ");
    int path[MAX], count = 0, curr = dest;
    while (curr != -1) {
        path[count++] = curr;
        curr = parent[curr];
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%d%s", path[i], (i > 0) ? " -> " : "\n");
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
    int choice, u, v, src, dest;

    printf("========================================\n");
    printf("   BFS & SHORTEST PATH LAB PROGRAM     \n");
    printf("========================================\n");
    printf("Enter number of vertices in graph (max %d): ", MAX);
    scanf("%d", &n);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Edge (u, v)\n");
        printf("2. Run BFS Traversal\n");
        printf("3. Find Shortest Path between (src, dest)\n");
        printf("4. Display Adjacency Matrix\n");
        printf("5. Exit\n");
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
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &src);
                bfs(src);
                break;

            case 3:
                printf("Enter source and destination (src dest): ");
                scanf("%d %d", &src, &dest);
                shortestPath(src, dest);
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
