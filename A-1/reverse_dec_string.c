#include <stdio.h> 

int main(){ 

    char x[19]; /*20-char string (0...19) */
    printf("Enter a decimal string: ");
    scanf("%s", x);

    int c = 0;  
    while(x[c] != '\0' && c < 20) 
        c++; /*checking number of empty chars*/
    int len = c - 1; 
    char x2[len]; 

    /*new array made w/o empty chars*/
    int i;
    for(i = 0; i <= len; i++)
        x2[i] = x[i];

    int lead = 0;
    int trail = 0; 
    while(x2[lead] == '0') lead++; /*num of leading zeros*/
    while(x2[len - trail] == '0') trail++; /*num of trailing zeros*/
    int stop = len - trail; 

    int check = 1; /*acts as boolean value (true = 1, false = 0)*/
    for(i = len; i >= 0; i--)
    {
        /*clearing leading and trailing zeros*/
        if(i < lead)    
            check = 0;
        if(i > stop) 
            check = 0;

        if(check == 1){
        printf("%c", x2[i]);
        
        }
        check = 1;
    }

    printf("\n");
    return 0;
}