#include <stdio.h> 

int main(){ 

    unsigned long int num;
    printf("Enter an integer: ");
    scanf("%lu", &num);
    unsigned long int rvsnum = 0;
    
    while (num != 0) /*function to calculate reverse number */
    {
        rvsnum *= 10;
        rvsnum += num % 10;
        num /= 10;
    }
    printf("%lu\n", rvsnum);
    
    return 0;
}