#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool A(char *in, int *index) {
    if (in[*index] == 'a' || in[*index] == 'b' || in[*index] == 'c') {
        (*index)++;
        return true;
    }
    return false;
}

bool S(char *in, int *index);

bool SPrime(char *in, int *index) {
    if (in[*index] == '+') {
        (*index)++;
        if (A(in, index) && SPrime(in, index)) {
            return true;
        } else {
            return false;
        }
    }
    return true; 
}

bool S(char *in, int *index) {
    if (in[*index] == '(') {
        (*index)++;
        if (A(in, index) && SPrime(in, index)) {
            if (in[*index] == ')') {
                (*index)++;
                if (in[*index] == '*') {
                    (*index)++;
                    if (in[*index] == '$') {
                        (*index)++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    char in[100];
    printf("Enter a string in the format (a+b+c)*$: ");
    scanf("%s", in);

    int index = 0;
    if (S(in, &index) && in[index] == '\0') {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return 0;
}