/*
1. Given a file name, Write a C program to take it as an argument to count the number of tokens and detect the type of tokens.
Tasks to be done.
-Removing preprocessor directives, whitespaces, tab spaces, empty lines, and comments lines.
-Identify the tokens and detect the tokens with their 6 types (as attached below)
-Print the number of tokens of each type.*/
/*
T.Lakshmi srinivas
CS21B2045
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Returns true if the string is a KEYWORD.
bool isKeyword(char* str){
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") || !strcmp(str, "continue") ||
        !strcmp(str, "int") || !strcmp(str, "double") ||
        !strcmp(str, "float") || !strcmp(str, "return") ||
        !strcmp(str, "char") || !strcmp(str, "case") ||
        !strcmp(str, "auto") || !strcmp(str, "sizeof") ||
        !strcmp(str, "long") || !strcmp(str, "short") ||
        !strcmp(str, "typedef") || !strcmp(str, "switch") ||
        !strcmp(str, "unsigned") || !strcmp(str, "void") ||
        !strcmp(str, "static") || !strcmp(str, "struct") ||
        !strcmp(str, "goto") || !strcmp(str, "const") ||
        !strcmp(str, "default") || !strcmp(str, "enum") ||
        !strcmp(str, "extern")|| !strcmp(str, "for") ||
        !strcmp(str, "volatile")|| !strcmp(str, "register") ||
        !strcmp(str, "union")|| !strcmp(str, "signed"))
        return (true);
    return (false);
}
// Returns true if the character is a DELIMITER.
bool isDelimiter(char ch){
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}'||ch == '|' || ch == '&' || ch == '!')
        return (true);
    return (false);
}

// Returns true if the character is an OPERATOR.
bool isOperator(char ch){
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&' || ch == '^' || ch == '!')
        return (true);
    return (false);
}

// Returns true if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str){
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}



// Returns true if the string is an INTEGER.
bool isInteger(char* str){
    int i, len = strlen(str);
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns true if the string is a REAL no.
bool isRealno(char* str){
    int i, len = strlen(str);
    bool hasDecimal = false;
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// Returns true if the character is a SPECIAL SYMBOL.
bool isSpecialSymbol(char ch){
    if( ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
        return true;
    return false;
}

// Extracts the SUBSTRING given the start, end position and the string
char* subString(char* str, int left, int right){
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

// Function for removing redundant lines, spaces and comments
void remover(char* filename) {
    FILE *reqFilePtr = fopen(filename,"r");
    FILE *outputFilePtr = fopen("temp.c","w");
    int prevChar = '\n';
    int currentChar = fgetc(reqFilePtr);
    while (currentChar != EOF){
        // remove multiline comments
        if(currentChar == '*' && prevChar == '/'){
            while(1){
                if(currentChar == '/' && prevChar == '*'){
                    break;
                }
                prevChar =currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
            // remove single line comments
        else if(currentChar == '/' && prevChar == '/'){
            while(1){
                if(currentChar == '\n'){
                    break;
                }
                prevChar =currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
            // remove redundant spaces
        else if(currentChar == ' ' && prevChar == ' '){
            while(1){
                if(currentChar != ' '){
                    break;
                }
                prevChar =currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
            // remove redundant lines
        else if(currentChar == '\n' && prevChar == '\n'){
            while(1){
                if(currentChar != '\n'){
                    break;
                }
                prevChar =currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
            // remove preprocessor directives
        else if(prevChar == '#'){
            while(1){
                
                if(currentChar == '\n'){
                    break;
                }
                prevChar =currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
            // else insert the char into the file
        else{
            fputc(prevChar,outputFilePtr);
            prevChar =currentChar;
            currentChar = fgetc(reqFilePtr);
        }
    }
    fputc(prevChar,outputFilePtr);
    fclose(reqFilePtr);
    fclose(outputFilePtr);
    reqFilePtr = fopen(filename,"w");
    outputFilePtr = fopen("temp.c","r");
    char c = fgetc(outputFilePtr);
    while (c != EOF){
        fputc(c, reqFilePtr);
        c = fgetc(outputFilePtr);
    }
    fclose(reqFilePtr);
    fclose(outputFilePtr);
}

// Parsing the input STRING.
void parser(FILE *fp1, FILE *fp2){
    char str[1000] = "";

    int string_count = 0;
    int keyword_count = 0;
    int identifier_count = 0;
    int integer_count = 0;
    int real_count = 0;
    int special_count = 0;
    int operator_count = 0;

    while (fgets(str, sizeof(str), fp1)) {
        int left = 0, right = 0;
    int len = strlen(str);
    
    while (right <= len && left <= right) {
        if(str[right] == '\n') break;
        if(str[right] == '"'){
            left = right;
            right++;
            while(str[right] != '"'){
                right++;
            }
            string_count++;
            char* subStr = subString(str, left, right);
            fputs(subStr,fp2);
            fputs(" IS A STRING\n", fp2);
            right++;
            left = right;
            continue;
        }
        if (isDelimiter(str[right]) == false)
            right++;
        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true){
                while(isOperator(str[right]) == true){
                    right++;
                }
                right--;
                operator_count++;
                char* subStr = subString(str, left, right);
                fputs(subStr,fp2);
                fputs(" IS AN OPERATOR\n", fp2);
            }
            else if(isSpecialSymbol(str[right]) == true){
                special_count++;
                fputc(str[right],fp2);
                fputs(" IS A SPECIAL SYMBOL\n", fp2);
            }
            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
            if (isKeyword(subStr) == true){
                keyword_count++;
                fputs(subStr,fp2);
                fputs(" Is a Keyword\n", fp2);
            }
            else if (isInteger(subStr) == true || isRealno(subStr) == true){
                if(isInteger(subStr) == true) integer_count++;
                else real_count++;
                fputs(subStr,fp2);
                fputs(" Is a Constant\n", fp2);
            }
            else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
                identifier_count++;
                fputs(subStr,fp2);
                fputs(" IS A VALID IDENTIFIER\n", fp2);
            }
            else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
                fputs(subStr,fp2);
                fputs(" IS NOT A VALID IDENTIFIER\n", fp2);
            }
            left = right;
        }
    }}
    printf("1.The no of identifiers are %d\n", identifier_count);
    printf("2.The no of keywords are %d\n", keyword_count);
    printf("3.The no of constants are %d\n", integer_count+real_count);
    printf("4.The no of operators are %d\n", operator_count);
    printf("5.The no of special symbols are %d\n", special_count);
    printf("6.The no of strings are %d\n", string_count);
    printf("7.The no of tokens: %d\n", identifier_count+keyword_count+integer_count+real_count+operator_count+special_count+string_count);
    return;
}

int main(){
    FILE *fp1, *fp2;
    
    fp1 = fopen("input.c","r");
    remover("input.c");
    remover("input.c");
    fp2 = fopen("result.txt", "w");
    
    parser(fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    return (0);
}