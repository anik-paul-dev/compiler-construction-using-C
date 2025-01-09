#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eliminateLeftRecursion(char* nonTerminal, char* production, char* transformedProduction) {
    char alpha[100] = "";
    char beta[100] = "";
    int hasLeftRecursion = 0;

    char productionCopy[100];
    strcpy(productionCopy, production);

    char* token = strtok(productionCopy, "|");
    while (token != NULL) {
        if (token[0] == nonTerminal[0]) {
            strcat(alpha, token + 1);
            strcat(alpha, nonTerminal);
            strcat(alpha, "|");
            hasLeftRecursion = 1;
        } else {
            strcat(beta, token);
            strcat(beta, nonTerminal);
            strcat(beta, "|");
        }
        token = strtok(NULL, "|");
    }

    if (hasLeftRecursion) {
        alpha[strlen(alpha) - 1] = '\0';
        beta[strlen(beta) - 1] = '\0';

        printf("%s -> %s'\n", nonTerminal, beta);
        printf("%s' -> %s | e\n", nonTerminal, alpha);

        snprintf(transformedProduction, 100, "%s|%s'", beta, nonTerminal);
    } else {
        printf("%s -> %s\n", nonTerminal, production);
        strcpy(transformedProduction, production);
    }
}

void eliminateLeftFactoring(char* nonTerminal, char* production) {
    char part1[20], part2[20], modifiedGram[20], newGram[20];
    int i, j = 0, k = 0, pos;

    for (i = 0; production[i] != '|' && production[i] != '\0'; i++, j++)
        part1[j] = production[i];
    part1[j] = '\0';

    if (production[i] == '|') {
        for (j = ++i, i = 0; production[j] != '\0'; j++, i++)
            part2[i] = production[j];
        part2[i] = '\0';
    } else {
        strcpy(part2, "");
    }

    for (i = 0; i < strlen(part1) && i < strlen(part2); i++) {
        if (part1[i] == part2[i]) {
            modifiedGram[k++] = part1[i];
            pos = i + 1;
        }
    }
    modifiedGram[k] = '\0';

    if (k > 0) {
        for (i = pos, j = 0; part1[i] != '\0'; i++, j++)
            newGram[j] = part1[i];
        if (j > 0)
            newGram[j++] = '|';
        for (i = pos; part2[i] != '\0'; i++, j++)
            newGram[j] = part2[i];
        newGram[j] = '\0';

        printf("Grammar With Left Factoring:\n");
        printf("%s -> %sX\n", nonTerminal, modifiedGram);
        printf("X -> %s\n", newGram);
    } else {
        printf("No common prefixes found. Original production is:\n");
        printf("%s -> %s\n", nonTerminal, production);
    }
}

int hasLeftRecursion(char* nonTerminal, char* production) {
    char productionCopy[100];
    strcpy(productionCopy, production);

    char* token = strtok(productionCopy, "|");
    while (token != NULL) {
        if (token[0] == nonTerminal[0]) {
            return 1;
        }
        token = strtok(NULL, "|");
    }
    return 0;
}

int hasLeftFactoring(char* production) {
    char part1[20], part2[20];
    int i, j = 0;

    for (i = 0; production[i] != '|' && production[i] != '\0'; i++, j++)
        part1[j] = production[i];
    part1[j] = '\0';

    if (production[i] == '|') {
        for (j = ++i, i = 0; production[j] != '\0'; j++, i++)
            part2[i] = production[j];
        part2[i] = '\0';
    } else {
        strcpy(part2, "");
    }

    for (i = 0; i < strlen(part1) && i < strlen(part2); i++) {
        if (part1[i] == part2[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char nonTerminal[10];
    char production[100];
    char transformedProduction[100];

    printf("Enter non-terminal: ");
    scanf("%s", nonTerminal);
    getchar();

    printf("Enter production rules: ");
    fgets(production, 100, stdin);
    production[strcspn(production, "\n")] = 0;

    if (hasLeftRecursion(nonTerminal, production)) {
        printf("\nEliminating left recursion for: %s -> %s\n", nonTerminal, production);
        eliminateLeftRecursion(nonTerminal, production, transformedProduction);
        strcpy(production, transformedProduction);
    }

    if (hasLeftFactoring(production)) {
        printf("\nAdding left factoring for: %s -> %s\n", nonTerminal, production);
        eliminateLeftFactoring(nonTerminal, production);
    }

    return 0;
}
