#include <stdio.h>
#include <ctype.h>

int main() {
    printf( " enter the path of input file :");
    char path[20];
    scanf("%s",path);
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("unable to open the  file\n");
        return 0;
    }

    int line_c , word_c,char_c,vowel_c,consonant_c,digit_c,extra_c;

    int current_char;
    int in_word = 0;

    while ((current_char = fgetc(f)) != EOF) {
        char_c++;
        //  word count
        if (!isspace(current_char) && !in_word) {
            word_c++;
            in_word = 1;
        } else if (isspace(current_char)) {
            in_word = 0;
        }
        // count of lines
        if (current_char == '\n') {
            line_c++;
        }
        

        //  count of characters based on division 
        if (isalpha(current_char)) {
            current_char = tolower(current_char); 
            if (current_char == 'a' || current_char == 'e' || current_char == 'i' || current_char == 'o' || current_char == 'u') {
                vowel_c++;
            } else {
                consonant_c++;
            }
        } else if (isdigit(current_char)) {
            digit_c++;
        } else {
            extra_c++;
        }
    }

    // Closing  the file
    fclose(f);
    // since the lines started counting from zero we have to add one
    printf("no of lines: %d\n", line_c+1);
    printf("no of words: %d\n", word_c);
    printf("no of characters: %d\n", char_c);
    printf("no of vowels: %d\n", vowel_c);
    printf("no of consonants: %d\n", consonant_c);
    printf("no of digits: %d\n", digit_c);
    printf("no of extra characters: %d\n", extra_c);
    printf("Sum of characters: %d\n", vowel_c + consonant_c + digit_c + extra_c);

    return 0;
}
