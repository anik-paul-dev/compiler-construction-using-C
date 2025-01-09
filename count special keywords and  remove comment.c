#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32
#define MAX_KEYWORD_LENGTH 20

int main() {
    FILE *inputFile, *outputFile, *file;
    char inputFileName[100], outputFileName[100], filename[100];
    char ch, prev;
    int singleLineComment = 0, multiLineComment = 0;
    int counts[MAX_KEYWORDS] = {0};
    char word[MAX_KEYWORD_LENGTH];
    int i;

    char keywords[MAX_KEYWORDS][MAX_KEYWORD_LENGTH] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };


    printf("Enter the input file name: ");
    scanf("%s", inputFileName);


    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error: Could not open file %s\n", inputFileName);
        return 1;
    }


    printf("Enter the output file name for removing comments: ");
    scanf("%s", outputFileName);


    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error: Could not create file %s\n", outputFileName);
        fclose(inputFile);
        return 1;
    }


    while ((ch = fgetc(inputFile)) != EOF) {
        if (!singleLineComment && !multiLineComment) {
            if (ch == '/') {
                if ((prev = fgetc(inputFile)) == '/') {
                    singleLineComment = 1;
                } else if (prev == '*') {
                    multiLineComment = 1;
                } else {
                    fputc(ch, outputFile);
                    fputc(prev, outputFile);
                }
            } else {
                fputc(ch, outputFile);
            }
        } else if (singleLineComment && ch == '\n') {
            singleLineComment = 0;
            fputc(ch, outputFile);
        } else if (multiLineComment && prev == '*' && ch == '/') {
            multiLineComment = 0;
        }

        prev = ch;
    }


    fclose(inputFile);
    fclose(outputFile);

    printf("Comments removed successfully and saved in %s!\n", outputFileName);


    printf("\n");
    printf("Enter the filename to detect keywords: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (fscanf(file, "%s", word) == 1) {
        for (i = 0; i < MAX_KEYWORDS; i++) {
            if (strcmp(word, keywords[i]) == 0) {
                counts[i]++;
                break;
            }
        }
    }
    printf("\nPresented Keywords and their counts:\n");
    for (i = 0; i < MAX_KEYWORDS; i++) {
        if (counts[i] > 0) {
            printf("%s - %d\n", keywords[i], counts[i]);
        }
    }


    fclose(file);

    return 0;
}
