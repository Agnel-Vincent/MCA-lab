/*
 * Problem 10: Red-Black Tree (Self-Balancing Binary Search Tree)
 * Implements Insertion and Deletion with explicit adherence to Red-Black Balancing Rules.
 */

#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

// Red-Black Tree Node Structure
struct Node {
    int data;
    int color; // 0 = RED, 1 = BLACK
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create new node (Rule: New node is always RED)
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = RED; // Rule 5: Newly inserted node is RED
    node->left = node->right = node->parent = NULL;
    return node;
}

// Left Rotation
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right Rotation
void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix violations caused by BST insertion
void fixInsert(struct Node *z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node *uncle = z->parent->parent->right;
            // Case 1: Uncle is RED -> Recolor parent, uncle, and grandparent
            if (uncle != NULL && uncle->color == RED) {
                printf("Fix: Uncle is RED. Recolor parent & uncle to BLACK, grandparent to RED.\n");
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: Uncle is BLACK and z is right child (LR case)
                if (z == z->parent->right) {
                    printf("Fix: LR Case -> Left Rotate parent.\n");
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: Uncle is BLACK and z is left child (LL case)
                printf("Fix: LL Case -> Recolor parent to BLACK, grandparent to RED, Right Rotate grandparent.\n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            // Symmetric cases when parent is right child of grandparent
            struct Node *uncle = z->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                printf("Fix: Uncle is RED. Recolor parent & uncle to BLACK, grandparent to RED.\n");
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    printf("Fix: RL Case -> Right Rotate parent.\n");
                    z = z->parent;
                    rightRotate(z);
                }
                printf("Fix: RR Case -> Recolor parent to BLACK, grandparent to RED, Left Rotate grandparent.\n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK; // Rule 2: Root is always BLACK
}

// Insert an element into Red-Black Tree
void insert(int data) {
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    // Standard BST search for insertion location
    while (x != NULL) {
        y = x;
        if (z->data < x->data) x = x->left;
        else if (z->data > x->data) x = x->right;
        else {
            printf("Key %d already exists in Red-Black Tree!\n", data);
            free(z);
            return;
        }
    }

    z->parent = y;
    if (y == NULL) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;

    printf("Inserted %d as RED node.\n", data);
    fixInsert(z);
}

// Helper to replace subtree u with subtree v
void rbTransplant(struct Node *u, struct Node *v) {
    if (u->parent == NULL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v != NULL) v->parent = u->parent;
}

// Find minimum node in subtree
struct Node* minimum(struct Node *node) {
    while (node->left != NULL) node = node->left;
    return node;
}

// Fix violations caused by BST deletion (Double-Black fixup)
void fixDelete(struct Node *x, struct Node *xParent) {
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (x == xParent->left) {
            struct Node *w = xParent->right;
            // Case 1: Sibling is RED
            if (w != NULL && w->color == RED) {
                printf("Delete Fix Case 1: Sibling RED -> Recolor and Left Rotate parent.\n");
                w->color = BLACK;
                xParent->color = RED;
                leftRotate(xParent);
                w = xParent->right;
            }
            // Case 2: Sibling is BLACK and both children are BLACK
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                printf("Delete Fix Case 2: Sibling children BLACK -> Recolor sibling to RED.\n");
                if (w != NULL) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Case 3: Sibling is BLACK, right child BLACK, left child RED
                if (w->right == NULL || w->right->color == BLACK) {
                    printf("Delete Fix Case 3: Sibling right child BLACK -> Rotate sibling.\n");
                    if (w->left != NULL) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = xParent->right;
                }
                // Case 4: Sibling is BLACK, right child RED
                printf("Delete Fix Case 4: Sibling right child RED -> Rotate parent & resolve.\n");
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->right != NULL) w->right->color = BLACK;
                leftRotate(xParent);
                x = root;
                break;
            }
        } else {
            // Symmetric cases when x is right child
            struct Node *w = xParent->left;
            if (w != NULL && w->color == RED) {
                printf("Delete Fix Case 1: Sibling RED -> Recolor and Right Rotate parent.\n");
                w->color = BLACK;
                xParent->color = RED;
                rightRotate(xParent);
                w = xParent->left;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                printf("Delete Fix Case 2: Sibling children BLACK -> Recolor sibling to RED.\n");
                if (w != NULL) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    printf("Delete Fix Case 3: Sibling left child BLACK -> Rotate sibling.\n");
                    if (w->right != NULL) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = xParent->left;
                }
                printf("Delete Fix Case 4: Sibling left child RED -> Rotate parent & resolve.\n");
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->left != NULL) w->left->color = BLACK;
                rightRotate(xParent);
                x = root;
                break;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
}

// Delete an element from Red-Black Tree
void deleteKey(int data) {
    struct Node *z = root;
    while (z != NULL && z->data != data) {
        if (data < z->data) z = z->left;
        else z = z->right;
    }

    if (z == NULL) {
        printf("Key %d not found in Red-Black Tree!\n", data);
        return;
    }

    struct Node *y = z;
    struct Node *x = NULL;
    struct Node *xParent = NULL;
    int originalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        xParent = z->parent;
        rbTransplant(z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        xParent = z->parent;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            xParent = y;
        } else {
            xParent = y->parent;
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);
    printf("Deleted key %d.\n", data);

    if (originalColor == BLACK) {
        fixDelete(x, xParent);
    }
}

// In-order traversal showing colors
void inorder(struct Node *n) {
    if (n != NULL) {
        inorder(n->left);
        printf("%d(%s) ", n->data, n->color == RED ? "RED" : "BLACK");
        inorder(n->right);
    }
}

// 2D visual tree layout
void printTree2D(struct Node *n, int space) {
    if (n == NULL) return;
    space += 7;
    printTree2D(n->right, space);
    printf("\n");
    for (int i = 7; i < space; i++) printf(" ");
    printf("%d[%c]\n", n->data, n->color == RED ? 'R' : 'B');
    printTree2D(n->left, space);
}

int main() {
    int choice, val;

    printf("===================================================\n");
    printf("        RED-BLACK TREE BALANCING PROGRAM           \n");
    printf("===================================================\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Insert Key\n");
        printf("2. Delete Key\n");
        printf("3. Display In-order Traversal (with colors)\n");
        printf("4. Display 2D Tree Structure\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer key to insert: ");
                scanf("%d", &val);
                insert(val);
                break;

            case 2:
                printf("Enter integer key to delete: ");
                scanf("%d", &val);
                deleteKey(val);
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
                printf("\n--- Red-Black Tree Structure ([R]=RED, [B]=BLACK) ---\n");
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

