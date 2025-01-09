#include <stdio.h>

void main() {
    FILE *source_file, *destination_file;
    char ch;

    // read mode
    source_file = fopen("New.txt", "r");
    if (source_file == NULL) {
        printf("Error");
    }

    // write mode
    destination_file = fopen("new.txt", "w");

    // Read character by character from the source file
    while ((ch = fgetc(source_file)) != EOF) {
        // Write each character to the destination file
        fputc(ch, destination_file);
    }

    printf("File copied successfully.\n");

    return 0;
}
