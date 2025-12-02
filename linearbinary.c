#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int n = 0;   // current size

// -------------------- INSERT --------------------
void insertElement() {
    if (n >= MAX) {
        printf("Array full! Cannot insert.\n");
        return;
    }
    int val;
    printf("Enter value to insert: ");
    scanf("%d", &val);

    arr[n++] = val;
    printf("Inserted successfully.\n");
}

// -------------------- DISPLAY --------------------
void display() {
    if (n == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// -------------------- UPDATE --------------------
void updateElement() {
    int pos, val;
    display();

    printf("Enter index to update (0 to %d): ", n-1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &val);

    arr[pos] = val;
    printf("Updated successfully.\n");
}

// -------------------- DELETE --------------------
void deleteElement() {
    int pos;
    display();

    printf("Enter index to delete (0 to %d): ", n-1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid index!\n");
        return;
    }

    for (int i = pos; i < n-1; i++)
        arr[i] = arr[i+1];

    n--;
    printf("Deleted successfully.\n");
}

// -------------------- LINEAR SEARCH --------------------
int linearSearch(int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// -------------------- BINARY SEARCH --------------------  
// (Array must be sorted)
void sortArray() {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int binarySearch(int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// -------------------- MAIN MENU --------------------
int main() {
    int choice, key, pos;

    while (1) {
        printf("\n===== SEARCH CRUD SYSTEM =====\n");
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Linear Search\n");
        printf("6. Binary Search (Requires Sorted Array)\n");
        printf("7. Sort Array\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            insertElement();
            break;

        case 2:
            display();
            break;

        case 3:
            updateElement();
            break;

        case 4:
            deleteElement();
            break;

        case 5:
            printf("Enter value to search (Linear): ");
            scanf("%d", &key);
            pos = linearSearch(key);
            if (pos == -1)
                printf("Value NOT found.\n");
            else
                printf("Value found at index %d.\n", pos);
            break;

        case 6:
            printf("Enter value to search (Binary): ");
            scanf("%d", &key);
            pos = binarySearch(key);
            if (pos == -1)
                printf("Value NOT found.\n");
            else
                printf("Value found at index %d.\n", pos);
            break;

        case 7:
            sortArray();
            printf("Array sorted successfully.\n");
            display();
            break;

        case 8:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
