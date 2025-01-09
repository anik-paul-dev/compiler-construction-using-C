#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchRegex(const char *regex, const char *example) {
    char regex1[100], regex2[100];
    int i = 0;
    while (regex[i] != '|' && regex[i] != '\0') {
        regex1[i] = regex[i];
        i++;
    }
    regex1[i] = '\0';

    if (regex[i] == '|') {
        int j = 0;
        i++;
        while (regex[i] != '\0') {
            regex2[j] = regex[i];
            i++;
            j++;
        }
        regex2[j] = '\0';
    } else {
        regex2[0] = '\0';
    }

    return (matchRegexPart(regex1, example) || matchRegexPart(regex2, example));
}

int matchRegexPart(const char *regex, const char *example) {
    int r_index = 0, e_index = 0;
    int r_len = strlen(regex);
    int e_len = strlen(example);

    while (r_index < r_len && e_index < e_len) {
        if (regex[r_index] == '0') {
            if (example[e_index] != '0')
                return 0;
            e_index++;
        } else if (regex[r_index] == '1') {

            if (example[e_index] != '1')
                return 0;
            e_index++;
        } else if (regex[r_index] == '*') {

            char prev_char = regex[r_index - 1];
            while (e_index < e_len && example[e_index] == prev_char)
                e_index++;
        }
        r_index++;
    }

    return (e_index == e_len && r_index == r_len);
}

int main() {

        char regex[100];
        char example[100];

            printf("Hello! ANIK_2076\n");
            printf("Enter random regular expression: ");
            scanf("%s", regex);

            printf("Enter example of string: ");
            scanf("%s", example);

            if (matchRegex(regex, example)) {
            printf("Matched\n");
            } else {
            printf("Not Matched\n");
            }

    return 0;
}
