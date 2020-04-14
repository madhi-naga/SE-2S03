#include <stdio.h>
#include <stdlib.h>
#include "expr.h"
#define N 4


char* makeString (char* s1 , char* s2 , char* s3);
Node* createNode (char* s, double val );
Node* binop ( Operation op , Node* a, Node* b);
double evalTree ( Node* root );
void freeTree ( Node* root );
Node* duplicateTree ( Node* root );
void printTree ( Node* root );


int main ()
{
    /*printf("%s\n", makeString("abc", "de", "fg"));*/

    Node* a[4];
    a[0] = createNode("a", .1);
    a[1] = createNode("b", .2);
    a[2] = createNode("c", .3);
    a[3] = createNode("d", .4);

    Node* t1 = binop(divop , a[0] , a[1]) ; /* a*b */
    Node* t2 = binop(addop , a[2] , t1); /* c+a*b */
    Node* t3 = binop(divop , a[3] , t2); /* d*(c+a*b) */
    Node* t4 = duplicateTree(t3); 
    Node* t5 = binop(subop , t4 , t3);
    Node* f = t5;
    
    printf(" --- Tree at t4 \n");
    
    printTree(t4);
    
    double val = evalTree(f);
    
    printf("\n--- Value at root of f %g\n", val );
    printf(" --- Evaluated Tree at f \n");
    
    printTree(f);
    freeTree(f);
    
    return 0;
}
