#include <stdio.h>

int is_same_diagonals(int n, int a[]){

    int check = 1; 
    
    /*checks current diagonal value of matrix with next diagonal value */
    int i;
    for(i = 0; i < n - 1; i++ ){
        
        if ( a[ i*(n + 1) ] != a[ (i+1)*(n + 1)] ){
            check = 0; 
        }
        
    }

    if(check == 1) return 1; /* diagonal */
    else return 0;
}

/* Test Main
int main(){
    
    int n = 4;
    int a[] = { 1, 2, 3, 4, 7, 2, 2, 3, 8, 7, 1, 2, 9, 8, 7, 1  };

    if (is_same_diagonals(n, a) == 1) printf("Diagonal\n");
    else printf("Not Diagonal\n");
    
    return 1;
}
*/
