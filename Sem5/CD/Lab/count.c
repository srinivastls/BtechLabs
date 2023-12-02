#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char f_path[10]; 

    printf("Enter the input file path: ");
    scanf("%s", f_path);

    FILE *f = fopen(f_path, "r");
    if (!f) {
        printf("unable to open the file: %s\n", f_path);
        return 0;
    }

    
    int c_line=0,c_word=0,c_char=0,c_vowels=0 ,c_consonants=0,c_digits=0 ,c_extras=0,current=0;
    char line[1000];
    while (fgets(line, sizeof(line), f) != NULL) {
        c_line++;
        c_char += strlen(line);

        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            c_word++;
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(f);
    f = fopen(f_path, "r");
    if (!f) {
        printf("unable to open the file: %s\n", f_path);
        return 0;
    }
    while ((current= fgetc(f)) != EOF) {
        //  count of characters based on division 
        if (isalpha(current)) {
            current = tolower(current); 
            if (current == 'a' || current == 'e' || current == 'i' || current == 'o' || current == 'u') {
                c_vowels++; // 1.count of vowels
            } else {
                c_consonants++; // 2.count of consonants 
            }
        } else if (isdigit(current)) { 
            c_digits++;   // 3.count of digits
        } else {
            c_extras++;   // 4.count of all other extra characters
        } 
    }

    fclose(f);
    printf("the counted values are as follows:\n");
    printf("no of lines: %d\n", c_line);
    printf("no of words: %d\n", c_word);
    printf("no of characters: %d\n", c_char);
    printf("1.no of vowels: %d\n", c_vowels);
    printf("2.no of consonants: %d\n", c_consonants);
    printf("3.no of digits: %d\n", c_digits);
    printf("4.no of extra characters: %d\n", c_extras);
    printf("Sum of 1st + 2nd + 3rd + 4th: %d\n", c_vowels + c_consonants + c_digits + c_extras);

    return 0;
}
