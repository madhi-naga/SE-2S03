#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

char* makeString (char* s1 , char* s2 , char* s3);
Node* createNode (char* s, double val );
Node* binop ( Operation op , Node* a, Node* b);
double evalTree ( Node* root );
void freeTree ( Node* root );
Node* duplicateTree ( Node* root );
void printTree ( Node* root );

char* makeString (char* s1 , char* s2 , char* s3)
{
    int n = strlen(s1) + strlen(s2) + strlen(s3) + 1;
    char* catStr = (char *) malloc(n * sizeof(char));
    if (!catStr) return NULL;

    strcpy(catStr, s1);
    strcat(catStr, s2);
    strcat(catStr, s3);
    return catStr;
}

Node* createNode (char* s, double val )
{
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;
    node->expr_string = malloc( (strlen(s) + 1) * sizeof(char));
    if (!(node->expr_string)) return NULL;

    strcpy(node->expr_string, s);
    node->left = NULL;
    node->right = NULL;
    node->num_parents = 0;
    node->value = val;

    return node;
}

Node* binop (Operation op , Node* a, Node* b){

    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;

    if ( a->num_parents == 1 || b->num_parents == 1 ) return NULL;

    node->left = a;
    node->right = b;
    node->operation = op;
    node->num_parents = 0;
    node->value = 0;
    (node->left->num_parents)++;
    (node->right->num_parents)++;

    if(node->operation == 0)
        node->expr_string = makeString( node->left->expr_string, "+", node->right->expr_string );
    else if(node->operation == 1)
        node->expr_string = makeString( node->left->expr_string, "-", node->right->expr_string );
    else if(node->operation == 2)
    {
        char* leftstr = makeString("(", node->left->expr_string, ")" );
        char* rightstr = makeString("(", node->right->expr_string, ")" );
        node->expr_string = makeString( leftstr, "*", rightstr );
        free(leftstr);
        free(rightstr);
    }
    else if(node->operation == 3)
    {
        char* leftstr = makeString("(", node->left->expr_string, ")" );
        char* rightstr = makeString("(", node->right->expr_string, ")" );
        node->expr_string = makeString( leftstr, "/", rightstr );
        free(leftstr);
        free(rightstr);
    }

    return node;
}

double evalTree ( Node* root )
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return root->value;

    double a = evalTree(root->left);
    double b = evalTree(root->right);

    if(root->operation == 0)
        root->value = a + b;
    else if(root->operation == 1)
        root->value = a - b;
    else if(root->operation == 2)
        root->value = a * b;
    else if(root->operation == 3)
        root->value = a / b;

    return root->value;
}

void freeTree(Node* root)
{
    if(root->left)
        freeTree(root->left);
    if(root->right)
        freeTree(root->right);
    
    free(root->expr_string);
    free(root);
    return;
}

Node* duplicateTree(Node* root)
{
    if (!root) return NULL;
    if (!(root->left) || !(root->right))
        return createNode(root->expr_string, root->value);

    Node* duproot = binop(root->operation, duplicateTree(root->left), duplicateTree(root->right));
    return duproot;
}

void printTree(Node* root)
{
    if (!root) return;

    printf(" Node\n");
    printf("    expr_string = %s\n", root->expr_string);
    printf("    value       = %g\n", root->value);
    printf("    num_parents = %d\n", root->num_parents);
    
    printTree(root->left);
    printTree(root->right);

}



