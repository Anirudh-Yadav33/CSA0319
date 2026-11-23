
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Book status
typedef enum {
    AVAILABLE,
    ISSUED,
    HELD,
    MAINTENANCE
} CopyStatus;

// Book structure
typedef struct {
    int copy_id;
    int title_id;
    int floor_no;
    int section_no;
    int shelf_no;
    int rack_no;
    CopyStatus status;
} BookCopy;

// BookList ADT
typedef struct {
    BookCopy *data;
    size_t count;
    size_t capacity;
} BookList;

// Initialize BookList
int booklist_init(BookList *list) {
    if (list == NULL)
        return 0;

    list->data = NULL;
    list->count = 0;
    list->capacity = 0;

    return 1;
}

// Increase array capacity
static int grow(BookList *list) {
    size_t newcap;

    if (list->capacity == 0)
        newcap = 8;
    else
        newcap = list->capacity * 2;

    BookCopy *p = realloc(list->data,
                          newcap * sizeof(BookCopy));

    if (p == NULL)
        return 0;

    list->data = p;
    list->capacity = newcap;

    return 1;
}

// Insert a book
int booklist_insert(BookList *list, size_t pos, BookCopy item) {
    if (list == NULL || pos > list->count)
        return 0;

    if (list->count == list->capacity) {
        if (!grow(list))
            return 0;
    }

    for (size_t i = list->count; i > pos; --i) {
        list->data[i] = list->data[i - 1];
    }

    list->data[pos] = item;
    list->count++;

    return 1;
}

// Delete a book
int booklist_delete(BookList *list, size_t pos,
                    BookCopy *removed) {
    if (list == NULL || pos >= list->count)
        return 0;

    if (removed != NULL)
        *removed = list->data[pos];

    for (size_t i = pos; i + 1 < list->count; ++i) {
        list->data[i] = list->data[i + 1];
    }

    list->count--;

    return 1;
}

// Display all books
void booklist_print(const BookList *list) {
    if (list == NULL)
        return;

    if (list->count == 0) {
        printf("Book list is empty.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("COPY ID  TITLE ID  STATUS\n");
    printf("---------------------------------------------\n");

    for (size_t i = 0; i < list->count; ++i) {
        printf("%-8d %-9d ",
               list->data[i].copy_id,
               list->data[i].title_id);

        switch (list->data[i].status) {
            case AVAILABLE:
                printf("AVAILABLE\n");
                break;

            case ISSUED:
                printf("ISSUED\n");
                break;

            case HELD:
                printf("HELD\n");
                break;

            case MAINTENANCE:
                printf("MAINTENANCE\n");
                break;
        }
    }

    printf("---------------------------------------------\n");
}

// Search book using Copy ID
int booklist_find(const BookList *list, int id) {
    if (list == NULL)
        return -1;

    for (size_t i = 0; i < list->count; ++i) {
        if (list->data[i].copy_id == id)
            return (int)i;
    }

    return -1;
}

// Release allocated memory
void booklist_destroy(BookList *list) {
    if (list == NULL)
        return;

    free(list->data);

    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

// Main function
int main(void) {
    BookList library;
    BookCopy removed;

    if (!booklist_init(&library)) {
        printf("Initialization failed.\n");
        return 1;
    }

    // Sample book records
    BookCopy b1 = {101, 10, 1, 1, 2, 1, AVAILABLE};
    BookCopy b2 = {102, 10, 1, 1, 2, 2, AVAILABLE};
    BookCopy b3 = {103, 20, 2, 1, 3, 1, ISSUED};
    BookCopy b4 = {104, 30, 2, 2, 1, 1, HELD};

    printf("SMART LIBRARY MANAGEMENT SYSTEM\n");

    // Insert books
    printf("\n1. INSERTING BOOKS\n");

    booklist_insert(&library, 0, b1);
    booklist_insert(&library, 1, b2);
    booklist_insert(&library, 2, b3);
    booklist_insert(&library, 3, b4);

    booklist_print(&library);

    // Search book
    printf("\n2. SEARCHING BOOK ID 102\n");

    int pos = booklist_find(&library, 102);

    if (pos != -1)
        printf("Book found at position %d.\n", pos);
    else
        printf("Book not found.\n");

    // Delete book
    printf("\n3. DELETING BOOK ID 102\n");

    if (booklist_delete(&library, 1, &removed))
        printf("Book ID %d deleted successfully.\n",
               removed.copy_id);
    else
        printf("Deletion failed.\n");

    // Display updated list
    printf("\n4. UPDATED BOOK LIST\n");

    booklist_print(&library);

    // Test invalid deletion
    printf("\n5. TESTING INVALID DELETION\n");

    if (!booklist_delete(&library, 10, NULL))
        printf("Invalid position rejected successfully.\n");

    // Display total records
    printf("\nTotal books: %zu\n", library.count);

    // Release memory
    booklist_destroy(&library);

    printf("\nLibrary memory released successfully.\n");
    printf("Program executed successfully.\n");

    return 0;
}
