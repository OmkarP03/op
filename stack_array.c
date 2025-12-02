#include<stdio.h>
#include<stdlib.h>
struct stack
{
    int size;
    int top;
    int *arr;
};

int isfUll(struct stack *s){
    if(s->top==s->size-1){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(struct stack *s){
    if(s->top==-1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(struct stack *s,int val){
    if(isfUll(s)){
        printf("Stack Overflow! Cannot push %d to the stack\n",val);
    }
    else{
        s->top++;
        s->arr[s->top]=val;
        printf("Pushed %d to the stack\n",val);
    }
}

int pop(struct stack *s){
    if(isEmpty(s)){
        printf("Stack Underflow! Cannot pop from the stack\n");
        return -1;  
    }
    else{
        int val = s->arr[s->top];
        s->top--;
        printf("Popped %d from the stack\n", val);
        return val;  
    }
}

int peek(struct stack *s, int pos){
    int arrayInd = s->top - pos + 1;
    if(arrayInd < 0){
        printf("Not a valid position for the stack\n");
        return -1;
    }
    else{
        return s->arr[arrayInd];
    }
}

void display(struct stack *s){
    if(isEmpty(s)){
        printf("Stack is empty\n");
    } else {
        printf("Stack elements : ");
        for(int i = s->top; i >= 0; i--){
            printf("%d ", s->arr[i]);
        }
        printf("\n");
    }
}


int main(){
    struct stack *s=(struct stack *)malloc(sizeof(struct stack));
    s->size=10;
    s->top=-1;
    s->arr=(int *)malloc(s->size*sizeof(int));
    printf("Stack has been created successfully\n");

    push(s,10);
    push(s,20);
    push(s,30);
    push(s,40);
    push(s,50);
    push(s,60);
    push(s,70);    
    push(s,80); 
    push(s,90);
    push(s,100);
    
      
    pop(s);
    pop(s);

    display(s);

    int val = peek(s, 3); 
    if(val != -1){
        printf("Element at position 3 from top is %d\n", val);
    }

return 0;
}