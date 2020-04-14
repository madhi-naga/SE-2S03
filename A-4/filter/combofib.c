#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100


char* combofib(int n) {

    char* f2 = (char*) malloc(N*sizeof(char) );
    char* f1 = (char*) malloc(N*sizeof(char) );
    char* next = (char*) malloc(N*sizeof(char) );
    int i;
    for (i = 3; i <= n; i++){
        if (i == 3){
            strcpy(f2, "0");
            strcpy(next, "01");
        }
        else{
            strcpy(f1, f2);
            strcpy(f2, next);
            strcat(next, f1);
        }
    }
    return next;
}


int main(){

    printf("%s\n", combofib(7));


}