
#include <stdio.h>
#include <stdlib.h>

// AVL Node structure
typedef struct AVL {
    int key, height;
    struct AVL *left, *right;
} AVL;

// Find maximum
int max(int a, int b) {
    return a > b ? a : b;
}

// Calculate height
int ht(AVL *n) {
    return n ? n->height : 0;
}

// Update height
void update(AVL *n) {
    n->height = 1 + max(ht(n->left), ht(n->right));
}

// Calculate balance factor
int bf(AVL *n) {
    return n ? ht(n->left) - ht(n->right) : 0;
}

// Create new node
AVL *createNode(int key) {
    AVL *n = malloc(sizeof(AVL));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n->key = key;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// Right rotation (LL)
AVL *rightRotate(AVL *z) {
    AVL *y = z->left;
    AVL *t = y->right;

    y->right = z;
    z->left = t;

    update(z);
    update(y);

    return y;
}

// Left rotation (RR)
AVL *leftRotate(AVL *z) {
    AVL *y = z->right;
    AVL *t = y->left;

    y->left = z;
    z->right = t;

    update(z);
    update(y);

    return y;
}

// Insert node and balance AVL tree
AVL *insert(AVL *root, int key) {
    // Normal BST insertion
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);

    else if (key > root->key)
        root->right = insert(root->right, key);

    else
        return root;  // Duplicate keys not allowed

    // Update height
    update(root);

    // Calculate balance factor
    int balance = bf(root);

    // LL Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(AVL *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(AVL *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Free memory
void freeTree(AVL *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main(void) {
    AVL *root = NULL;

    int values[] = {30, 20, 10, 40, 50, 25};
    int n = sizeof(values) / sizeof(values[0]);

    printf("AVL TREE IMPLEMENTATION\n");

    // Insert elements
    printf("\nInserting elements:\n");

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("Inserted: %d\n", values[i]);
    }

    // Display traversals
    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    // Display height and balance factor
    printf("\n\nRoot: %d", root->key);
    printf("\nHeight: %d", ht(root));
    printf("\nBalance Factor: %d", bf(root));

    printf("\n\nAVL tree maintained successfully.\n");

    // Release memory
    freeTree(root);

    printf("Memory released successfully.\n");

    return 0;
}
