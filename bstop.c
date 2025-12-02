#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct stackNode{
    struct Node* treeNode;
    struct stackNode* next;
};
struct stack{
    struct stackNode* top;
};
void initStack(struct stack *s){
    s->top = NULL;
}
int isStackEmpty(struct stack* s){
    return s->top == NULL;
}
void push(struct stack* s, struct Node* node){
    struct stackNode* newNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    newNode->treeNode = node;
    newNode->next = s->top;
    s->top = newNode;
}
struct Node* pop(struct stack *s){
    if(isStackEmpty(s)) return NULL;
    struct stackNode *temp = s->top;
    struct Node *res = temp->treeNode;
    s->top = s->top->next;
    free(temp);
    return res;
}


struct Node* createNode(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int val){
    struct Node* newNode = createNode(val);

    if (root == NULL)
        return newNode;

    struct Node* prev = NULL;
    struct Node* current = root;

    while(current != NULL){
        prev = current;
        if(val == current->data){
            printf("Value already exists\n");
            free(newNode);
            return root;
        }
        else if(val < current->data){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    if(val < prev->data){
        prev->left = newNode;
    }
    else{
        prev->right = newNode;
    }
    return root;
}

struct Node* search(struct Node *root, int val) {
    while (root != NULL) {
        if (val == root->data)
            return root;
        else if (val < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

struct Node* deleteNode(struct Node *root, int val){
    if (root == NULL)
        return root;

    struct Node *parent = NULL;
    struct Node *current = root;

   
    while (current != NULL && current->data != val) {
        parent = current; 
        if (val < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        printf("Value %d not found.\n", val);
        return root;
    }

    if (current->left == NULL || current->right == NULL) {
       
        struct Node* child;
        if (current->left != NULL){
            child = current->left;
        }
        else{
            child = current->right;
        }
        if (parent == NULL) {
            free(current);
            return child;
        }
        if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;

        free(current);
    }
    else {
        struct Node *succParent = current;
        struct Node *succ = current->right;
        
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        current->data = succ->data;

        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        free(succ);
    }

    return root;
}

struct Node *update(struct Node *root, int oldVal, int newVal) {
    struct Node *target = search(root, oldVal);
    if (target == NULL) {
        printf("Value %d not found, cannot update.\n", oldVal);
        return root;
    }
    root = deleteNode(root, oldVal);
    root = insert(root, newVal);
    printf("Value %d updated to %d successfully.\n", oldVal, newVal);
    return root;
}
void inorder(struct Node *root) {
    if (root == NULL) return;

    struct stack s;
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


int get_integer_input() {
    int value;
    char term;
    while (1) {
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            printf("Invalid input Please enter a whole number: ");
            while (getchar() != '\n');
        } else {
            return value;
        }
    }
}

int main() {
    struct Node *root = NULL;
    int choice, val, oldVal, newVal;

    while (1) {
        printf("\n\n---- Binary Search Tree CRUD ----\n");
        printf("1. Insert\n2. Search\n3. Update\n4. Delete\n5. Display (Inorder)\n6. Exit\n");
        printf("Enter your choice: ");
        choice = get_integer_input();

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            val = get_integer_input();
            root = insert(root, val);
            break;

        case 2:
            printf("Enter value to search: ");
            val = get_integer_input();
            if (search(root, val))
                printf("Value found\n");
            else
                printf("Value not found\n");
            break;

        case 3:
            printf("Enter value to update: ");
            oldVal = get_integer_input();
            printf("Enter new value: ");
            newVal = get_integer_input();
            root = update(root, oldVal, newVal);
            break;

        case 4:
            printf("Enter value to delete: ");
            val = get_integer_input();
            root = deleteNode(root, val);
            printf("Value deleted (if it existed)\n");
            break;

        case 5:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 6:
            printf("Exiting program\n");
            exit(0);

        default:
            printf("Invalid Number.\n");
        }
    }
    return 0;
}