#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int n = 0;  // number of elements

// ------------------------ CRUD FUNCTIONS ------------------------

void insertElement() {
    if (n >= MAX) {
        printf("Array is full!\n");
        return;
    }
    int val;
    printf("Enter value to insert: ");
    scanf("%d", &val);

    arr[n++] = val;
    printf("Inserted successfully.\n");
}

void display() {
    if (n == 0) {
        printf("Array is empty!\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void updateElement() {
    int pos, val;
    display();
    printf("Enter index to update (0 to %d): ", n - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &val);

    arr[pos] = val;
    printf("Update successful.\n");
}

void deleteElement() {
    int pos;
    display();
    printf("Enter index to delete (0 to %d): ", n - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid index!\n");
        return;
    }

    for (int i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];

    n--;
    printf("Deletion successful.\n");
}

// ------------------------ BUBBLE SORT ------------------------
void bubbleSort() {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    printf("Array sorted using Bubble Sort.\n");
}

// ------------------------ SELECTION SORT ------------------------
void selectionSort() {
    for (int i = 0; i < n - 1; i++) {
        int SI = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[SI])
                SI = j;
        }

        int temp = arr[SI];
        arr[SI] = arr[i];
        arr[i] = temp;
    }
    printf("Array sorted using Selection Sort.\n");
}

// ------------------------ INSERTION SORT ------------------------
void insertionSort() {
    for (int i = 1; i < n; i++) {
        int curr = arr[i];
        int prev = i - 1;

        while (prev >= 0 && arr[prev] > curr) {
            arr[prev + 1] = arr[prev];
            prev--;
        }

        arr[prev + 1] = curr;
    }
    printf("Array sorted using Insertion Sort.\n");
}

// ------------------------ MAIN MENU ------------------------
int main() {
    int choice;

    while (1) {
        printf("\n====== SORTING CRUD SYSTEM ======\n");
        printf("1. Insert Element\n");
        printf("2. Display Elements\n");
        printf("3. Update Element\n");
        printf("4. Delete Element\n");
        printf("5. Bubble Sort\n");
        printf("6. Selection Sort\n");
        printf("7. Insertion Sort\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: insertElement(); break;
        case 2: display(); break;
        case 3: updateElement(); break;
        case 4: deleteElement(); break;
        case 5: bubbleSort(); display(); break;
        case 6: selectionSort(); display(); break;
        case 7: insertionSort(); display(); break;
        case 8: 
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
