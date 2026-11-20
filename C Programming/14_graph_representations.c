/*
 * Problem 14: Interactive Graph Representations (Adjacency Matrix & Adjacency List)
 * Allows examiner to add edges, display both structures, and query edge existence.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n; // Number of vertices

// 1. Matrix Representation
int mat[MAX][MAX];

// 2. List Representation
struct Node {
    int v;
    struct Node* next;
} *adj[MAX];

void initGraph(int vertices) {
    n = vertices;
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
        for (int j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }
    printf("Initialized graph with %d vertices (0 to %d).\n", n, n - 1);
}

// Add edge to both Matrix and List
void addEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        printf("Invalid vertices! Must be between 0 and %d.\n", n - 1);
        return;
    }

    // 1. Update Matrix (Undirected)
    mat[u][v] = 1;
    mat[v][u] = 1;

    // 2. Update List (Prepend to head for both u and v)
    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    n1->v = v;
    n1->next = adj[u];
    adj[u] = n1;

    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    n2->v = u;
    n2->next = adj[v];
    adj[v] = n2;

    printf("Edge (%d - %d) added to both Adjacency Matrix and Adjacency List.\n", u, v);
}

// Check edge existence
int hasEdgeMatrix(int u, int v) {
    return mat[u][v];
}

int hasEdgeList(int u, int v) {
    for (struct Node* p = adj[u]; p; p = p->next) {
        if (p->v == v) return 1;
    }
    return 0;
}

// Display Adjacency Matrix
void displayMatrix() {
    printf("\n--- Adjacency Matrix (%d x %d) ---\n    ", n, n);
    for (int i = 0; i < n; i++) printf("%d ", i);
    printf("\n   ");
    for (int i = 0; i < n; i++) printf("--");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        for (int j = 0; j < n; j++) printf("%d ", mat[i][j]);
        printf("\n");
    }
}

// Display Adjacency List
void displayList() {
    printf("\n--- Adjacency List ---\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        struct Node* p = adj[i];
        if (!p) {
            printf("NULL");
        } else {
            while (p) {
                printf("%d -> ", p->v);
                p = p->next;
            }
            printf("NULL");
        }
        printf("\n");
    }
}

int main() {
    int choice, vertices, u, v;

    printf("===================================================\n");
    printf("   GRAPH REPRESENTATION (MATRIX & LIST) PROGRAM    \n");
    printf("===================================================\n");
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &vertices);

    initGraph(vertices);

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Add Edge (u, v)\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Display Adjacency List\n");
        printf("4. Check Edge Existence\n");
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
                displayMatrix();
                break;

            case 3:
                displayList();
                break;

            case 4:
                printf("Enter edge endpoints to check (u v): ");
                scanf("%d %d", &u, &v);
                if (u >= 0 && u < n && v >= 0 && v < n) {
                    printf("Matrix Query: Edge exists? %s\n", hasEdgeMatrix(u, v) ? "YES" : "NO");
                    printf("List Query:   Edge exists? %s\n", hasEdgeList(u, v) ? "YES" : "NO");
                } else {
                    printf("Invalid vertices!\n");
                }
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
