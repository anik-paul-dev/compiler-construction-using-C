#include <stdio.h>

void main() {
    FILE *source_file;
    char ch;

    

    
    source_file = fopen("anik.c", "r");
    if (source_file == NULL) {
        printf("Error");

    }

    
    
    while ((ch = fgetc(source_file)) != EOF){   
        printf("%c", ch);
    }
    return 0;
}
