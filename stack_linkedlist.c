#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

void linkedListTraversal(struct Node *ptr) {
    while (ptr != NULL) {
        printf("Element: %d\n", ptr->data);
        ptr = ptr->next;
    }
}

int isEmpty(struct Node *top) {
    if( top == NULL)
        return 1;
    else
        return 0;
}

struct Node *push(struct Node *top, int x) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Stack Overflow FULL\n");
    }
    n->data = x;
    n->next = top;
    top = n;
    printf("Pushed %d onto the stack\n", x);
    return top;
}

int pop(struct Node *tp) {
    if (isEmpty(tp)) {
        printf("Stack Underflow\n");
        return -1;
    }
    struct Node *n = tp;
    top = tp->next;
    int x = n->data;
    free(n);
    return x;
}

int peek(struct Node *tp, int pos) {
    struct Node *ptr = tp;
    for (int i = 1; i < pos && ptr != NULL; i++) {
        ptr = ptr->next;
    }
    if (ptr != NULL) {
        return ptr->data;
    } else {
        printf("Invalid position!\n");
        return -1;
    }
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');  
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            top = push(top, value);
            break;

        case 2:
            value = pop(top);
            if (value != -1) {
                printf("Popped element is %d\n", value);
            }
            break;

        case 3: {
            int position;
            printf("Enter position to peek: ");
            scanf("%d", &position);
            value = peek(top, position);
            if (value != -1) {
                printf("Element at position %d is %d\n", position, value);
            }
            break;
        }

        case 4:
            printf("Stack elements are:\n");
            linkedListTraversal(top);
            break;

        case 5:
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
} 