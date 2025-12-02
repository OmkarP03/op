#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
    int rthread; 
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->rthread = 0;  
    return node;
}

struct Node* insert(struct Node* root, int key){
    struct Node* ptr = root;
    struct Node* parent = NULL;

    while (ptr != NULL){
        if (key == ptr->data){
            printf("duplicate key %d not allowed\n", key);
            return root;
        }

        parent = ptr;

        if (key < ptr->data){
            ptr = ptr->left;
        } 
        else{
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    struct Node* temp = createNode(key);

    if (parent == NULL){
        root = temp;
    }
  
    else if (key < parent->data) {
        parent->left = temp;
        temp->right = parent;
        temp->rthread = 1;
    }

    else {
        temp->rthread = parent->rthread;
        temp->right = parent->right;
        parent->rthread = 0;
        parent->right = temp;
    }

    printf("Node %d inserted successfully.\n", key);
    return root;
}

struct Node* leftMost(struct Node* n){
    if (n == NULL)
        return NULL;

    while (n->left != NULL)
        n = n->left;

    return n;
}

void inorder(struct Node* root) {
    if (root == NULL){
        printf("Tree is empty\n");
        return;
    }

    struct Node* cur = leftMost(root);
    while (cur != NULL){
        printf("%d ", cur->data);
        if (cur->rthread)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
    }
    printf("\n");
}

struct Node* search(struct Node* root, int key) {
    struct Node* ptr = root;

    while (ptr != NULL) {
        if (key == ptr->data)
            return ptr;
        else if (key < ptr->data)
            ptr = ptr->left;
        else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }
    return NULL;
}


struct Node* deleteNode(struct Node* root, int key) {
    struct Node *parent = NULL, *curr = root;
    int found = 0;

    while (curr != NULL) {
        if (key == curr->data) {
            found = 1;
            break;
        }
        parent = curr;
        if (key < curr->data)
            curr = curr->left;
        else {
            if (curr->rthread == 0)
                curr = curr->right;
            else
                break;
        }
    }

    if (!found) {
        printf("Key %d not found in the tree\n", key);
        return root;
    }

  
    if (curr->left != NULL && curr->rthread == 0) {
        struct Node* succParent = curr;
        struct Node* succ = curr->right;
        while (succ->left != NULL){
            succParent = succ;
            succ = succ->left;
        }
        curr->data = succ->data;         
        curr = succ;                       
        parent = succParent;
    }

    struct Node* child = NULL;
    if (curr->left != NULL)
        child = curr->left;
    else if (curr->rthread == 0)
        child = curr->right;

    if (parent == NULL){
        root = child;
    }
    else if (curr == parent->left) {
        parent->left = child;
    }
    else{
        if (curr->rthread == 1 && child == NULL) {
            parent->rthread = 1;
            parent->right = curr->right; 
        } else{
            parent->right = child;
        }
    }

    free(curr);
    printf("Node %d deleted successfully\n", key);
    return root;
}


struct Node* update(struct Node* root, int oldVal, int newVal) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return root;
    }

    if (search(root, newVal) != NULL) {
        printf("value %d already exists cannot update\n", newVal);
        return root;
    }

    root = deleteNode(root, oldVal);
    root = insert(root, newVal);

    printf("Node value updated from %d to %d successfully.\n", oldVal, newVal);
    return root;
}

int get_integer_input() {
    int value;
    char term;
    while (1){
        if (scanf("%d%c", &value, &term) != 2 || term != '\n'){
            printf("Invalid input Please enter valid whole number: ");
            while (getchar() != '\n');
        } else{
            return value;
        }
    }
}

int main() {
    struct Node* root = NULL;
    int choice, val, oldVal, newVal;

    while (1) {
        printf("\n--- Right Threaded Binary Tree (CRUD) ---\n");
        printf("1. Insert\n2. Display (Inorder)\n3. Search\n4. Update\n5. Delete\n6. Exit\n");
        printf("Enter your choice: ");
        choice = get_integer_input();

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                val = get_integer_input();
                root = insert(root, val);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorder(root);
                break;
            case 3:
                printf("Enter value to search: ");
                val = get_integer_input();
                if (search(root, val))
                    printf("Node %d found.\n", val);
                else
                    printf("Node %d not found.\n", val);
                break;
            case 4:
                printf("Enter old value: ");
                oldVal = get_integer_input();
                printf("Enter new value: ");
                newVal = get_integer_input();
                root = update(root, oldVal, newVal);
                break;
            case 5:
                printf("Enter value to delete: ");
                val = get_integer_input();
                root = deleteNode(root, val);
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}