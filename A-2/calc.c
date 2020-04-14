#include <stdio.h>
#include <string.h>
#define N 80



void add( const char a[], const char b[], char res[] ){
    
    int big;
    int shifta = 0, shiftb = 0;
    int l1 = strlen (a), l2 = strlen (b);

    /*figuring out which number is larger,
     how many digits to shift over the small number*/
    if(l1 < l2){
        big = l2; 
        shifta = l2 - l1;
    } 
    else {
        big = l1;
        shiftb = l1 - l2;
    }

    int dig; 
    int asciidig;
    int temp;
    int i;
    for(i = big - 1; i >= 0; i--){

        /*checking if one of the digits from A and B is blank */
        if ((big == l2) && ((l2 - i) > l1)) 
            dig = (int) b[i] + temp - 48;
        else if ((big == l1) && ((l1 - i) > l2)) 
            dig = (int) a[i] + temp - 48;
        else 
            dig = (int) b[i-shiftb] + (int) a[i-shifta]  + temp - 96;

        /*checking if carry-over digit is needed*/
        if ( dig >= 10 ){
            dig = dig - 10;
            temp = 1;
        } 
        else temp = 0;

        asciidig = dig + 48; /*converting to ascii*/       
        res[i+1] = (char) asciidig; 
        
        
    }
    if (temp == 1) res[0] = '1';
    else res[0] = ' ';

}

void sub(const char a[], const char b[], char res []){
    
    int big;
    
    int shifta = 0, shiftb = 0, sign = 0;
    int l1 = strlen(a), l2 = strlen(b);
    
    /*figuring out which number is larger,
     how many digits to shift over the small number,
     and if sign is negative */
    if(l2 > l1){
        big = l2; 
        shifta = l2 - l1;
        sign = 1;
    } 
    else if (l1 == l2) {
        int j;
        for(j = 0; j < l2; j++){
            if (b[j] > a[j]) 
                sign = 1;
        }
        if(sign == 1) big = l2;
        else big = l1;
    }
    else {
        big = l1;
        shiftb = l1 - l2;
        sign = 0;
    }
 

    int dig;
    int asciidig;
    int temp;
    int i;
    for(i = big - 1; i >= 0; i--){

        if (sign == 1) /*if negative, should subtract by b - a*/
        {
              /*checking if one of the digits from A is blank */
            if ((l2 - i) > l1){
                dig = (int) b[i] - temp - 48;
                
            }
            else
                dig = ( (int) b[i-shiftb] ) - ( (int) a[i-shifta] ) - temp;
        }
        else 
        {
            /*checking if one of the digits from B is blank */
            if ((l1 - i) > l2){
                dig = (int) a[i] - temp - 48;
                
            }
            else 
                dig = (int) a[i-shifta] - (int) b[i-shiftb] - temp;
        }

        /*checking if carry-over digit is needed*/
        if ( dig < 0 ){
            dig = dig + 10;
            temp = 1;
        } 
        else temp = 0;

        asciidig = dig + 48; /*converting to ascii*/
        res[i+1] = (char) asciidig;
        
    }
    /*for negative */
    if (sign == 1) res[0] = '-';
    else res[0] = ' ';

    if (strlen(res) == 0) res[0] = '0'; 
    
}


int main (){
char a[N], b[N], res[N + 1];

    char op;
    printf("Enter nums:\n ");
    scanf ("%s %s %c", a, b, &op);
    switch (op) {
    case '+':

        add(a, b, res);
        break;
    case '-':
        sub(a, b, res);
    }   
    
    char buf [20];
    int l1 = strlen (a), l2 = strlen (b), l3 = strlen (res);
    int m = l1 > l2 ? l1 : l2;
    m = m > l3 ? m : l3;
    sprintf (buf , "%% %ds\n%% %ds\n%% %ds\n", m, m, m);
    printf (buf , a, b, res );
    return 0;
} 
