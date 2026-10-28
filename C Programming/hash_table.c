#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    int key;
    int value;
    int status;  // 0 = empty, 1 = occupied, 2 = deleted
} Entry;

Node *chain[SIZE];
Entry table[SIZE];

int hash(int key) {
    return (key % SIZE + SIZE) % SIZE;
}

void initStructures(void) {
    for (int i = 0; i < SIZE; i++) {
        chain[i] = NULL;
        table[i].status = 0;
    }
}

// Separate Chaining
void insertChain(int k, int v) {
    int i = hash(k);
    Node *current = chain[i];

    while (current != NULL) {
        if (current->key == k) {
            current->value = v;
            printf("Updated existing key %d in chaining table\n", k);
            return;
        }
        current = current->next;
    }

    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    n->key = k;
    n->value = v;
    n->next = chain[i];
    chain[i] = n;
    printf("Inserted key %d using chaining at index %d\n", k, i);
}

// Linear Probing
void insertOpen(int k, int v) {
    int i = hash(k);

    for (int j = 0; j < SIZE; j++) {
        int p = (i + j) % SIZE;

        if (table[p].status == 0 || table[p].status == 2) {
            table[p].key = k;
            table[p].value = v;
            table[p].status = 1;
            printf("Inserted key %d using open addressing at index %d\n", k, p);
            return;
        }

        if (table[p].status == 1 && table[p].key == k) {
            table[p].value = v;
            printf("Updated existing key %d in open addressing table\n", k);
            return;
        }
    }

    printf("Table Full\n");
}

// Search in both implementations
int search(int k) {
    int i = hash(k);

    // Open addressing search
    for (int j = 0; j < SIZE; j++) {
        int p = (i + j) % SIZE;

        if (table[p].status == 0) {
            break;
        }

        if (table[p].status == 1 && table[p].key == k) {
            printf("Found in open addressing! Value = %d\n", table[p].value);
            return 1;
        }
    }

    // Separate chaining search
    Node *n = chain[i];
    while (n != NULL) {
        if (n->key == k) {
            printf("Found in chaining! Value = %d\n", n->value);
            return 1;
        }
        n = n->next;
    }

    printf("Key not found\n");
    return 0;
}

// Delete from both implementations
void deleteKey(int k) {
    int i = hash(k);

    // Open addressing delete
    for (int j = 0; j < SIZE; j++) {
        int p = (i + j) % SIZE;

        if (table[p].status == 0) {
            break;
        }

        if (table[p].status == 1 && table[p].key == k) {
            table[p].status = 2;
            printf("Key %d deleted from open addressing table\n", k);
            return;
        }
    }

    // Separate chaining delete
    Node *current = chain[i];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->key == k) {
            if (prev == NULL) {
                chain[i] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted from chaining table\n", k);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Key not found\n");
}

void displayStructures(void) {
    printf("\nOpen Addressing Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (table[i].status == 1) {
            printf("Index %d -> (%d, %d)\n", i, table[i].key, table[i].value);
        } else {
            printf("Index %d -> Empty\n", i);
        }
    }

    printf("\nSeparate Chaining Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Bucket %d: ", i);
        Node *current = chain[i];
        if (current == NULL) {
            printf("Empty\n");
            continue;
        }
        while (current != NULL) {
            printf("(%d, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, k, v, method;
    initStructures();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key and value: ");
                scanf("%d %d", &k, &v);
                printf("Choose hashing method:\n1. Separate Chaining\n2. Open Addressing\nEnter method: ");
                scanf("%d", &method);
                if (method == 1) {
                    insertChain(k, v);
                } else if (method == 2) {
                    insertOpen(k, v);
                } else {
                    printf("Invalid method\n");
                }
                break;

            case 2:
                printf("Enter key: ");
                scanf("%d", &k);
                search(k);
                break;

            case 3:
                printf("Enter key: ");
                scanf("%d", &k);
                deleteKey(k);
                break;

            case 4:
                displayStructures();
                break;

            case 5:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}