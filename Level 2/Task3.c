// C program for Data Structure Implementation using array

#include <stdio.h>
#include <conio.h>
#include <windows.h>

// functions and global variable to implement queue
#define maxsize 5
void enqueue();
void dequeue();
void display_all_stack();
void display_front();
void display_rear();

// functions and global variable to implement queue
int front = 0, rear = -1, queue[maxsize];
int top = -1;
int max_size=5;
int stack[5];
void push();
void pop();
void display_all_queue();
void display_top();
void stack_();

// interface for operation related to stack
void stack_() {
    int ch;
    while(1) {
        system("cls");
        printf("\n\t\t Implementation of Stack using array");
        printf("\n\n\t 1. Push operation");
        printf("\n\t 2. Pop operation");
        printf("\n\t 3. Display all elements");
        printf("\n\t 4. Display top element");
        printf("\n\t 5. Exit");
        printf("\n\n Enter your choice: ");
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            display_all_stack();
            break;
        case 4:
            display_top();
            break;
        case 5:
            break;
        default:
        	printf("Wrong choice!!! Please make correct choice.");
        }
        if(ch==5)
        	break;
    }
}

void push() {
    int item;
    if(top == max_size)
        printf("\n\tThe stack is full");
    else{
        printf("\nEnter the element: ");
        scanf("%d", &item);
        top++;
        stack[top] = item;
        printf("\t A new data is being added in stack");
    }
    getch();
}

void pop() {
    int item;
    if(top == -1)
        printf("\n\t The stack cannot be popped any more because it's empty");
    else{
        printf("\n\t The popped element is %d", stack[top]);
        top--;
    }
    getch();
}

void display_all_stack(){
    int i;
	if (top == -1)
		printf("\n\t The stack is empty");
	else{
		printf("\n The elements of the stack are :");
		for(i=top; i>=0; i--)
        	printf("\n\t %d", stack[i]);
    }
    getch();
}

void display_top(){
	if (top == -1)
		printf("\n\t The stack is empty");
	else
		printf("\n The top of the stack is : %d", stack[top]);
    getch();
}

// interface for operation related to queue
void queue_() {
    int ch;
    while(1){
        system("cls");
        printf("\n\t\t Implementation of Queue using array");
        printf("\n\n\t 1. Enqueue operation ");
        printf("\n\t 2. Dequeue operation ");
        printf("\n\t 3. Display all elements ");
        printf("\n\t 4. Display front element ");
        printf("\n\t 5. Display rear element ");
        printf("\n\t 6. Exit");
        printf("\n\n Enter your choice: ");
        scanf("%d", &ch);
        switch(ch){
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display_all_queue();
            break;
        case 4:
            display_front();
            break;
        case 5:
            display_rear();
            break;
        case 6:
            printf("\n\n\t Program terminated successfully !!!");
            break;
        default:
            printf("\t\t Please enter the correct choice!!! \n");
        }
        if(ch==6)
            break;
    }
}

void enqueue() {
    int item;
    if(rear >= (maxsize-1))
        printf("\n\t The queue is full");
    else{
        printf("\n Enter the item: ");
        scanf("%d", &item);
        rear++;
        queue[rear] = item;
        printf("\t A new data is being enqueued in queue");
    }
    getch();
}

void dequeue(){
    if(front > rear)
        printf("\n\t The queue is empty");
    else{
        printf("\n The dequeued item is: %d",queue[front]);
        front++;
    }
    getch();
}

void display_all_queue(){
    int i;
    if(front > rear)
        printf("\n\t The queue is empty");
    else{
    	printf("\n Data in the queue is:");
        for(i=front; i<=rear; i++)
            printf("\n\t %d", queue[i]);
    }
    getch();
}

void display_front(){
    if(front > rear)
        printf("\n\t The queue is empty");
    else
        printf("\n The front element is: %d", queue[front]);
    getch();
}
void display_rear(){
    if(front > rear)
        printf("\n\t The queue is empty");
    else
        printf("\n The rear element is: %d", queue[rear]);
    getch();
}

// main program to allow user to implement stack or queue
int main() {
    int ch;
    while(1) {
        system("cls");
        printf("\n\t\t Welcome to Data Structure Implementation");
        printf("\n\n\t 1. Stack");
        printf("\n\t 2. Linear queue");
        printf("\n\t 3. Exit");
        printf("\n\n Enter your choice: ");
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            stack_();
            break;
        case 2:
            queue_();
            break;
        case 3:
            break;
        default:
        	printf("Wrong choice!!! Please make correct choice.");
        }
        if(ch==3)
        	break;
        getch();
    }
    return 0;
}