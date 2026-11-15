/*
 * Problem 9: AVL Tree (Self-Balancing Binary Search Tree)
 * Implements Insertion, Deletion, and Rotations (LL, RR, LR, RL) to maintain balance.
 */

#include <stdio.h>
#include <stdlib.h>

// AVL Node Structure
struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
};

// Utility function to get height of node
int height(struct Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new AVL node
struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->height = 1; // New node is initially added at leaf
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Get Balance factor of node N: height(left) - height(right)
int getBalance(struct Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Right Rotation (LL Case)
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

// Left Rotation (RR Case)
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

// Recursive Insert into AVL Tree
struct Node* insert(struct Node* node, int key) {
    // 1. Normal BST Insertion
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        printf("Key %d already exists in AVL tree!\n", key);
        return node;
    }

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor to check if this node became unbalanced
    int balance = getBalance(node);

    // LL Case (Left-Left)
    if (balance > 1 && key < node->left->key) {
        printf("Rebalancing: LL Rotation applied at Node %d\n", node->key);
        return rightRotate(node);
    }

    // RR Case (Right-Right)
    if (balance < -1 && key > node->right->key) {
        printf("Rebalancing: RR Rotation applied at Node %d\n", node->key);
        return leftRotate(node);
    }

    // LR Case (Left-Right)
    if (balance > 1 && key > node->left->key) {
        printf("Rebalancing: LR Rotation applied at Node %d\n", node->key);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case (Right-Left)
    if (balance < -1 && key < node->right->key) {
        printf("Rebalancing: RL Rotation applied at Node %d\n", node->key);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find node with minimum key value (in-order successor)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Recursive Delete from AVL Tree
struct Node* deleteNode(struct Node* root, int key) {
    // 1. Standard BST Deletion
    if (root == NULL) {
        printf("Key %d not found in AVL tree!\n", key);
        return root;
    }

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) { // No child
                temp = root;
                root = NULL;
            } else { // One child
                *root = *temp;
            }
            free(temp);
            printf("Successfully deleted key %d.\n", key);
        } else {
            // Node with two children: get in-order successor
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    // 2. Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Balance factor
    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        printf("Rebalancing after deletion: LL Rotation at Node %d\n", root->key);
        return rightRotate(root);
    }

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        printf("Rebalancing after deletion: LR Rotation at Node %d\n", root->key);
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        printf("Rebalancing after deletion: RR Rotation at Node %d\n", root->key);
        return leftRotate(root);
    }

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        printf("Rebalancing after deletion: RL Rotation at Node %d\n", root->key);
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal: displays sorted keys and balance factor
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d [BF=%d, H=%d]  ", root->key, getBalance(root), root->height);
        inorder(root->right);
    }
}

// 2D tree visualizer
void printTree2D(struct Node *root, int space) {
    if (root == NULL) return;
    space += 6;
    printTree2D(root->right, space);
    printf("\n");
    for (int i = 6; i < space; i++) printf(" ");
    printf("%d(BF:%d)\n", root->key, getBalance(root));
    printTree2D(root->left, space);
}

int main() {
    struct Node *root = NULL;
    int choice, key;

    printf("===================================================\n");
    printf("         AVL TREE BALANCING PROGRAM                \n");
    printf("===================================================\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Insert Key\n");
        printf("2. Delete Key\n");
        printf("3. In-order Traversal (Sorted with BF)\n");
        printf("4. Display 2D Tree Structure\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                printf("Enter integer key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 3:
                printf("\nIn-order Traversal: ");
                if (root == NULL) printf("Tree is EMPTY.\n");
                else {
                    inorder(root);
                    printf("\n");
                }
                break;

            case 4:
                printf("\n--- AVL Tree Structure (rotated 90 deg counter-clockwise) ---\n");
                if (root == NULL) printf("Tree is EMPTY.\n");
                else printTree2D(root, 0);
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

