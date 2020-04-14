#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* makeString (char* s1 , char* s2 , char* s3);

int main ()
{
    printf("%s\n", makeString("abc", "de", "fg"));
    return 0;
}

char* makeString (char* s1 , char* s2 , char* s3)
{
    int n = strlen(s1) + strlen(s2) + strlen(s3);

    char* catStr = (char *) malloc(n * sizeof(char));
    if (catStr == NULL) return NULL;

    strcpy(catStr, s1);
    strcat(catStr, s2);
    strcat(catStr, s3);

    return catStr;
}

