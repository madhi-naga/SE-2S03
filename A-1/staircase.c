#include <stdio.h> 

int main(){

    int num;

    printf("Enter number of staircases: ");
    scanf("%d", &num);
    if (num > 100){
        printf("n=%d", num);
        printf( ", must be in [1, 100]\n");
        return 1;
    }     

    int cycles = num / 5; 
    int numws;

    int i, j, k, z;
    for(j = 1; j <= cycles; j++) /*repeating rows of 5*/
    {
        for (k = 1; k <= 3; k++) /*going thru num of columns*/
        {
            numws = 3 - k; /*for whitespaces*/
            for (i = 1; i <= 5; i++) /*going thru num of rows*/
            {
            printf( "%*s ", numws, ""); 
            for (z = 1; z <= k; z++) printf("#");
            if (i==5) printf("\n");
            }   
        }  
    }

    /*for the remainder of staircases left  */
    int rem = num % 5; 
        for (k = 1; k <= 3; k++) 
        {
            numws = 3 - k; /* for whitespaces  */
            for (i = 1; i <= rem; i++) /* going thru num of rows  */
            {
            printf( "%*s ", numws, ""); 

            for (z = 1; z <= k; z++) 
                printf("#");
                
            if (i==rem) printf("\n");
            }   
        }

    
    return 0;
}
