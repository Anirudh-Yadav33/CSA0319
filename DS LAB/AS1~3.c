
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
#define H 17

typedef enum {
    AVAILABLE, ISSUED
} Status;

typedef struct {
    int copy_id, title_id;
    Status status;
} Copy;

typedef struct {
    int key, index, used;
} Entry;

static Copy copies[N];
static Entry index_by_id[H];
static int count = 0, free_count = 0;

// Hash function
static unsigned hash_id(int id) {
    return (unsigned)id % H;
}

// Insert into hash table
static int map_put(int id, int idx) {
    unsigned p = hash_id(id);

    for (int k = 0; k < H; ++k, p = (p + 1) % H) {
        if (!index_by_id[p].used ||
            index_by_id[p].key == id) {
            index_by_id[p] = (Entry){id, idx, 1};
            return 1;
        }
    }
    return 0;
}

// Search in hash table
static int map_get(int id) {
    unsigned p = hash_id(id);

    for (int k = 0; k < H; ++k, p = (p + 1) % H) {
        if (!index_by_id[p].used)
            return -1;

        if (index_by_id[p].key == id)
            return index_by_id[p].index;
    }
    return -1;
}

// Initialize library
static int init_library(void) {
    memset(index_by_id, 0, sizeof(index_by_id));
    count = 0;
    free_count = 0;
    return 1;
}

// Add book copy
static int add_copy(int id, int title) {
    if (count == N || map_get(id) >= 0)
        return 0;

    copies[count] = (Copy){id, title, AVAILABLE};

    if (!map_put(id, count))
        return 0;

    count++;
    free_count++;

    return 1;
}

// Issue book
static int issue_copy(int id) {
    int i = map_get(id);

    if (i < 0 || copies[i].status != AVAILABLE)
        return 0;

    copies[i].status = ISSUED;
    free_count--;

    return 1;
}

// Return book
static int return_copy(int id) {
    int i = map_get(id);

    if (i < 0 || copies[i].status != ISSUED)
        return 0;

    copies[i].status = AVAILABLE;
    free_count++;

    return 1;
}

// Lookup book
static int lookup_copy(int id) {
    int i = map_get(id);

    if (i < 0)
        return 0;

    printf("Copy %d: title %d, status %s\n",
           id, copies[i].title_id,
           copies[i].status == AVAILABLE ?
           "AVAILABLE" : "ISSUED");

    return 1;
}

// Display library status
static void print_state(void) {
    printf("Copies=%d Free=%d\n", count, free_count);

    for (int i = 0; i < count; i++) {
        printf("%d:%s ",
               copies[i].copy_id,
               copies[i].status == AVAILABLE ? "A" : "I");
    }

    printf("\n");
}

// Main function
int main(void) {
    init_library();

    printf("SMART LIBRARY MANAGEMENT SYSTEM\n\n");

    printf("Adding book copies...\n");

    add_copy(101, 10);
    add_copy(102, 10);
    add_copy(201, 20);

    puts("\nInitial Library Status:");
    print_state();

    printf("\nIssuing books 101 and 102...\n");

    issue_copy(101);
    issue_copy(102);

    puts("\nAfter Issuing:");
    print_state();

    printf("\nSearching for Copy ID 101:\n");
    if (!lookup_copy(101))
        printf("Book not found.\n");

    printf("\nTrying to issue book 101 again:\n");
    printf("Issue already-issued 101: %s\n",
           issue_copy(101) ? "OK" : "REJECTED");

    printf("\nReturning book 101:\n");
    printf("Return 101: %s\n",
           return_copy(101) ? "OK" : "REJECTED");

    printf("\nReturning unknown book 999:\n");
    printf("Return 999: %s\n",
           return_copy(999) ? "OK" : "REJECTED");

    puts("\nFinal Library Status:");
    print_state();

    return 0;
}
