#include <stdio.h> 

int main(){

    unsigned int n; /*num of staircases [1, 100]*/
    unsigned int m; /*num of stairs [1, 9]*/
    unsigned int p; /*num of staircases per row [1, 100]*/

    printf("Enter number of staircases: ");
    scanf("%u", &n);
    printf("Enter number of stairs: ");
    scanf("%u", &m);
    printf("Enter number of staircases per row: ");
    scanf("%u", &p);

    if (n > 100){
        printf("n=%u", n);
        printf( ", must be in [1, 100]\n");
        return 1;
    }     
    if (m > 9){
        printf("n=%u", m);
        printf( ", must be in [1, 9]\n");
        return 1;
    }  
    if (p > 100){
        printf("n=%u", p);
        printf( ", must be in [1, 100]\n");
        return 1;
    }  

    unsigned int cycles = n / p; 
    unsigned int numws;
    int i, j, k, z;
    for(j = 1; j <= cycles; j++) /*repeating rows */
    {
        for (k = 1; k <= m; k++) /*going thru num of columns*/
        {
            numws = m - k; /*for whitespaces */
            for ( i = 1; i <= p; i++) /*going thru num of rows*/
            {
            printf( "%*s ", numws, ""); 

            for (z = 1; z <= k; z++) 
                printf("%u", m);
                
            if (i==p) printf("\n");
            }   
        }  
    }
    
    /*for the remainder of staircases left*/
    unsigned int rem = n % p; 
    for (k = 1; k <= m; k++) /*going thru num of columns*/
    {
            numws = m - k;
            for (i = 1; i <= rem; i++) /*going thru num of rows*/
            {
            printf( "%*s ", numws, ""); 
            for (z = 1; z <= k; z++) printf("%u", m);
            if (i==rem) printf("\n");
            }   
    } 
    
    return 0;
}