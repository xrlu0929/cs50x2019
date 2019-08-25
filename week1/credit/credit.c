/**
  * credit.c
  *
  * A program for validating credit card numbers.
  *
  */
  
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Declare and initialize a variable and ask for user input.
    long long cardnumber = 0;
 
    do
    {
        cardnumber = get_long("card number: ");
    }
    while (cardnumber <= 0);
    
    // count of digits in cardnumber
    int count = 0;
    long long digits = cardnumber;
    while(digits > 0)
    {
        digits = digits/10;
        count++;
    }
    
    // parse digits to origin number
    long long digit_parse = cardnumber;
    // in correct orgin (same as card number)
    int origin[count];
    for(int i = count - 1; i >=0; i--)
    {
        origin[i] = digit_parse % 10;
        digit_parse = digit_parse / 10;
    }
    
    // verify count (digits of credit card number)
    if(count != 13 && count != 15 && count != 16){
//         printf("count %i", count);
        printf("INVALID\n");
        return 0;
    }
    
    // general verification 
    // under line digits
    int sum_underline = 0;
    // sum left
    int sum_leftout = 0;
    for(int i = count -2; i >= -1; i = i -2)
    {
        if(i >= 0) {
//             printf("index %i \n", i);
            int temp = origin[i] * 2;
//             printf("temp %i \n", temp);
            int temp_sum = 0;
            // verify temp into digit;
            while(temp > 0){
                temp_sum = temp_sum + temp % 10;
                temp = temp/10;
            }
//             printf("temp sum %i \n", temp_sum);
            sum_underline = temp_sum + sum_underline;
        }
       
        sum_leftout = sum_leftout + origin[i + 1];
    }
//     printf("sum_underline %i \n", sum_underline);
//     printf("sum_leftout %i \n", sum_leftout);
    bool valid = false;
    if( (sum_underline + sum_leftout)%10 == 0 ){
        valid = true;
    } else {
//         printf("calculation\n");
        printf("INVALID\n");
        return 0;
    }
    
    // find which company
    int firstTwo = 0;
    firstTwo = origin[0] * 10 + origin[1];
    // American Express
    if(count == 15 && (firstTwo == 34 || firstTwo == 37)) {
        printf("AMEX\n");
        return 0;
    } 
    
    // visa
    if( (count == 13 || count == 16) && origin[0] == 4) {
        printf("VISA\n");
        return 0;
    } 
    
    // MasterCard
    if(count == 16){
        printf("MASTERCARD\n");
        return 0;
    }
    
    printf("INVALID\n");
    return 0;
}  
