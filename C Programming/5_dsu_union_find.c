/*
 * Problem 5: Interactive Disjoint Set Union (Union-Find)
 * Implements Path Compression and Union by Rank for Dynamic Connectivity.
 */

#include <stdio.h>
#define MAX 50
int parent[MAX];
int rnk[MAX];
int n; // Number of elements

// 1. Initialize Disjoint Sets
void makeSet(int total) {
    n = total;
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Each node is initially its own root
        rnk[i] = 0;    // Initial rank is 0
    }
    printf("Initialized %d disjoint sets (0 to %d).\n", n, n - 1);
}

// 2. Find with Path Compression
int findSet(int v) {
    if (v < 0 || v >= n) return -1;
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]); // Path compression
}

// 3. Union by Rank
void unionSets(int a, int b) {
    if (a < 0 || a >= n || b < 0 || b >= n) {
        printf("Invalid elements! Must be between 0 and %d.\n", n - 1);
        return;
    }

    int rootA = findSet(a);
    int rootB = findSet(b);

    if (rootA == rootB) {
        printf("Elements %d and %d are already in the same set (Root = %d).\n", a, b, rootA);
        return;
    }

    // Attach smaller rank tree under larger rank tree
    if (rnk[rootA] < rnk[rootB]) {
        parent[rootA] = rootB;
        printf("Union: Attached Root %d under Root %d (rank unchanged).\n", rootA, rootB);
    } else if (rnk[rootA] > rnk[rootB]) {
        parent[rootB] = rootA;
        printf("Union: Attached Root %d under Root %d (rank unchanged).\n", rootB, rootA);
    } else {
        parent[rootB] = rootA;
        rnk[rootA]++;
        printf("Union: Attached Root %d under Root %d (new rank of %d = %d).\n", rootB, rootA, rootA, rnk[rootA]);
    }
}

// 4. Dynamic Connectivity Check
int isConnected(int a, int b) {
    if (a < 0 || a >= n || b < 0 || b >= n) return 0;
    return findSet(a) == findSet(b);
}

// 5. Display Internal Disjoint Set State
void displaySets() {
    printf("\n--- Disjoint Set Union State ---\n");
    printf("Element: ");
    for (int i = 0; i < n; i++) printf("%2d ", i);
    printf("\nParent:  ");
    for (int i = 0; i < n; i++) printf("%2d ", parent[i]);
    printf("\nRank:    ");
    for (int i = 0; i < n; i++) printf("%2d ", rnk[i]);
    printf("\n");
}

int main() {
    int choice, total, u, v;
    printf("Enter total number of elements (max %d): ", MAX);
    scanf("%d", &total);
    makeSet(total);
    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Union / Connect (u, v)\n");
        printf("2. Find Set Representative (Root) with Path Compression\n");
        printf("3. Check Dynamic Connectivity (Are u and v connected?)\n");
        printf("4. Display Parent and Rank Arrays\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter two elements to union (u v): ");
                scanf("%d %d", &u, &v);
                unionSets(u, v);
                break;
            case 2:
                printf("Enter element to find its root: ");
                scanf("%d", &u);
                v = findSet(u);
                if (v != -1) printf("Root of element %d is: %d (Path Compressed)\n", u, v);
                else printf("Invalid element!\n");
                break;
            case 3:
                printf("Enter two elements to test connectivity (u v): ");
                scanf("%d %d", &u, &v);
                if (isConnected(u, v)) {
                    printf("Dynamic Connectivity: YES, %d and %d are CONNECTED.\n", u, v);
                } else {
                    printf("Dynamic Connectivity: NO, %d and %d are NOT connected.\n", u, v);
                }
                break;
            case 4:
                displaySets();
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
