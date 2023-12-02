#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULE_LEN 100
#define MAX_SYMBOLS 100

// Structure to represent a production rule
struct ProductionRule {
    char nonTerminal;
    char symbols[MAX_RULE_LEN];
};

// Structure to represent FIRST and FOLLOW sets
struct Sets {
    char nonTerminal;
    char first[MAX_SYMBOLS];
    char follow[MAX_SYMBOLS];
};

// Function to determine if a symbol is epsilon ('#')
bool isEpsilon(char symbol) {
    return (symbol == '#');
}

// Function to determine if a symbol is a terminal
bool isTerminal(char symbol) {
    return (symbol >= 'a' && symbol <= 'z');
}

// Function to initialize a set
void initializeSet(char set[]) {
    set[0] = '\0';
}

// Function to add a symbol to a set
void addToSet(char set[], char symbol) {
    if (strchr(set, symbol) == NULL) {
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}

// Function to compute FIRST sets
void computeFirstSets(struct ProductionRule rules[], int numRules, struct Sets firstSets[]) {
    bool changed = true;

    while (changed) {
        changed = false;

        for (int i = 0; i < numRules; i++) {
            char nonTerminal = rules[i].nonTerminal;
            char *production = rules[i].symbols;

            int j = 0;
            while (production[j] != '\0') {
                char symbol = production[j];

                if (isTerminal(symbol)) {
                    addToSet(firstSets[nonTerminal - 'A'].first, symbol);
                    break;
                } else if (isEpsilon(symbol)) {
                    addToSet(firstSets[nonTerminal - 'A'].first, symbol);
                } else {
                    int symbolIndex = symbol - 'A';
                    char *firstSet = firstSets[symbolIndex].first;

                    int k;
                    for (k = 0; firstSet[k] != '\0'; k++) {
                        if (firstSet[k] != '#') {
                            addToSet(firstSets[nonTerminal - 'A'].first, firstSet[k]);
                        }
                    }

                    if (firstSet[k] == '\0') {
                        // If we reached the end of FIRST(symbol), continue to the next symbol
                        break;
                    }
                }

                j++;
            }
        }
    }
}

// Function to compute FOLLOW sets
void computeFollowSets(struct ProductionRule rules[], int numRules, struct Sets firstSets[], struct Sets followSets[]) {
    bool changed = true;

    while (changed) {
        changed = false;

        for (int i = 0; i < numRules; i++) {
            char nonTerminal = rules[i].nonTerminal;
            char *production = rules[i].symbols;

            for (int j = 0; production[j] != '\0'; j++) {
                char symbol = production[j];

                if (!isTerminal(symbol)) {
                    int symbolIndex = symbol - 'A';

                    for (int k = j + 1; production[k] != '\0'; k++) {
                        if (isTerminal(production[k])) {
                            addToSet(followSets[symbolIndex].follow, production[k]);
                            break;
                        } else if (isEpsilon(production[k])) {
                            for (int l = 0; followSets[nonTerminal - 'A'].follow[l] != '\0'; l++) {
                                addToSet(followSets[symbolIndex].follow, followSets[nonTerminal - 'A'].follow[l]);
                            }
                        } else {
                            int nextSymbolIndex = production[k] - 'A';
                            char *firstSet = firstSets[nextSymbolIndex].first;

                            int m;
                            for (m = 0; firstSet[m] != '\0'; m++) {
                                if (firstSet[m] != '#') {
                                    addToSet(followSets[symbolIndex].follow, firstSet[m]);
                                }
                            }

                            if (firstSet[m] == '\0' || strchr(firstSets[nextSymbolIndex].first, '#') == NULL) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Function to initialize the LL(1) parsing table
void initializeLL1Table(char *ll1Table[][MAX_SYMBOLS]) {
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            ll1Table[i][j] = NULL;
        }
    }
}

// Function to add a production to the LL(1) parsing table
void addToLL1Table(char *ll1Table[][MAX_SYMBOLS], char nonTerminal, char terminal, const char *production) {
    int nonTerminalIndex = nonTerminal - 'A';
    int terminalIndex = terminal - 'a';

    if (ll1Table[nonTerminalIndex][terminalIndex] == NULL) {
        ll1Table[nonTerminalIndex][terminalIndex] = strdup(production);
    } else {
        // Handle conflicts (e.g., print an error message or choose a resolution strategy)
    }
}

// Function to print the LL(1) parsing table
void printLL1ParsingTable(char *ll1Table[][MAX_SYMBOLS], int numNonTerminals) {
    printf("LL(1) Parsing Table:\n");

    // Print the table headers (terminals)
    printf("%5s", "");
    for (char terminal = 'a'; terminal <= 'z'; terminal++) {
        printf("%5c", terminal);
    }
    printf("\n");

    // Print the table entries
    for (int i = 0; i < numNonTerminals; i++) {
        char nonTerminal = 'A' + i;
        printf("%5c", nonTerminal);
        for (char terminal = 'a'; terminal <= 'z'; terminal++) {
            char *production = ll1Table[i][terminal - 'a'];
            if (production != NULL) {
                printf("%5s", production);
            } else {
                printf("%5s", "");
            }
        }
        printf("\n");
    }
}

int main() {
    // Parse the input CFG from the input file and represent it in a data structure
    struct ProductionRule rules[MAX_RULE_LEN];
    int numRules = 0;

    FILE *file = fopen("CFG", "r");
    if (file == NULL) {
        perror("Error opening input.cfg");
        exit(1);
    }

    char line[MAX_RULE_LEN];
    while (fgets(line, sizeof(line), file)) {
        
        if (line[0] != '#') {
            sscanf(line, " %c -> %s", &rules[numRules].nonTerminal, rules[numRules].symbols);
            numRules++;
        }
    }
    fclose(file);

    // Determine the set of terminals (T) and non-terminals (NT)
    int numNonTerminals = 0;
    int numTerminals = 0;
    bool isNonTerminal[MAX_RULE_LEN] = {0};

    for (int i = 0; i < numRules; i++) {
        char nonTerminal = rules[i].nonTerminal;
        
        if (!isNonTerminal[nonTerminal - 'A']) {
            isNonTerminal[nonTerminal - 'A'] = true;
            numNonTerminals++;
        }

        char *production = rules[i].symbols;
        for (int j = 0; production[j] != '\0'; j++) {
            char symbol = production[j];
            if (isTerminal(symbol)) {
                numTerminals++;
            }
        }
    }

    // Initialize an LL(1) parsing table data structure
    char *ll1Table[MAX_SYMBOLS][MAX_SYMBOLS];
    initializeLL1Table(ll1Table);

    // Implement functions to compute FIRST and FOLLOW sets
    struct Sets firstSets[MAX_SYMBOLS];
    struct Sets followSets[MAX_SYMBOLS];

    for (int i = 0; i < numNonTerminals; i++) {
        firstSets[i].nonTerminal = 'A' + i;
        initializeSet(firstSets[i].first);
        initializeSet(firstSets[i].follow);
    }

    for (int i = 0; i < numRules; i++) {
        char nonTerminal = rules[i].nonTerminal;
        if (isTerminal(rules[i].symbols[0])) {
            addToSet(firstSets[nonTerminal - 'A'].first, rules[i].symbols[0]);
        }
    }

    computeFirstSets(rules, numRules, firstSets);
    computeFollowSets(rules, numRules, firstSets, followSets);

    // Fill in the LL(1) parsing table
    for (int i = 0; i < numRules; i++) {
        char nonTerminal = rules[i].nonTerminal;
        char *production = rules[i].symbols;
        
        if (isEpsilon(production[0])) {
            for (int k = 0; followSets[nonTerminal - 'A'].follow[k] != '\0'; k++) {
                char terminal = followSets[nonTerminal - 'A'].follow[k];
                addToLL1Table(ll1Table, nonTerminal, terminal, "#");
            }
        } else {
            for (int j = 0; production[j] != '\0'; j++) {
                char symbol = production[j];
                if (isTerminal(symbol)) {
                    addToLL1Table(ll1Table, nonTerminal, symbol, production);
                    break;
                } else if (!isEpsilon(symbol)) {
                    int symbolIndex = symbol - 'A';
                    char *firstSet = firstSets[symbolIndex].first;

                    for (int k = 0; firstSet[k] != '\0'; k++) {
                        if (firstSet[k] != '#') {
                            addToLL1Table(ll1Table, nonTerminal, firstSet[k], production);
                        }
                    }

                    if (strchr(firstSet, '#') == NULL) {
                        break;
                    }
                }
            }
        }
    }

    // Print the LL(1) parsing table
    printLL1ParsingTable(ll1Table, numNonTerminals);

    return 0;
}
