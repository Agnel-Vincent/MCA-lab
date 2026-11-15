/*
 * Problem 13: Segment Tree (Range Sum & Range Minimum Query)
 * Implements Segment Tree Construction, Range Queries, and Point Updates.
 */

#include <stdio.h>

#define MAX 50
#define INF 999999

// Segment Tree Node storing both range sum and range minimum
struct SegNode {
    int sum;
    int min;
};

struct SegNode tree[4 * MAX];
int arr[MAX];
int n = 0;

int minVal(int a, int b) {
    return (a < b) ? a : b;
}

// 1. Build Segment Tree in O(N) time
void buildTree(int node, int start, int end) {
    if (start == end) {
        // Leaf node corresponds to a single array element
        tree[node].sum = arr[start];
        tree[node].min = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;

    buildTree(leftChild, start, mid);
    buildTree(rightChild, mid + 1, end);

    // Merge results from left and right children
    tree[node].sum = tree[leftChild].sum + tree[rightChild].sum;
    tree[node].min = minVal(tree[leftChild].min, tree[rightChild].min);
}

// 2. Query Range Sum in O(log N)
int querySum(int node, int start, int end, int l, int r) {
    // Range completely outside query interval
    if (r < start || end < l)
        return 0;

    // Range completely inside query interval
    if (l <= start && end <= r)
        return tree[node].sum;

    // Partial overlap: query both halves
    int mid = (start + end) / 2;
    int leftSum = querySum(2 * node, start, mid, l, r);
    int rightSum = querySum(2 * node + 1, mid + 1, end, l, r);
    return leftSum + rightSum;
}

// 3. Query Range Minimum in O(log N)
int queryMin(int node, int start, int end, int l, int r) {
    // Range completely outside query interval
    if (r < start || end < l)
        return INF;

    // Range completely inside query interval
    if (l <= start && end <= r)
        return tree[node].min;

    // Partial overlap: query both halves
    int mid = (start + end) / 2;
    int leftMin = queryMin(2 * node, start, mid, l, r);
    int rightMin = queryMin(2 * node + 1, mid + 1, end, l, r);
    return minVal(leftMin, rightMin);
}

// 4. Point Update in O(log N)
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        tree[node].sum = val;
        tree[node].min = val;
        return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid)
        update(2 * node, start, mid, idx, val);
    else
        update(2 * node + 1, mid + 1, end, idx, val);

    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].min = minVal(tree[2 * node].min, tree[2 * node + 1].min);
}

// Display array
void displayArray() {
    printf("\nCurrent Array [Index: Value]:\n");
    for (int i = 0; i < n; i++) {
        printf("[%d]: %d   ", i, arr[i]);
    }
    printf("\n");
}

int main() {
    int choice, l, r, idx, val;

    printf("===================================================\n");
    printf("   SEGMENT TREE (RANGE SUM & RANGE MIN QUERY)      \n");
    printf("===================================================\n");
    printf("Enter number of elements in array (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter %d space-separated integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Build the tree (root node is at index 1)
    buildTree(1, 0, n - 1);
    printf("Segment Tree successfully built!\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Query Range Sum [L, R]\n");
        printf("2. Query Range Minimum [L, R]\n");
        printf("3. Update Element at Index [idx = val]\n");
        printf("4. Display Current Array\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter range endpoints (L R) [0 to %d]: ", n - 1);
                scanf("%d %d", &l, &r);
                if (l >= 0 && r < n && l <= r) {
                    printf("Range Sum [%d, %d] = %d\n", l, r, querySum(1, 0, n - 1, l, r));
                } else {
                    printf("Invalid range indices!\n");
                }
                break;

            case 2:
                printf("Enter range endpoints (L R) [0 to %d]: ", n - 1);
                scanf("%d %d", &l, &r);
                if (l >= 0 && r < n && l <= r) {
                    printf("Range Minimum [%d, %d] = %d\n", l, r, queryMin(1, 0, n - 1, l, r));
                } else {
                    printf("Invalid range indices!\n");
                }
                break;

            case 3:
                printf("Enter index to update (0 to %d) and new value (idx val): ", n - 1);
                scanf("%d %d", &idx, &val);
                if (idx >= 0 && idx < n) {
                    update(1, 0, n - 1, idx, val);
                    printf("Successfully updated index %d to value %d.\n", idx, val);
                } else {
                    printf("Invalid array index!\n");
                }
                break;

            case 4:
                displayArray();
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

