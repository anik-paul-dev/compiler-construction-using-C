#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eliminateLeftRecursion(char* nonTerminal, char* production) {
    char alpha[100] = "";
    char beta[100] = "";
    int hasLeftRecursion = 0;

    // Split production rules by '|'
    char* token = strtok(production, "|");
    while (token != NULL) {
        if (token[0] == nonTerminal[0]) {
            // Left-recursive part
            strcat(alpha, token + 1);
            strcat(alpha, nonTerminal); // Append the non-terminal
            strcat(alpha, "|");
            hasLeftRecursion = 1;
        } else {
            // Non-recursive part
            strcat(beta, token);
            strcat(beta, nonTerminal); // Append the non-terminal
            strcat(beta, "|");
        }
        token = strtok(NULL, "|");
    }

    if (hasLeftRecursion) {
        // Remove trailing '|'
        alpha[strlen(alpha) - 1] = '\0';
        beta[strlen(beta) - 1] = '\0';

        // Print the transformed productions
        printf("%s -> %s'\n", nonTerminal, beta);
        printf("%s' -> %s | e\n", nonTerminal, alpha);
    } else {
        // No left recursion found, print the original production
        printf("%s -> %s\n", nonTerminal, production);
    }
}

int main() {
    char nonTerminal[10];
    char production[100];

    printf("Enter non-terminal:");
    scanf("%s", nonTerminal);

    printf("Enter production rules: ");
    scanf(" %[^\n]", production);

    printf("\nEliminating left recursion for: %s -> %s\n", nonTerminal, production);
    eliminateLeftRecursion(nonTerminal, production);

    return 0;
}
