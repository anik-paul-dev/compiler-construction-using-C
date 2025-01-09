#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 100

int isKeyword(char *str) {
    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for",
        "goto", "if", "int", "long", "register", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    int i;
    for (i = 0; i < numKeywords; ++i) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int isValidChar(char ch) {
    return isalnum(ch) || ch == '_';
}
int countAndDisplayVariables(FILE *file) {
    char word[MAX_LEN];
    int count = 0;
    char ch;
    int insideComment = 0, insideLineComment = 0, insideString = 0;

    typedef struct {
        char name[MAX_LEN];
        int count;
    } VariableCount;

    VariableCount variableCounts[MAX_LEN];
    int numVariables = 0;

    while ((ch = fgetc(file)) != EOF) {

        if (ch == '/') {
            ch = fgetc(file);
            if (ch == '*') {
                insideComment = 1;
            } else if (ch == '/') {
                insideLineComment = 1;
            } else {
                ungetc(ch, file);
            }
        } else if (ch == '*' && insideComment) {
            if ((ch = fgetc(file)) == '/') {
                insideComment = 0;
            }
        } else if (ch == '\n' && insideLineComment) {
            insideLineComment = 0;
        }

        if (ch == '"' || ch == '\'') {
            char quote = ch;
            insideString = !insideString;
            while (insideString && (ch = fgetc(file)) != EOF && ch != quote) {
                if (ch == '\\') fgetc(file);
            }
            insideString = 0;
        }

        if (ch == '#') {
            // Check for #include and handle <>
            char directive[MAX_LEN];
            int i = 0;
            directive[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isalpha(ch)) {
                directive[i++] = ch;
            }
            directive[i] = '\0';

            if (strcmp(directive, "#include") == 0) {
                while (ch != '<' && ch != '\n' && ch != EOF) {
                    ch = fgetc(file);
                }
                if (ch == '<') {
                    int j = 0;
                    while ((ch = fgetc(file)) != EOF && ch != '>') {
                        word[j++] = ch;
                    }
                    word[j] = '\0';
                    if (strlen(word) > 0) {
                        // Handle <stdio.h> or other header files
                        int found = 0;
                        int k;
                        for (k = 0; k < numVariables; ++k) {
                            if (strcmp(variableCounts[k].name, word) == 0) {
                                variableCounts[k].count++;
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            strcpy(variableCounts[numVariables].name, word);
                            variableCounts[numVariables].count = 1;
                            numVariables++;
                        }
                    }
                }
                while (ch != '\n' && ch != EOF) {
                    ch = fgetc(file);
                }
            }
        } else if (!insideComment && !insideLineComment && !insideString && isValidChar(ch)) {
            int i = 0;
            word[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isValidChar(ch)) {
                word[i++] = ch;
            }
            word[i] = '\0';

            if (!isKeyword(word) && !isdigit(word[0])) {
                int found = 0;
                int k;
                for (k = 0; k < numVariables; ++k) {
                    if (strcmp(variableCounts[k].name, word) == 0) {
                        variableCounts[k].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(variableCounts[numVariables].name, word);
                    variableCounts[numVariables].count = 1;
                    numVariables++;
                }
            }
        }
    }

    printf("Variable counts:\n");
    int i;
    for (i = 0; i < numVariables; ++i) {
        printf("%s: %d\n", variableCounts[i].name, variableCounts[i].count);
        count++;
    }

    return count;
}

int main() {
    char filename[50];
    FILE *file;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }
    int count = countAndDisplayVariables(file);
    fclose(file);
    printf("Total number of unique variables/identifiers: %d\n", count);
    return 0;
}
