#include <stdio.h>
#include <stdlib.h>

#define MAX 10


int adj[MAX][MAX];   
int visited[MAX];    
int vertexCount = 0; 


struct Stack{
    int items[MAX];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isStackEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, int value){
    if (s->top == MAX - 1){
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

int pop(struct Stack* s){
    if (isStackEmpty(s)) return -1;
    return s->items[(s->top)--];
}


void addVertex() {
    if (vertexCount == MAX) {
        printf("Maximum vertices reached!\n");
        return;
    }

    vertexCount++;
    printf("Vertex %d added.\n", vertexCount - 1);
}

void addEdge(int src, int dest) {
    if (src >= vertexCount || dest >= vertexCount){
        printf("Invalid vertex number\n");
        return;
    }

    adj[src][dest] = 1;
    adj[dest][src] = 1;

    printf("Edge %d -- %d added\n", src, dest);
}

void displayGraph() {
    printf("\nAdjacency Matrix:\n  ");

    for (int i = 0; i < vertexCount; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < vertexCount; i++) {
        printf("%d ", i);
        for (int j = 0; j < vertexCount; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

void resetVisited() {
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;
}

void DFS(int start){
    if (start >= vertexCount) {
        printf("Invalid starting vertex!\n");
        return;
    }

    struct Stack s;
    initStack(&s);
    
    resetVisited();

    printf("DFS: ");
    push(&s, start);

    while (!isStackEmpty(&s)) {
        int v = pop(&s);

        if (!visited[v]) {
            visited[v] = 1;
            printf("%d ", v);

            for (int i = 0; i < vertexCount; i++) {
                if (adj[v][i] == 1 && !visited[i]) {
                    push(&s, i);
                }
            }
        }
    }

    printf("\n");
}


struct Queue {
    int items[MAX];
    int front, rear;
};

void initQueue(struct Queue* q) { 
    q->front = q->rear = 0; 
}

int isQueueEmpty(struct Queue* q) {
    return q->front == q->rear;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX) {
        printf("Queue Overflow!\n");
        return;
    }
    q->items[q->rear++] = value;
}

int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) return -1;
    return q->items[q->front++];
}


void BFS(int start) {
    if (start >= vertexCount) {
        printf("Invalid starting vertex\n");
        return;
    }

    struct Queue q;
    initQueue(&q);

    resetVisited();

    printf("BFS: ");
    enqueue(&q, start);
    visited[start] = 1;

    while (!isQueueEmpty(&q)) {
        int v = dequeue(&q);
        printf("%d ", v);

        for (int i = 0; i < vertexCount; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}


int get_integer_input() {
    int value;
    char term;
    while (1) {
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            printf("Invalid input! Please enter a whole number: ");
            while (getchar() != '\n'); 
        } else {
            return value;
        }
    }
}



int main() {
    int choice, src, dest, start;

    while (1) {
        printf("\n===== GRAPH MENU =====\n");
        printf("1. Add Vertex\n");
        printf("2. Add Edge\n");
        printf("3. Display Graph (Matrix)\n");
        printf("4. DFS (Iterative)\n");
        printf("5. BFS\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        choice = get_integer_input();  

        switch (choice) {
            case 1:
                addVertex();
                break;

            case 2:
                printf("Enter source vertex: ");
                src = get_integer_input();

                printf("Enter destination vertex: ");
                dest = get_integer_input();

                addEdge(src, dest);
                break;

            case 3:
                displayGraph();
                break;

            case 4:
                printf("Enter starting vertex for DFS: ");
                start = get_integer_input();
                DFS(start);
                break;

            case 5:
                printf("Enter starting vertex for BFS: ");
                start = get_integer_input();
                BFS(start);
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