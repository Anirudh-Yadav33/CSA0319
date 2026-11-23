#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum {
    AVAILABLE, ISSUED, HELD, MAINTENANCE
} CopyStatus;

typedef struct {
    int copy_id;
    int title_id;
    int floor_no, section_no, shelf_no, rack_no;
    CopyStatus status;
} BookCopy;

typedef struct {
    BookCopy *data;
    size_t count;
    size_t capacity;
} BookList;

// Initialize BookList
int booklist_init(BookList *list) {
    if (list == NULL) return 0;

    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
    return 1;
}

// Increase capacity
static int grow(BookList *list) {
    size_t newcap = (list->capacity == 0) ? 4 : list->capacity * 2;

    BookCopy *temp = realloc(list->data,
                             newcap * sizeof(BookCopy));

    if (temp == NULL) return 0;

    list->data = temp;
    list->capacity = newcap;
    return 1;
}

// Insert book
int booklist_insert(BookList *list, size_t pos, BookCopy item) {
    if (list == NULL || pos > list->count)
        return 0;

    if (list->count == list->capacity) {
        if (!grow(list)) return 0;
    }

    for (size_t i = list->count; i > pos; i--) {
        list->data[i] = list->data[i - 1];
    }

    list->data[pos] = item;
    list->count++;

    return 1;
}

// Delete book
int booklist_delete(BookList *list, size_t pos, BookCopy *removed) {
    if (list == NULL || pos >= list->count)
        return 0;

    if (removed != NULL)
        *removed = list->data[pos];

    for (size_t i = pos; i + 1 < list->count; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->count--;
    return 1;
}

// Display books
void booklist_print(const BookList *list) {
    if (list == NULL) return;

    if (list->count == 0) {
        printf("Book list is empty.\n");
        return;
    }

    printf("\n--- LIBRARY BOOK LIST ---\n");

    for (size_t i = 0; i < list->count; i++) {
        BookCopy b = list->data[i];

        printf("Copy ID: %d | Title ID: %d | Floor: %d | "
               "Section: %d | Shelf: %d | Rack: %d | Status: %s\n",
               b.copy_id, b.title_id, b.floor_no,
               b.section_no, b.shelf_no, b.rack_no,
               b.status == AVAILABLE ? "AVAILABLE" :
               b.status == ISSUED ? "ISSUED" :
               b.status == HELD ? "HELD" : "MAINTENANCE");
    }
}

// Search book
int booklist_find(const BookList *list, int id) {
    if (list == NULL) return -1;

    for (size_t i = 0; i < list->count; i++) {
        if (list->data[i].copy_id == id)
            return (int)i;
    }

    return -1;
}

// Free memory
void booklist_destroy(BookList *list) {
    if (list == NULL) return;

    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

// Main function
int main(void) {
    BookList library;
    BookCopy removed;

    booklist_init(&library);

    BookCopy b1 = {101, 10, 1, 1, 2, 1, AVAILABLE};
    BookCopy b2 = {102, 10, 1, 1, 2, 2, AVAILABLE};
    BookCopy b3 = {103, 20, 2, 1, 3, 1, ISSUED};

    printf("Adding books...\n");

    booklist_insert(&library, 0, b1);
    booklist_insert(&library, 1, b2);
    booklist_insert(&library, 2, b3);

    booklist_print(&library);

    printf("\nSearching for Copy ID 102...\n");

    int pos = booklist_find(&library, 102);

    if (pos != -1)
        printf("Book found at position %d\n", pos);
    else
        printf("Book not found.\n");

    printf("\nDeleting Copy ID 102...\n");

    if (booklist_delete(&library, 1, &removed))
        printf("Deleted Copy ID: %d successfully.\n", removed.copy_id);
    else
        printf("Deletion failed.\n");

    booklist_print(&library);

    booklist_destroy(&library);

    printf("\nLibrary memory released successfully.\n");

    return 0;
}
