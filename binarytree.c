#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct StackNode {
    struct Node *treeNode;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
};

void initStack(struct Stack *s){
    s->top = NULL;
}

int isStackEmpty(struct Stack *s) {
    return s->top == NULL;
}

void push(struct Stack *s, struct Node *node) {
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->treeNode = node;
    newNode->next = s->top;
    s->top = newNode;
}


struct Node* pop(struct Stack *s){
    if (isStackEmpty(s)) return NULL;
    struct StackNode *temp = s->top;
    struct Node *res = temp->treeNode;
    s->top = s->top->next;
    free(temp);
    return res;
}

struct QNode {
    struct Node *treeNode;
    struct QNode *next;
};

struct Queue {
    struct QNode *front, *rear;
};

void initQueue(struct Queue *q){
    q->front = q->rear = NULL;
}

int isQueueEmpty(struct Queue *q) {
    return q->front == NULL;
}

void enqueue(struct Queue *q, struct Node *node) {
    struct QNode *newNode = (struct QNode *)malloc(sizeof(struct QNode));
    newNode->treeNode = node;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

struct Node* dequeue(struct Queue *q) {
    if (isQueueEmpty(q)) return NULL;

    struct QNode *temp = q->front;
    struct Node *res = temp->treeNode;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return res;
}

struct Node* createNode(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node *root, int val) {
    struct Node *newNode = createNode(val);
    if (root == NULL) {
        printf("%d added successfully\n", val);
        return newNode;
    }

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        struct Node *temp = dequeue(&q);

        if (temp->left == NULL) {
            temp->left = newNode;
            printf("%d added successfully.\n", val);
            break;
        } else {
            enqueue(&q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            printf("%d added successfully.\n", val);
            break;
        } else {
            enqueue(&q, temp->right);
        }
    }
    return root;
}

int search(struct Node *root, int val) {
    if (root == NULL) return 0;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        struct Node *temp = dequeue(&q);
        if (temp->data == val)
            return 1;
        if (temp->left)
            enqueue(&q, temp->left);
        if (temp->right)
            enqueue(&q, temp->right);
    }
    return 0;
}

struct Node* deleteNode(struct Node *root, int val) {
    if (root == NULL) {
        printf("The tree is empty.\n");
        return NULL;
    }

    if (root->left == NULL && root->right == NULL) {
        if (root->data == val) {
            free(root);
            return NULL;
        }
        return root;
    }

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    struct Node *temp, *keyNode = NULL, *last = NULL, *parent = NULL;

    while (!isQueueEmpty(&q)) {
        last = dequeue(&q);
        if (last->data == val)
            keyNode = last;
        if (last->left){
            parent = last;
            enqueue(&q, last->left);
        }
        if (last->right) {
            parent = last;
            enqueue(&q, last->right);
        }
    }

    if (keyNode != NULL) {
        keyNode->data = last->data;
        if (parent->right == last) {
            free(parent->right);
            parent->right = NULL;
        } else if (parent->left == last) {
            free(parent->left);
            parent->left = NULL;
        }
        printf("%d deleted successfully.\n", val);
    }

    return root;
}

void inorder(struct Node *root) {
    if (root == NULL) return;

    struct Stack s;
    initStack(&s);
    struct Node *curr = root;

    while (curr != NULL || !isStackEmpty(&s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

void preorder(struct Node *root) {
    if (root == NULL) return;

    struct Stack s;
    initStack(&s);
    push(&s, root);

    while (!isStackEmpty(&s)) {
        struct Node *curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right)
            push(&s, curr->right);
        if (curr->left)
            push(&s, curr->left);
    }
    printf("\n");
}

void postorder(struct Node *root) {
    if (root == NULL) return;

    struct Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    push(&s1, root);
    while (!isStackEmpty(&s1)) {
        struct Node *curr = pop(&s1);
        push(&s2, curr);
        if (curr->left)
            push(&s1, curr->left);
        if (curr->right)
            push(&s1, curr->right);
    }

    while (!isStackEmpty(&s2)) {
        struct Node *temp = pop(&s2);
        printf("%d ", temp->data);
    }
    printf("\n");
}

void levelOrder(struct Node *root) {
    if (root == NULL) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        struct Node *curr = dequeue(&q);
        printf("%d ", curr->data);
        if (curr->left)
            enqueue(&q, curr->left);
        if (curr->right)
            enqueue(&q, curr->right);
    }
    printf("\n");
}

int get_integer_input() {
    int value;
    char term; 
    while (1) {
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            printf("invalid input please enter a whole number: ");
            while (getchar() != '\n'); 
        } else {
            return value; 
        } 
    }
}

int main() {
    struct Node *root = NULL;
    int choice, val;

    do {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Level Order Traversal\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        choice = get_integer_input();  

        switch (choice) {
        case 1:
            printf("Enter value: ");
            val = get_integer_input();  
            root = insert(root, val);
            break;

        case 2:
            printf("Enter value to search: ");
            val = get_integer_input();  
            printf(search(root, val) ? "Found\n" : "Not Found\n");
            break;

        case 3:
            printf("Enter value to delete: ");
            val = get_integer_input(); 
            root = deleteNode(root, val);
            break;

        case 4:
            printf("Inorder: ");
            inorder(root);
            break;

        case 5:
            printf("Preorder: ");
            preorder(root);
            break;

        case 6:
            printf("Postorder: ");
            postorder(root);
            break;

        case 7:
            printf("Level Order: ");
            levelOrder(root);
            break;

        case 8:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 8);

    return 0;
}