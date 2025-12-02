#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *f, *r;
};

int linkedlisttraversal(struct Node *ptr)
{
    while (ptr != NULL)
    {
        printf("Element: %d\n", ptr->data);
        ptr = ptr->next;
    }
}

int isEmpty(struct Queue *q)
{
    if (q->f == NULL)
    {
        return 1;
    }
    return 0;
}

void enqueue(struct Queue *q, int val)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("Queue Overflow! Cannot enqueue %d to the queue\n", val);
    }
    else
    {
        n->data = val;
        n->next = NULL;
        if (q->r == NULL)
        {
            q->f = q->r = n;
        }
        else
        {
            q->r->next = n;
            q->r = n;
        }
        printf("Enqueued %d to the queue\n", val);
    }
}
int dequeue(struct Queue *q)
{
    int a = -1;
    struct Node *temp;
    if (isEmpty(q))
    {
        printf("Queue Underflow! Cannot dequeue from the queue\n");
        return a;
    }
    else
    {
        temp = q->f;
        a = q->f->data;
        q->f = q->f->next;
        free(temp);
        printf("Dequeued %d from the queue\n", a);
        return a;
    }
}

int peek(struct Queue *q, int pos)
{
    if (isEmpty(q))
    {
        printf("Queue is empty!\n");
        return -1;
    }
    if (pos <= 0)
    {
        printf("Invalid position!\n");
        return -1;
    }
    struct Node *ptr = q->f;
    int i = 1;
    while (ptr != NULL && i < pos)
    {
        ptr = ptr->next;
        i++;
    }
    if (ptr != NULL)
    {
        return ptr->data;
    }
    else
    {
        printf("Position out of bounds!\n");
        return -1;
    }
}

int main()
{
    struct Queue q;
    q.f = q.r = NULL;
    int choice, val;

    while (1)
    {
        printf("\n--- Queue Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice (1 to 5): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number in 1 to 5.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &val);
            enqueue(&q, val);
            break;

        case 2:
            val = dequeue(&q);
            if (val != -1)
            {
                printf("Dequeued element is %d\n", val);
            }
            break;

        case 3:
        {
            int pos;
            printf("Enter position to peek: ");
            scanf("%d", &pos);
            val = peek(&q, pos);
            if (val != -1)
            {
                printf("Element at position %d is %d\n", pos, val);
            }
        }
        break;

        case 4:
            printf("Queue elements are:\n");
            linkedlisttraversal(q.f);
            break;

        case 5:
            printf("Exit program\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}