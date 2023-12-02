// T.LAKSHMI SRINVAS
// CS21B2045
#include <stdio.h>
#include <stdlib.h>

//Declaring Global Variable Toke
char token;

//Declaring The Required Functions
void fA();
void fS();
void fB();
void error();

//Declaring The Required Recursive Terminal Functions
void fS(){
    switch (token) {
        case 'a':
            token=getchar();
            fA();
            fS();
            break;
        case 'c':
            token=getchar();
            break;
        default:
            error();

    }

}


void fA(){
    switch (token) {
        case 'b':
            token=getchar();
            if(token=='a')token=getchar();
            else error();
            break;
        case 'a':
            fS();
            fB();
            break;
        case 'c':
            fS();
            fB();
            break;
        default:
            error();

    }
}

void fB(){
    switch (token) {
        case 'b':
            token=getchar();
            fA();
            break;
        case 'a':
            fS();
            break;
        case 'c':
            fS();
            break;
        default:
            error();
    }

}

//error function when the string is rejected
void error(){
    printf("The String is Rejected");
    exit(0);
}


//Declaring Global Variable Toke
char token;

//Declaring Main Function
int main(){
    printf("Please enter the required string\n");
    token = getchar();
    fS();
    if(token=='$')
        printf("Accept");
    else
        error();
}

