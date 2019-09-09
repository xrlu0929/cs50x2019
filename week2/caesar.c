#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void cipher(int key);
string moveAscii(int i, int key, int min, int max, string plainTxt);

int main(int argc, string argv[])
{
    int key = 0;
    if(argc == 2) 
    {
        // printf("good with argv number\n");
        // check if it is int
        for(int i = 0; i < strlen(argv[1]); i++)
        {
            // strlen is from <string.h>
            if(!isdigit(argv[1][i]))
            {
                // isdigit is from <ctype.h>
                // if there is one non-digit character
                printf("Usage: ./caesar k\n");
                return 0;
            }
        }
        // argv is all digits
        // convertable to an int
        key = atoi(argv[1]);
        cipher(key);
    } 
    else 
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
}

//Function to get User message and decrypt it
void cipher(int key)
{
    string plainTxt = get_string("Enter your message:\n");
    string ciphTxt = "";
    for(int i = 0; i < strlen(plainTxt); i++)
    {
        // check if alphabetic or numeric
        if(isalnum(plainTxt[i]))
        {
            int min;
            int max;
            // if upper
            if(isupper(plainTxt[i]))
            {
                min = (int)'A';
                max = (int)'Z';
                moveAscii(i, key, min, max, plainTxt);
            } 
            else 
            {
                min = (int)'a';
                max = (int)'z';
                moveAscii(i, key, min, max, plainTxt);
            }
            
        }

    }
    printf("ciphertext: %s\n", plainTxt);
}

string moveAscii(int i, int key, int min, int max, string plainTxt)
{
    int key_adj = key % 26;
    int counter = 0;
    while(counter < key)
    {
        if(plainTxt[i] < max)
        {
            plainTxt[i]++;
           
        } 
        else 
        {
            // if plainTxt >= max
            // return to min
            plainTxt[i] = min; 
        }
        counter++;
    }
    
    return plainTxt;
}
