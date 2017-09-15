#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "aparse.h"

int main(int argc, char* argv[]){

    char buffer[BUFFER];
    printf("--------------------------------------------\n");
    printf("       ARITHMETIC EXPRESSION PARSER         |\n");
    printf("         (ENTER \"exit\" TO EXIT)             |\n");
    printf("--------------------------------------------\n");
    char iExpression[BUFFER];
    char iKeyword[30];
    while (1){
        fflush(stdin);
        zeroFill(buffer, BUFFER);
        zeroFill(iExpression, BUFFER);
        zeroFill(iKeyword, 30);

        printf("\n[>] ");
        gets(buffer);

        gin(buffer, iKeyword, iExpression);

        switch(inparse(iKeyword, iExpression)){
        case 1:
            return 0;
            break;
        case -1:
            printf("[*] Invalid Keyword.\n");
            continue;
        case -2:
            printf("[*] Invalid Arithmetic Expression.\n");
            continue;
        default:
            continue;
        }

        getKeyword(buffer, iKeyword);
    }

    return 0;
}
