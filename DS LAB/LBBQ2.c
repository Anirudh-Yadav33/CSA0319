#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

void display()
{
    struct node *temp = head;

    while(temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertBegin(int x)
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = x;
    newnode->next = head;
    head = newnode;
}

void insertEnd(int x)
{
    struct node *newnode, *temp;
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = x;
    newnode->next = NULL;

    if(head == NULL)
        head = newnode;
    else
    {
        temp = head;
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
    }
}

void insertPos(int x, int pos)
{
    struct node *newnode, *temp;
    int i;

    if(pos < 1)
    {
        printf("Invalid position\n");
        return;
    }

    if(pos == 1)
    {
        insertBegin(x);
        return;
    }

    temp = head;

    for(i = 1; i < pos-1 && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = temp->next;
    temp->next = newnode;
}

int main()
{
    int ch, x, pos;

    do
    {
        printf("\n1.Beginning 2.End 3.Position 4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if(ch == 1)
        {
            printf("Enter roll number: ");
            scanf("%d", &x);
            insertBegin(x);
            display();
        }
        else if(ch == 2)
        {
            printf("Enter roll number: ");
            scanf("%d", &x);
            insertEnd(x);
            display();
        }
        else if(ch == 3)
        {
            printf("Enter roll number and position: ");
            scanf("%d %d", &x, &pos);
            insertPos(x, pos);
            display();
        }
        else if(ch == 4)
            printf("Exit\n");
        else
            printf("Invalid choice\n");

    } while(ch != 4);

    return 0;
}