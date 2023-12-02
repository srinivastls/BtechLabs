#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

void insert(int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
}

void display(){
    struct Node *temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}


// SORT IN nlogn time

void sort(){
    
}

int main(){

    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        int data;
        printf("Enter the data: ");
        scanf("%d", &data);
        insert(data);
    }

    display();
    sort();
    display();

    return 0;

}