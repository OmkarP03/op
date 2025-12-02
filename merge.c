#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int n = 0;  // number of elements

// ---------------- PRINT ARRAY ----------------
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// ---------------- MERGE FUNCTION ----------------
void merge(int A[], int low, int mid, int high) {
    int B[100];
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high) {
        if (A[i] < A[j])
            B[k++] = A[i++];
        else
            B[k++] = A[j++];
    }

    while (i <= mid)
        B[k++] = A[i++];

    while (j <= high)
        B[k++] = A[j++];

    for (int p = low; p <= high; p++)
        A[p] = B[p];
}

// ---------------- MERGE SORT RECURSIVE ----------------
void mergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);

        merge(A, low, mid, high);
    }
}

// ---------------- CRUD FUNCTIONS ----------------

// INSERT
void insertElement() {
    if (n >= MAX) {
        printf("Array full! Cannot insert.\n");
        return;
    }
    int val;
    printf("Enter element to insert: ");
    scanf("%d", &val);

    arr[n++] = val;
    printf("Inserted successfully.\n");
}

// DISPLAY
void display() {
    if (n == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    printArray(arr, n);
}

// UPDATE
void updateElement() {
    int pos, newVal;

    display();
    printf("Enter index to update (0 to %d): ", n - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &newVal);

    arr[pos] = newVal;
    printf("Updated successfully.\n");
}

// DELETE
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
    printf("Deleted successfully.\n");
}

// ---------------- MAIN MENU ----------------
int main() {
    int choice;

    while (1) {
        printf("\n===== MERGE SORT CRUD SYSTEM =====\n");
        printf("1. Insert Element\n");
        printf("2. Display Elements\n");
        printf("3. Update Element\n");
        printf("4. Delete Element\n");
        printf("5. Sort Using Merge Sort\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertElement(); break;
            case 2: display(); break;
            case 3: updateElement(); break;
            case 4: deleteElement(); break;
            case 5:
                if (n == 0) printf("Array empty! Nothing to sort.\n");
                else {
                    mergeSort(arr, 0, n - 1);
                    printf("Array sorted successfully!\n");
                    display();
                }
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
