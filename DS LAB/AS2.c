
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
typedef struct Node {
    int id;
    char title[40];
    struct Node *next;
} Node;

// Add song at the end
Node *append(Node *head, int id, const char *title) {
    Node *n = malloc(sizeof *n);

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    n->id = id;
    snprintf(n->title, sizeof n->title, "%s", title);
    n->next = NULL;

    if (head == NULL)
        return n;

    Node *p = head;

    while (p->next != NULL)
        p = p->next;

    p->next = n;

    return head;
}

// Remove song using ID
Node *remove_song(Node *head, int id) {
    Node *p = head;
    Node *prev = NULL;

    while (p != NULL && p->id != id) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Song ID %d not found.\n", id);
        return head;
    }

    if (prev == NULL)
        head = p->next;
    else
        prev->next = p->next;

    free(p);

    printf("Song ID %d removed successfully.\n", id);

    return head;
}

// Reverse playlist
Node *reverse(Node *head) {
    Node *prev = NULL;
    Node *cur = head;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

// Display playlist
void display(const Node *p) {
    if (p == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    while (p != NULL) {
        printf("%d : %s -> ", p->id, p->title);
        p = p->next;
    }

    printf("NULL\n");
}

// Free allocated memory
void free_list(Node *p) {
    while (p != NULL) {
        Node *n = p->next;
        free(p);
        p = n;
    }
}

// Main function
int main(void) {
    Node *head = NULL;

    printf("MUSIC PLAYLIST MANAGEMENT SYSTEM\n");

    // Add songs
    printf("\n1. Adding Songs\n");

    head = append(head, 1, "Alpha");
    head = append(head, 2, "Bravo");
    head = append(head, 3, "Charlie");

    printf("\nOriginal Playlist:\n");
    display(head);

    // Remove song
    printf("\n2. Removing Song ID 2\n");

    head = remove_song(head, 2);

    printf("\nUpdated Playlist:\n");
    display(head);

    // Reverse playlist
    printf("\n3. Reversing Playlist\n");

    head = reverse(head);

    printf("\nReversed Playlist:\n");
    display(head);

    // Release memory
    free_list(head);
    head = NULL;

    printf("\nMemory released successfully.\n");
    printf("Program executed successfully.\n");

    return 0;
}
