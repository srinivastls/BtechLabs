#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>

char *keywords[] = {"auto","break","case","char","const","continue","default",
                    "do","double","else","enum","extern","float","for","goto",
                    "if","int","long","register","return","short","signed",
                    "sizeof","static","struct","switch","typedef","union",
                    "unsigned","void","volatile","while"};

char *operators[] = {"+","-","*","/","%","++","--","==","!=",">","<",">=","<=",
                     "&&","||","!","&","|","^","<<",">>","~","=","+=","-=","*=",
                     "/=","%=","<<=",">>=","&=","^=","|="};

char *special[] = {"[","]","(",")","{","}",".",",",";","#","\"","'","\\","!","@","$","?"};


int main(){
    FILE *file1,*file2;
    char F_path[20];     // we assume that the path of the file is less than 20 character;
    
    file1=fopen("input.c","r");
    file2=fopen("output3.txt","w");
    char C_char, n_Char;
    while ((C_char = fgetc(file1)) != EOF) {
        if (C_char == '/') {
            n_Char = fgetc(file1);
            if (n_Char == '/') {
                while ((C_char = fgetc(file1)) != '\n' && C_char != EOF);
            }
            else if (n_Char == '*') {
                while (!((C_char = fgetc(file1)) == '*' && (n_Char = fgetc(file1)) == '/')) {
                    if (C_char == EOF) {
                        printf("Error: Unclosed multi-line comment.\n");
                        return 1;
                    }
                }
            }
            else {
                fputc(C_char, file2);
                fputc(n_Char, file2);
            }
        }
        else {
            fputc(C_char,file2);
        }
    }

    fclose(file1);
    fclose(file2);
    
    file1=fopen("output3.txt","r");
    file2=fopen("output5.txt","w");

    if(!file1){
        printf("unable to open the file: %s\n",F_path);
        return 0;
    }
    int c_line=0,c_word=0,c_char=0,c_vowels=0 ,c_consonants=0,c_digits=0 ,c_extras=0,current=0;
    char line[1000];
    while (fgets(line, sizeof(line), file1) != NULL) { 
              

              if(line[0] != '#'){
        
        char *token = strtok(line, " ()\t\n");
        
        

        while (token != NULL) {
            fputc(token,file2);
         bool isKeyword = false;
         bool isOperator = false;
         bool isSpecial = false;
            for (int i = 0; i < 32; i++) {
            if (strcmp(keywords[i], token) == 0 ) {
                isKeyword = true;
                c_word++;
                break;
        }
            }
            for (int i = 0; i < 33; i++) {
            if (strcmp(operators[i], token) == 0 ) {
                isOperator = true;
                printf("%s is a operator\n", token);
                c_digits++;
                break;
        }
            }
            for (int i = 0; i < 17; i++) {
            if (strcmp(special[i], token) == 0 ) {
                isSpecial = true;
                c_vowels++;
                break;
        }
            }
            if (!isKeyword && !isOperator && !isSpecial) {
                c_extras++;
            }
        
            token = strtok(NULL, " ()\t\n");
            
        
        
    }
    }
    }
    fclose(file1);
    fclose(file2);
    
    printf("the counted values of keywords:%d\n",c_word);
    printf("the counted values of operators:%d\n",c_digits);
    printf("the counted values of identifiers:%d\n",c_extras);
    printf("the counted values of special characters:%d\n",c_vowels);


    return 0;
}

