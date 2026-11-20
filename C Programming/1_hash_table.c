/*
 * Problem 1: Interactive Hash Table (Separate Chaining & Open Addressing)
 * Allows examiner to interactively insert, search, and display both techniques.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

/* ========================================================
 * 1. SEPARATE CHAINING DATA STRUCTURE
 * ======================================================== */
struct Node {
    int key;
    int value;
    struct Node* next;
} *chain[SIZE];

int hash(int key) {
    int idx = key % SIZE;
    return (idx < 0) ? idx + SIZE : idx;
}

void insertChain(int k, int v) {
    int h = hash(k);
    for (struct Node* p = chain[h]; p; p = p->next) {
        if (p->key == k) {
            p->value = v;
            printf("Key %d already exists. Updated value to %d.\n", k, v);
            return;
        }
    }
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->key = k; n->value = v;
    n->next = chain[h];
    chain[h] = n;
    printf("Successfully inserted (%d, %d) at Bucket [%d].\n", k, v, h);
}

void searchChain(int k) {
    int h = hash(k);
    for (struct Node* p = chain[h]; p; p = p->next) {
        if (p->key == k) {
            printf("Found! Key: %d -> Value: %d (in Bucket [%d])\n", k, p->value, h);
            return;
        }
    }
    printf("Key %d not found in Separate Chaining Table.\n", k);
}

void displayChain() {
    printf("\n--- Separate Chaining Hash Table ---\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Bucket [%d]: ", i);
        for (struct Node* p = chain[i]; p; p = p->next) {
            printf("(%d, %d) -> ", p->key, p->value);
        }
        printf("NULL\n");
    }
}

/* ========================================================
 * 2. OPEN ADDRESSING (LINEAR PROBING) DATA STRUCTURE
 * ======================================================== */
int oKey[SIZE], oVal[SIZE], used[SIZE];

void insertOpen(int k, int v) {
    int h = hash(k);
    for (int i = 0; i < SIZE; i++) {
        int idx = (h + i) % SIZE;
        if (used[idx] && oKey[idx] == k) {
            oVal[idx] = v;
            printf("Key %d exists. Updated value to %d at Slot [%d].\n", k, v, idx);
            return;
        }
        if (!used[idx]) {
            oKey[idx] = k;
            oVal[idx] = v;
            used[idx] = 1;
            if (i > 0) printf("Collision resolved! Inserted (%d, %d) at Slot [%d] after %d probe(s).\n", k, v, idx, i);
            else printf("Inserted (%d, %d) directly at Slot [%d].\n", k, v, idx);
            return;
        }
    }
    printf("Error: Open Addressing Hash Table is FULL!\n");
}

void searchOpen(int k) {
    int h = hash(k);
    for (int i = 0; i < SIZE; i++) {
        int idx = (h + i) % SIZE;
        if (!used[idx]) break; // Empty slot terminates probe
        if (oKey[idx] == k) {
            printf("Found! Key: %d -> Value: %d (at Slot [%d])\n", k, oVal[idx], idx);
            return;
        }
    }
    printf("Key %d not found in Open Addressing Table.\n", k);
}

void displayOpen() {
    printf("\n--- Open Addressing (Linear Probing) Table ---\n");
    for (int i = 0; i < SIZE; i++) {
        if (used[i]) printf("Slot [%d]: (Key: %d, Value: %d)\n", i, oKey[i], oVal[i]);
        else printf("Slot [%d]: EMPTY\n", i);
    }
}

/* ========================================================
 * INTERACTIVE MAIN CONTROLLER
 * ======================================================== */
int main() {
    int tech = 1, choice, k, v;
    printf("Select Collision Resolution Technique:\n");
    printf("1. Separate Chaining (Linked Lists)\n");
    printf("2. Open Addressing (Linear Probing)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &tech);
    while (1) {
        printf("\n========================================\n");
        printf(" Current Mode: %s\n", (tech == 1) ? "SEPARATE CHAINING" : "OPEN ADDRESSING");
        printf("========================================\n");
        printf("1. Insert Key-Value\n");
        printf("2. Search by Key\n");
        printf("3. Display Hash Table\n");
        printf("4. Switch Technique (1 <-> 2)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Key (integer): ");
                scanf("%d", &k);
                printf("Enter Value (integer): ");
                scanf("%d", &v);
                if (tech == 1) insertChain(k, v);
                else insertOpen(k, v);
                break;
            case 2:
                printf("Enter Key to Search: ");
                scanf("%d", &k);
                if (tech == 1) searchChain(k);
                else searchOpen(k);
                break;
            case 3:
                if (tech == 1) displayChain();
                else displayOpen();
                break;
            case 4:
                tech = (tech == 1) ? 2 : 1;
                printf("Switched technique to: %s\n", (tech == 1) ? "SEPARATE CHAINING" : "OPEN ADDRESSING");
                break;
            case 5:
                printf("Exiting Program. Good luck with your exam!\n");
                return 0;
            default:
                printf("Invalid choice! Please choose 1 to 5.\n");
        }
    }
    return 0;
}
