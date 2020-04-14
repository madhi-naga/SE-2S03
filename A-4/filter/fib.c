#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000000
#define zero '0'
#define one '1'


typedef enum {
    up,
    down,
    left,
    right
} direction;


int fib(int n, int x, int y, int step, RGB b, RGB f, int w, int h, RGB* image);
double getTime(int);
char* fibCombo(int n);

/* draw is from main_line2.c example*/
void draw(int x, int y, direction dir, int step, int w, RGB* im, RGB c)
{
#define I(i, j) im[(i)*w + j]
    int j;
    if (dir == up)
        for (j = 0; j < step; j++)
            I(x + j, y) = c;
    if (dir == down)
        for (j = 0; j < step; j++)
            I(x - j, y) = c;
    if (dir == right)
        for (j = 0; j < step; j++)
            I(x, y + j) = c;
    if (dir == left)
        for (j = 0; j < step; j++)
            I(x, y - j) = c;
#undef I
}


int fib(int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB* image){

    char* fibword = fibCombo(n);
    int len = strlen(fibword);
    int i, pos;

    /* setting image to all white */
    for (i = 0; i < w*h; i++)
        image[i] = bc;

    direction prev = up;
    i = 0;
    while(fibword[i]){
        pos = i + 1;
        draw(x, y, prev, step, w, image, fc);

        if(prev == up)
            x += step;
        else if(prev == down)
            x -= step;
        else if(prev == left)
            y += step;
        else if(prev == right)
            y -= step;

        if ((x < 0 || y < 0) || (x >= h || y >= w))
            return 0;

        if(fibword[i] == zero){

            if( (pos % 2) == 0){
                if (prev == up)
                    prev = left;
				else if (prev == down)
                    prev = right;
				else if (prev == left)
                    prev = down;
				else
                    prev = up;
            }
            else{
                if (prev == up)
                    prev = right;
				else if (prev == down)
                    prev = left;
				else if (prev == left)
                    prev = up;
				else
                    prev = down;
            }
        }
        i++;
    }
    free(fibword);
    return len;
}

char* fibCombo(int n){

    char* f2 = (char*) malloc(N*sizeof(char) );
    char* f1 = (char*) malloc(N*sizeof(char) );
    char* next = (char*) malloc(N*sizeof(char) );

    int i;
    /* producing fibonacci combination */
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
    free(f2);
    free(f1);
    return next;
}


