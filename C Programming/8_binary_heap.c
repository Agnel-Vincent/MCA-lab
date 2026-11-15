/*
 * Problem 8: Binary Heap (Min-Heap and Max-Heap)
 * Implements Insertion, Deletion, and Bottom-Up Heapify Operations.
 */

#include <stdio.h>

#define MAX 50

int heap[MAX];
int heapSize = 0;
int isMinHeap = 1; // 1 for Min-Heap, 0 for Max-Heap

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Compare function: returns 1 if child should move above parent
int compare(int childVal, int parentVal) {
    if (isMinHeap) {
        return childVal < parentVal; // Min-Heap: smaller value has higher priority
    } else {
        return childVal > parentVal; // Max-Heap: larger value has higher priority
    }
}

// 1. Heapify Down (Sift Down) at index i
void heapify(int i) {
    int target = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && compare(heap[left], heap[target]))
        target = left;
    if (right < heapSize && compare(heap[right], heap[target]))
        target = right;

    if (target != i) {
        swap(&heap[i], &heap[target]);
        heapify(target); // Recursively heapify affected subtree
    }
}

// 2. Insert key into Heap
void insert(int key) {
    if (heapSize >= MAX) {
        printf("Error: Heap is FULL!\n");
        return;
    }

    int i = heapSize++;
    heap[i] = key;

    // Sift Up
    while (i > 0 && compare(heap[i], heap[(i - 1) / 2])) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("Inserted %d into %s.\n", key, isMinHeap ? "Min-Heap" : "Max-Heap");
}

// 3. Delete Root (Extract Min or Extract Max)
void deleteRoot() {
    if (heapSize <= 0) {
        printf("Error: Heap is EMPTY!\n");
        return;
    }

    int root = heap[0];
    heap[0] = heap[--heapSize];
    heapify(0);

    printf("Extracted root element: %d from %s.\n", root, isMinHeap ? "Min-Heap" : "Max-Heap");
}

// 4. Build Heap from an arbitrary array in O(N) time
void buildHeap() {
    int count;
    printf("Enter number of elements to build heap (max %d): ", MAX);
    scanf("%d", &count);
    if (count <= 0 || count > MAX) {
        printf("Invalid count!\n");
        return;
    }

    printf("Enter %d integers: ", count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &heap[i]);
    }
    heapSize = count;

    // Bottom-up heapify: start from last non-leaf node down to root
    for (int i = (heapSize / 2) - 1; i >= 0; i--) {
        heapify(i);
    }
    printf("Heap successfully built using bottom-up heapify!\n");
}

// 5. Display Heap array
void display() {
    if (heapSize == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("\n--- Current %s (Size: %d) ---\n", isMinHeap ? "Min-Heap" : "Max-Heap", heapSize);
    printf("Array Elements: ");
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    printf("\nParent-Child Tree Layout:\n");
    for (int i = 0; i < heapSize / 2; i++) {
        printf("Node [%d]: Left -> ", heap[i]);
        if (2 * i + 1 < heapSize) printf("%d", heap[2 * i + 1]);
        else printf("-");
        printf(" | Right -> ");
        if (2 * i + 2 < heapSize) printf("%d", heap[2 * i + 2]);
        else printf("-");
        printf("\n");
    }
}

int main() {
    int choice, val;

    printf("===================================================\n");
    printf("   BINARY HEAP (MIN-HEAP & MAX-HEAP) PROGRAM       \n");
    printf("===================================================\n");
    printf("Select Heap Type:\n");
    printf("1. Min-Heap (Root has minimum value)\n");
    printf("2. Max-Heap (Root has maximum value)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);
    isMinHeap = (choice == 1) ? 1 : 0;

    while (1) {
        printf("\n========================================\n");
        printf(" Current Mode: %s\n", isMinHeap ? "MIN-HEAP" : "MAX-HEAP");
        printf("========================================\n");
        printf("1. Insert Element\n");
        printf("2. Delete Root (Extract %s)\n", isMinHeap ? "Min" : "Max");
        printf("3. Display Heap Elements\n");
        printf("4. Build Heap from an Array (Heapify)\n");
        printf("5. Switch Mode (Min-Heap <-> Max-Heap)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;

            case 2:
                deleteRoot();
                break;

            case 3:
                display();
                break;

            case 4:
                buildHeap();
                break;

            case 5:
                isMinHeap = !isMinHeap;
                // Re-heapify existing elements for the new mode
                for (int i = (heapSize / 2) - 1; i >= 0; i--) {
                    heapify(i);
                }
                printf("Switched to: %s and re-heapified array!\n", isMinHeap ? "MIN-HEAP" : "MAX-HEAP");
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

