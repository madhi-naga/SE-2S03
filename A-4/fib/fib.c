#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    up,
    down,
    left,
    right
} direction;

char *fibcombo(int n); 
void draw(int x, int y, direction dir, int step, int w, RGB* im, RGB c);
int fib(int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB* image);

char *fibcombo(int n) 
{

    char *last = malloc(2);
	if (!last)
        return NULL;
	strcpy(last, "1");
 
	char *cur = malloc(2);
	if (!cur) 
        return NULL;
	strcpy(cur, "0");

	int i;
	for (i = 2; i < n; i++) {
 
		char *next = malloc(strlen(last) + strlen(cur) + 1);
		if (!next) 
            return NULL;

		strcpy(next, cur);
		strcat(next, last);
 
		free(last);
        
		last = cur;
		cur = next;
	}

	free(last);
	return cur;
} 

/* referenced from main_line2.c on avenue */
void draw(int x, int y, direction dir, int step, int w, RGB* im, RGB c) {
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

	char *fibword = fibcombo(n);

	int len = strlen(fibword);
    int i;
	for (i = 0; i < w*h; i++)
		image[i] = bc;

	direction prev = up;
    int pos = 0;
    int j = 0;
	while(fibword[j] != '\0') {
        pos = j + 1;
		draw(x, y, prev, step, w, image, fc);

		if (prev == up) 
            x += step;
		else if (prev == down) 
            x -= step;
		else if (prev == right) 
            y += step;
		else 
            y -= step;

		if ( (x < 0 || y < 0 ) || (x >= h || y >= w) )
            return 0;

		if (fibword[j] == '0') {
			if ( (pos % 2) == 0) {
				if (prev == up) 
                    prev = left;
				else if (prev == down) 
                    prev = right;
				else if (prev == left) 
                    prev = down;
				else 
                    prev = up;
			}
			else {
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
        j++;
	}
    
	free(fibword);
	return len;
}