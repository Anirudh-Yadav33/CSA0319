
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
typedef struct Trie {
    struct Trie *child[26];
    int terminal;
} Trie;

// Create a new Trie node
Trie *newTrie(void) {
    Trie *node = calloc(1, sizeof(Trie));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    return node;
}

// Insert a word
void insert(Trie *root, const char *s) {
    Trie *p = root;

    for (; *s; ++s) {
        int k = *s - 'a';

        if (k < 0 || k >= 26)
            return;

        if (!p->child[k])
            p->child[k] = newTrie();

        p = p->child[k];
    }

    p->terminal = 1;
}

// Search for a complete word
int search(Trie *root, const char *s) {
    Trie *p = root;

    for (; *s; ++s) {
        int k = *s - 'a';

        if (k < 0 || k >= 26 || !p->child[k])
            return 0;

        p = p->child[k];
    }

    return p->terminal;
}

// Check prefix
int startsWith(Trie *root, const char *s) {
    Trie *p = root;

    for (; *s; ++s) {
        int k = *s - 'a';

        if (k < 0 || k >= 26 || !p->child[k])
            return 0;

        p = p->child[k];
    }

    return 1;
}

// Free Trie memory
void freeTrie(Trie *root) {
    if (root == NULL)
        return;

    for (int i = 0; i < 26; i++)
        freeTrie(root->child[i]);

    free(root);
}

// Main function
int main(void) {
    Trie *root = newTrie();

    printf("TRIE DATA STRUCTURE IMPLEMENTATION\n");

    // Insert words
    printf("\n1. INSERTING WORDS\n");

    insert(root, "apple");
    insert(root, "application");
    insert(root, "apply");
    insert(root, "banana");
    insert(root, "bat");

    printf("Inserted: apple, application, apply, banana, bat\n");

    // Search complete words
    printf("\n2. SEARCHING WORDS\n");

    printf("Search apple: %s\n",
           search(root, "apple") ? "FOUND" : "NOT FOUND");

    printf("Search app: %s\n",
           search(root, "app") ? "FOUND" : "NOT FOUND");

    printf("Search banana: %s\n",
           search(root, "banana") ? "FOUND" : "NOT FOUND");

    printf("Search orange: %s\n",
           search(root, "orange") ? "FOUND" : "NOT FOUND");

    // Prefix search
    printf("\n3. PREFIX SEARCH\n");

    printf("Prefix app: %s\n",
           startsWith(root, "app") ? "YES" : "NO");

    printf("Prefix ban: %s\n",
           startsWith(root, "ban") ? "YES" : "NO");

    printf("Prefix cat: %s\n",
           startsWith(root, "cat") ? "YES" : "NO");

    // Free memory
    freeTrie(root);

    printf("\nMemory released successfully.\n");
    printf("Program executed successfully.\n");

    return 0;
}
