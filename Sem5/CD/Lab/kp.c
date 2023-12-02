#include <stdio.h>
int editorMiss(const char *textinput) {
    int answer = 0;
    while (*textinput) {
        char ch = *textinput;
        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') ||
            ch == ' ') {
            textinput++;
        } else {
            answer++;
            textinput++;
        }
    }
    return answer;
}
int main() {
    char textinput[1000];
    fgets(textinput, sizeof(textinput), stdin);
    int answer = countMisses(textinput);
    printf("%d\n", answer);
return 0;
}