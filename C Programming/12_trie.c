/*
 * Problem 12: Trie (Prefix Tree)
 * Implements Fast String Search and Autocomplete Functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 100

// Trie Node Structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Create a new Trie node
struct TrieNode* createNode() {
    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Convert character to lowercase index 0-25
int getIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

// 1. Insert word into Trie
void insert(struct TrieNode *root, const char *word) {
    struct TrieNode *curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = getIndex(word[i]);
        if (index == -1) continue; // Skip non-alphabetic chars

        if (curr->children[index] == NULL) {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = 1;
    printf("Successfully inserted word: \"%s\"\n", word);
}

// 2. Search for exact word in Trie
int search(struct TrieNode *root, const char *word) {
    struct TrieNode *curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = getIndex(word[i]);
        if (index == -1 || curr->children[index] == NULL) {
            return 0; // Character path does not exist
        }
        curr = curr->children[index];
    }
    return (curr != NULL && curr->isEndOfWord);
}

// Helper to recursively collect and print all words matching prefix
void autocompleteDFS(struct TrieNode *node, char *prefix, int length, int *matchCount) {
    if (node == NULL) return;

    if (node->isEndOfWord) {
        prefix[length] = '\0';
        printf("  -> %s\n", prefix);
        (*matchCount)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            prefix[length] = 'a' + i;
            autocompleteDFS(node->children[i], prefix, length + 1, matchCount);
        }
    }
}

// 3. Autocomplete suggestions by prefix
void autocomplete(struct TrieNode *root, const char *prefix) {
    struct TrieNode *curr = root;
    char buffer[MAX_WORD_LEN];
    int len = 0;

    // Traverse down to end of prefix
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = getIndex(prefix[i]);
        if (index == -1 || curr->children[index] == NULL) {
            printf("No autocomplete suggestions found for prefix \"%s\".\n", prefix);
            return;
        }
        buffer[len++] = 'a' + index;
        curr = curr->children[index];
    }

    int matchCount = 0;
    printf("\nAutocomplete Suggestions for prefix \"%s\":\n", prefix);
    autocompleteDFS(curr, buffer, len, &matchCount);

    if (matchCount == 0) {
        printf("No words found matching this prefix.\n");
    } else {
        printf("Found %d suggestion(s).\n", matchCount);
    }
}

// 4. Display all words currently stored in Trie
void displayAll(struct TrieNode *root) {
    char buffer[MAX_WORD_LEN];
    int count = 0;
    printf("\n--- All Words Stored in Trie ---\n");
    autocompleteDFS(root, buffer, 0, &count);
    if (count == 0) printf("Trie is currently EMPTY.\n");
    else printf("Total words: %d\n", count);
}

int main() {
    struct TrieNode *root = createNode();
    int choice;
    char word[MAX_WORD_LEN];

    printf("===================================================\n");
    printf("     TRIE (PREFIX TREE) & AUTOCOMPLETE PROGRAM     \n");
    printf("===================================================\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Insert Word\n");
        printf("2. Search Exact Word\n");
        printf("3. Autocomplete / Prefix Search\n");
        printf("4. Display All Stored Words\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word to insert (alphabetic): ");
                scanf("%s", word);
                insert(root, word);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);
                if (search(root, word)) {
                    printf("Result: Word \"%s\" EXISTS in Trie.\n", word);
                } else {
                    printf("Result: Word \"%s\" NOT found in Trie.\n", word);
                }
                break;

            case 3:
                printf("Enter prefix for autocomplete: ");
                scanf("%s", word);
                autocomplete(root, word);
                break;

            case 4:
                displayAll(root);
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

