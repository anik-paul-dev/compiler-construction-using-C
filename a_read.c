#include <stdio.h>

void main() {
    FILE *source_file;
    char ch

    /* if
    write the code

    */

    // c file in reading
    source_file = fopen("anik.c", "r");
    if (source_file == NULL) {
        printf("Error");

    }
    // writing c file
    //Read character by character from the source file
    while ((ch = fgetc(source_file)) != EOF){   //EOF = End of file
        printf("%c", ch);
    }
    return 0;
}
