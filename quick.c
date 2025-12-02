#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int n = 0; // number of elements

// ------------------- Quick Sort -------------------
int partition(int arr[],int start,int end)
{
    int pos = start;
    for ( int i=start; i <= end; i++)
    {
        if (arr[i] <= arr[end])
        {
            int temp = arr[i];
            arr[i] = arr[pos];
            arr[pos] = temp;
            pos++;
        }
    }
    return pos-1;
}
void quicksort(int arr[],int start,int end)
{
    if(start>=end)
        return;


    int pivot = partition(arr, start, end);
    //left side
    quicksort(arr, start, pivot - 1);
    //right side
    quicksort(arr, pivot + 1, end);
}
// ------------------- CRUD Operations -------------------

// C = Create / Insert
void insertElement() {
    if (n >= MAX) {
        printf("Array full! Cannot insert.\n");
        return;
    }
    int val;
    printf("Enter number to insert: ");
    scanf("%d", &val);
    arr[n++] = val;
    printf("Inserted successfully.\n");
}

// R = Read / Display
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

// U = Update value
void updateElement() {
    int pos, newVal;
    display();

    printf("Enter index to update (0 to %d): ", n - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid position!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &newVal);

    arr[pos] = newVal;
    printf("Updated successfully.\n");
}

// D = Delete value
void deleteElement() {
    int pos;
    display();

    printf("Enter index to delete (0 to %d): ", n - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= n) {
        printf("Invalid position!\n");
        return;
    }

    for (int i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];

    n--;
    printf("Deleted successfully.\n");
}

// ------------------ MAIN MENU ------------------
int main() {
    int choice;

    while (1) {
        printf("\n===== QUICK SORT CRUD SYSTEM =====\n");
        printf("1. Insert Element\n");
        printf("2. Display Elements\n");
        printf("3. Update Element\n");
        printf("4. Delete Element\n");
        printf("5. Sort Using Quick Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: insertElement(); break;
        case 2: display(); break;
        case 3: updateElement(); break;
        case 4: deleteElement(); break;
        case 5:
            if (n == 0) printf("Array empty! Nothing to sort.\n");
            else {
                quicksort(arr, 0, n - 1);
                printf("Array sorted successfully.\n");
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
