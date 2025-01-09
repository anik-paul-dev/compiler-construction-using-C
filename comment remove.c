#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[100], outputFileName[100];
    char ch, prev;
    int singleLineComment = 0, multiLineComment = 0;

    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error: Could not open file %s\n", inputFileName);
        return 1;
    }
    printf("Enter the output file name: ");
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
    printf("Comments removed successfully!\n");
    return 0;}
