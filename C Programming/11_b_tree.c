/*
 * Problem 11: B-Tree of Order M (Multi-level Indexing Structure)
 * Implements Insertion and Traversal for balanced multi-way indexing.
 */

#include <stdio.h>
#include <stdlib.h>

#define M 4 // Order of B-Tree (Each node holds max M-1 keys, max M children)

// B-Tree Node Structure
struct BTreeNode {
    int keys[M - 1];              // Array of keys
    struct BTreeNode *child[M];   // Array of child pointers
    int count;                    // Current number of keys
    int isLeaf;                   // 1 if leaf node, 0 otherwise
};

struct BTreeNode *root = NULL;

// Create a new B-Tree Node
struct BTreeNode* createNode(int isLeaf) {
    struct BTreeNode *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->count = 0;
    newNode->isLeaf = isLeaf;
    for (int i = 0; i < M; i++) {
        newNode->child[i] = NULL;
    }
    return newNode;
}

// In-order traversal across all keys and children
void inorder(struct BTreeNode *node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->count; i++) {
            inorder(node->child[i]);
            printf("%d ", node->keys[i]);
        }
        inorder(node->child[i]);
    }
}

// Search for a key in B-Tree
int search(struct BTreeNode *node, int key) {
    if (node == NULL) return 0;

    int i = 0;
    while (i < node->count && key > node->keys[i])
        i++;

    if (i < node->count && key == node->keys[i])
        return 1; // Key found

    if (node->isLeaf)
        return 0; // Key not in tree

    return search(node->child[i], key);
}

// Split full child y of node x at child index i
void splitChild(struct BTreeNode *x, int i, struct BTreeNode *y) {
    int mid = (M - 1) / 2; // Median key position

    // Create a new node z to store keys after median
    struct BTreeNode *z = createNode(y->isLeaf);
    z->count = (M - 1) - mid - 1;

    // Copy the last keys of y to z
    for (int j = 0; j < z->count; j++) {
        z->keys[j] = y->keys[j + mid + 1];
    }

    // Copy child pointers if y is not a leaf
    if (!y->isLeaf) {
        for (int j = 0; j <= z->count; j++) {
            z->child[j] = y->child[j + mid + 1];
        }
    }

    y->count = mid;

    // Shift child pointers of x to make room for z
    for (int j = x->count; j >= i + 1; j--) {
        x->child[j + 1] = x->child[j];
    }
    x->child[i + 1] = z;

    // Shift keys of x to move median of y up into x
    for (int j = x->count - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[mid];
    x->count++;
}

// Insert key into a non-full B-Tree node
void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->count - 1;

    if (node->isLeaf) {
        // Find position and insert key in sorted order
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->count++;
    } else {
        // Find appropriate child
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        // If the chosen child is full, split it first
        if (node->child[i]->count == M - 1) {
            splitChild(node, i, node->child[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->child[i], key);
    }
}

// Main Insert into B-Tree
void insert(int key) {
    if (search(root, key)) {
        printf("Key %d already exists in B-Tree!\n", key);
        return;
    }

    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->count = 1;
        printf("Inserted %d as new root.\n", key);
        return;
    }

    // If root is full, tree grows in height
    if (root->count == M - 1) {
        struct BTreeNode *newRoot = createNode(0);
        newRoot->child[0] = root;
        splitChild(newRoot, 0, root);

        int i = 0;
        if (newRoot->keys[0] < key) i++;
        insertNonFull(newRoot->child[i], key);

        root = newRoot;
        printf("Root was full! Split root and inserted %d (Tree height increased).\n", key);
    } else {
        insertNonFull(root, key);
        printf("Inserted %d successfully.\n", key);
    }
}

// Display B-Tree levels hierarchically
void display(struct BTreeNode *node, int level) {
    if (node != NULL) {
        printf("Level %d: [ ", level);
        for (int i = 0; i < node->count; i++) {
            printf("%d ", node->keys[i]);
        }
        printf("]\n");

        for (int i = 0; i <= node->count; i++) {
            display(node->child[i], level + 1);
        }
    }
}

int main() {
    int choice, key;

    printf("===================================================\n");
    printf("       B-TREE OF ORDER %d INDEXING PROGRAM          \n", M);
    printf("===================================================\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Insert Key\n");
        printf("2. Search Key\n");
        printf("3. Display In-order Traversal (Sorted)\n");
        printf("4. Display Hierarchical Tree Levels\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key)) {
                    printf("Key %d FOUND in B-Tree.\n", key);
                } else {
                    printf("Key %d NOT found in B-Tree.\n", key);
                }
                break;

            case 3:
                printf("\nIn-order Traversal: ");
                if (root == NULL) printf("B-Tree is EMPTY.\n");
                else {
                    inorder(root);
                    printf("\n");
                }
                break;

            case 4:
                printf("\n--- Hierarchical B-Tree Levels ---\n");
                if (root == NULL) printf("B-Tree is EMPTY.\n");
                else display(root, 0);
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

