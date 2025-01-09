#include<stdio.h>
#include<ctype.h>
#include<string.h>

void followfirst(char, int, int);
void follow(char c);

int count = 8, n = 0;
int m = 0;

char calc_follow[10][100];
int k, e;
char ck, f[10];
char production[10][10];

int main(int argc, char **argv)
{
    int km = 0;
    int i, x, kay;
    char donee[count];
    int ptr = -1;
    int point1 = 0, point2;

    strcpy(production[0], "E=TR");
    strcpy(production[1], "R=+TR");
    strcpy(production[2], "R=#");
    strcpy(production[3], "T=FY");
    strcpy(production[4], "Y=*FY");
    strcpy(production[5], "Y=#");
    strcpy(production[6], "F=(E)");
    strcpy(production[7], "F=i");

    // Initializing the calc_follow array
    for(k = 0; k < count; k++) {
        for(kay = 0; kay < 100; kay++) {
            calc_follow[k][kay] = '!';
        }
    }

    int land = 0;
    for(e = 0; e < count; e++)
    {
        ck = production[e][0];
        point2 = 0;
        x = 0;

        for(kay = 0; kay <= ptr; kay++)
            if(ck == donee[kay])
                x = 1;

        if (x == 1)
            continue;
        land += 1;

        follow(ck);
        ptr += 1;

        donee[ptr] = ck;
        printf(" Follow(%c) = { ", ck);
        calc_follow[point1][point2++] = ck;

        for(i = 0 + km; i < m; i++) {
            int lark = 0, chk = 0;
            for(lark = 0; lark < point2; lark++) {
                if (f[i] == calc_follow[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if(chk == 0) {
                printf("%c, ", f[i]);
                calc_follow[point1][point2++] = f[i];
            }
        }
        printf(" }\n\n");
        km = m;
        point1++;
    }
}

void follow(char c)
{
    int i, j;

    if(production[0][0] == c) {
        f[m++] = '$';
    }
    for(i = 0; i < 10; i++) {
        for(j = 2;j < 10; j++) {
            if(production[i][j] == c) {
                if(production[i][j+1] != '\0') {
                    followfirst(production[i][j+1], i, (j+2));
                }
                if(production[i][j+1]=='\0' && c != production[i][0]) {
                    follow(production[i][0]);
                }
            }
        }
    }
}

void followfirst(char c, int c1, int c2)
{
    int k;

    if(!(isupper(c)))
        f[m++] = c;
    else {
        int i = 0, j = 1;
        for(i = 0; i < count; i++) {
            if(calc_follow[i][0] == c)
                break;
        }

        while(calc_follow[i][j] != '!') {
            if(calc_follow[i][j] != '#') {
                f[m++] = calc_follow[i][j];
            } else {
                if(production[c1][c2] == '\0') {

                    follow(production[c1][0]);
                } else {

                    followfirst(production[c1][c2], c1, c2+1);
                }
            }
            j++;
        }
    }
}
