#include <stdio.h>
#include <stdlib.h>

struct HashMap {
    int table[10];
    int size;
};

// --------------------------------------------------
// Initialize Hash Table
// --------------------------------------------------
void initHash(struct HashMap* h) {
    h->size = 10;
    for (int i = 0; i < h->size; i++) {
        h->table[i] = -1;
    }
}

// --------------------------------------------------
// Insert
// --------------------------------------------------
void insert(struct HashMap* h, int val) {
    int index = val % h->size;
    int start = index;

    do {
        if (h->table[index] == val) {
            printf("Duplicate key found!\n");
            return;
        }
        if (h->table[index] == -1 || h->table[index] == -2) {
            h->table[index] = val;
            printf("Inserted %d\n", val);
            return;
        }
        index = (index + 1) % h->size;
    } while (index != start);

    printf("Hash table FULL!\n");
}

// --------------------------------------------------
// Search
// --------------------------------------------------
int search(struct HashMap* h, int val) {
    int index = val % h->size;
    int start = index;

    do {
        if (h->table[index] == val) {
            return 1;
        }
        index = (index + 1) % h->size;
    } while (index != start);

    return 0;
}

// --------------------------------------------------
// Delete
// --------------------------------------------------
void deleteKey(struct HashMap* h, int val) {
    int index = val % h->size;
    int start = index;

    do {
        if (h->table[index] == val) {
            h->table[index] = -2;
            printf("%d deleted.\n", val);
            return;
        }
        if (h->table[index] == -1) break;

        index = (index + 1) % h->size;
    } while (index != start);

    printf("%d not found.\n", val);
}

// --------------------------------------------------
// Display
// --------------------------------------------------
void display(struct HashMap* h) {
    int allEmpty = 1;

    for (int i = 0; i < h->size; i++) {
        if (h->table[i] == -1) {
            printf("Empty\n");
        } 
        else if (h->table[i] == -2) {
            printf("Deleted\n");
        } 
        else {
            printf("%d\n", h->table[i]);
            allEmpty = 0;
        }
    }

    if (allEmpty) {
        printf("Table is empty\n");
    }
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main() {
    struct HashMap h;
    initHash(&h);

    int val, choice;

    while (1) {
        printf("\n--- Hash Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display Hash Table\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter Number: ");
            if (scanf("%d", &val) != 1) {
                printf("Invalid Input. Please Enter Valid Number.\n");
                while (getchar() != '\n');
                continue;
            }
            insert(&h, val);
            break;

        case 2:
            printf("Enter number to Search: ");
            if (scanf("%d", &val) != 1) {
                printf("Invalid Input. Please Enter Valid Number.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("%d %s\n", val, search(&h, val) ? "Found" : "Not Found");
            break;

        case 3:
            printf("Enter number to Delete: ");
            if (scanf("%d", &val) != 1) {
                printf("Invalid Input. Please Enter Valid Number.\n");
                while (getchar() != '\n');
                continue;
            }
            deleteKey(&h, val);
            break;

        case 4:
            display(&h);
            break;

        case 5:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
