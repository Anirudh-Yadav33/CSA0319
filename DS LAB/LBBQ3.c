#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

struct node* create(int x)
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = x;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

void preorder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    struct node *root;

    root = create(10);
    root->left = create(5);
    root->right = create(15);
    root->left->left = create(3);
    root->left->right = create(7);
    root->right->left = create(12);
    root->right->right = create(18);

    printf("Preorder traversal: ");
    preorder(root);

    return 0;
}