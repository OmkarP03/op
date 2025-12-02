#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int size;
    int f;   
    int r;   
    int *arr;
};

int isEmpty(struct Queue* q) {
    if (q->f == q->r) {
        return 1;
    }
    else {
        return 0;
    }
}

int isFull(struct Queue* q) {
    if (q->r == q->size - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void enqueue(struct Queue* q, int val) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", val);
    } else {
        q->r++;
        q->arr[q->r] = val;
        printf("Enqueued %d\n", val);
    }
}

int dequeue(struct Queue* q) {
    int a = -1;
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue\n");
    } else {
        q->f++;
        a = q->arr[q->f];
        printf("Dequeued %d\n", a);
    }
    return a;
}

int peek(struct Queue* q, int pos) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    if (pos <= 0 || pos > (q->r - q->f)) {
        printf("Invalid position!\n");
        return -1;
    }
    return q->arr[q->f + pos];
}

void display(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        for (int i = q->f + 1; i <= q->r; i++) {
            printf("%d ", q->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    struct Queue q;
    q.size = 10;
    q.f = q.r = -1;
    q.arr = (int*)malloc(q.size * sizeof(int));

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);
    dequeue(&q);
    display(&q);

    printf("Element at position 2: %d\n", peek(&q, 2));

    return 0;
}
