#include <stdio.h> 

int main(){ 

    unsigned int x, y;
    printf("Enter two positive integers: ");
    scanf("%u%u", &x, &y);
    
    printf("Common factors of (%u, %u): ", x, y);
    

    unsigned int finalval;
    unsigned int sum = 0;
    unsigned int gcf;
    unsigned int lcm = 0;   
    
    
    if (x < y) finalval = x;
    else finalval = y;

    /*finds all common factors*/
    int i;
    for(i = 1; i <= finalval; i++){
        if (x % i == 0 && y % i == 0)
        {
        printf("%u ", i); 
        sum += i;
        gcf = i;
        }
    }

    if (x == 0 || y == 0) /*preventing zero division error*/
    { 
    gcf = 0; 
    lcm = 0; 
    }
    else lcm = x*y / gcf;

    sum = sum + lcm + gcf;
    printf("\nGCF: %u", gcf);
    printf("\nLCM: %u", lcm);
    printf("\nsum: %u\n", sum);

    return 0;
}