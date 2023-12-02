#include <stdio.h>
#include <string.h>

#define MAX_PROD_RULES 100
#define MAX_NONTERMINALS 20
#define MAX_TERMINALS 20

typedef struct {                                            
  char lhs[MAX_NONTERMINALS + 1];
  char rhs[MAX_TERMINALS + 1][MAX_TERMINALS + 1];
  int num_rhs;
} ProductionRule;

typedef struct {
  char nonterminal;
  char production[MAX_TERMINALS + 1];
} ParsingTableEntry;

void read_grammar(ProductionRule *grammar, int *num_production_rules) {
  FILE *fp = fopen("grammar.txt", "r");
  if (fp == NULL) {
    printf("Error opening grammar file\n");
    exit(1);
  }

  int i = 0;
  while (1) {
    char line[100];
    if (fgets(line, 100, fp) == NULL) {
      break;
    }

    if (line[0] == '\n') {
      continue;
    }

    sscanf(line, "%s -> %s", grammar[i].lhs, grammar[i].rhs[0]);
    grammar[i].num_rhs = 1;
    for (int j = 1; j < MAX_TERMINALS; j++) {
      grammar[i].rhs[j][0] = '\0';
    }
    i++;
  }

  *num_production_rules = i;

  fclose(fp);
}

void compute_first(char *first, char *production, int num_rhs) {
  memset(first, 0, sizeof(char) * MAX_TERMINALS);

  for (int i = 0; i < num_rhs; i++) {
    if (production[i] != '\0') {
      if (production[i] >= 'a' && production[i] <= 'z') {
        first[production[i] - 'a'] = 1;
      } else {
        compute_first(first, production + i + 1, grammar[production[i] - 'A'].num_rhs);
      }
    }
  }
}

void compute_follow(char *follow, char *nonterminal) {
  memset(follow, 0, sizeof(char) * MAX_TERMINALS);

  follow[nonterminal - 'A'] = '$';

  for (int i = 0; i < num_production_rules; i++) {
    for (int j = 0; j < grammar[i].num_rhs; j++) {
      if (grammar[i].rhs[j][0] == nonterminal) {
        if (j + 1 < grammar[i].num_rhs) {
          compute_first(follow, grammar[i].rhs[j + 1], grammar[i].num_rhs);
        } else {
          for (int k = 0; k < MAX_TERMINALS; k++) {
            if (follow[k] == 0) {
              follow[k] = 1;
              break;
            }
          }
        }
      }
    }
  }
}

void print_parsing_table(ParsingTableEntry *parsing_table, int num_nonterminals, int num_terminals) {
  printf("Parsing Table:\n");
  for (int i = 0; i < num_nonterminals; i++) {
    printf("%-10s", grammar[i].lhs);
    for (int j = 0; j < num_terminals; j++) {
      printf("%-10s", parsing_table[i * num_terminals + j].production);
    }
    printf("\n");
  }
}

int main() {
  ProductionRule grammar[MAX_PROD_RULES];
  int num_production_rules;

  read_grammar(grammar, &num_production_rules);

  char first[MAX_NONTERMINALS];
  char follow[MAX_NONTERMINALS];

