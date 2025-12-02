#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

struct StackNode {
    struct Node *node;
    struct StackNode *next;
};

struct StackNode *Top = NULL;  

void push(struct Node *node) {
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = Top;
    Top = newNode;
}

struct Node *pop(){
    if (Top == NULL)
        return NULL;

    struct StackNode *temp = Top;
    struct Node *res = temp->node;

    Top = Top->next;
    free(temp);

    return res;
}

int isEmpty() {
    return Top == NULL;
}

int height(struct Node *n){
    if (n != NULL)
        return n->height;
    else
        return 0;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

struct Node *createNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}


struct Node *insert(struct Node *root, int key) {
    Top = NULL;

    if (root == NULL)
        return createNode(key);

    struct Node *parent = NULL, *current = root;

    
    while (current != NULL){
        if (key == current->data){
            printf("duplicate key %d not allowed\n", key);
            while(!isEmpty()) pop(); 
            return root;
        }
        push(current);
        parent = current;

        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else
            return root;
    }

    struct Node *newNode = createNode(key);

    if (key < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;


    while (!isEmpty()) {
        struct Node *node = pop();
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data){ 
            if (!isEmpty()){
                struct Node *parentNode = Top->node;
                if (node->data < parentNode->data)
                    parentNode->left = rightRotate(node);
                else
                    parentNode->right = rightRotate(node);
            } 
            else
                root = rightRotate(node);
        }
        else if (balance < -1 && key > node->right->data) { 
            if (!isEmpty()){
                struct Node *parentNode = Top->node;
                if (node->data < parentNode->data)
                    parentNode->left = leftRotate(node);
                else
                    parentNode->right = leftRotate(node);
            } else
                root = leftRotate(node);
        }
        else if (balance > 1 && key > node->left->data) { 
            node->left = leftRotate(node->left);
            if (!isEmpty()) {
                struct Node *parentNode = Top->node;
                if (node->data < parentNode->data)
                    parentNode->left = rightRotate(node);
                else
                    parentNode->right = rightRotate(node);
            } 
            else
                root = rightRotate(node);
        }
        else if (balance < -1 && key < node->right->data) { 
            node->right = rightRotate(node->right);
            if (!isEmpty()){
                struct Node *parentNode = Top->node;
                if (node->data < parentNode->data)
                    parentNode->left = leftRotate(node);
                else
                    parentNode->right = leftRotate(node);
            } 
            else
                root = leftRotate(node);
        }
    }
    printf("Node %d inserted successfully.\n", key);
    return root;
}

struct Node *search(struct Node *root, int key) {
    struct Node *current = root;
    while (current != NULL){
        if (key == current->data)
            return current;
        else if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}


struct Node *deleteNode(struct Node *root, int key) {
    Top = NULL;
    struct Node *parent = NULL, *current = root;
    
    while(current != NULL && current->data != key){
        push(current);
        parent = current;
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return root; 
    
    if (current->left == NULL || current->right == NULL) {
        struct Node *temp;

        if (current->left != NULL) {
            temp = current->left;
        } 
        else{
            temp = current->right;
        }


        if (parent == NULL)
            root = temp;
        else if (key < parent->data)
            parent->left = temp;
        else
            parent->right = temp;

        free(current);
    }
    else {

        push(current);
        struct Node *succ = current->right;
        struct Node *succParent = current;

        while (succ->left != NULL) {
            push(succ);
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

    while (!isEmpty()) {
        struct Node *node = pop();
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            node = rightRotate(node);
        else if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
        else if (balance < -1 && getBalance(node->right) <= 0)
            node = leftRotate(node);
        else if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }

        if (!isEmpty()) {
            struct Node *parentNode = Top->node;
            if (node->data < parentNode->data)
                parentNode->left = node;
            else
                parentNode->right = node;
        }
        else
            root = node;
    }

    return root;
}

struct Node *update(struct Node *root, int oldKey, int newKey) {
    root = deleteNode(root, oldKey);
    root = insert(root, newKey);
    return root;
}

void inorder(struct Node *root) {
    Top = NULL;

    struct Node *current = root;

    while (current != NULL || !isEmpty()) {
        while (current != NULL) {
            push(current);
            current = current->left;
        }

        current = pop();
        printf("%d ", current->data);

        current = current->right;
    }
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
    int choice, key, oldKey, newKey;

    while (1) {
        printf("\n--- AVL Tree (Iterative CRUD) ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Update\n5. Display (Inorder)\n6. Exit\n");
        printf("Enter your choice: ");
        choice = get_integer_input();

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            key = get_integer_input();
            root = insert(root, key);
            break;

        case 2:
            printf("Enter key to delete: ");
            key = get_integer_input();
            root = deleteNode(root, key);
            printf("value deleted (if it existed)\n");
            break;

        case 3:
            printf("Enter key to search: ");
            key = get_integer_input();
            if (search(root, key))
                printf("%d found\n", key);
            else
                printf("%d not found\n", key);
            break;

        case 4:
            printf("Enter old key: ");
            oldKey = get_integer_input();
            printf("Enter new key: ");
            newKey = get_integer_input();
            root = update(root, oldKey, newKey);
            printf("Updated %d to %d\n", oldKey, newKey);
            break;

        case 5:
            printf("Inorder: ");
            inorder(root);
            printf("\n");
            break;

        case 6:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}