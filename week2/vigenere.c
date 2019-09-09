#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
string cipher(int *keys, int size);
string shift(string plainTxt, int *keys, int length, int i, int min, int max, int pos);

int main(int argc, string argv[])
{
    //check if it has a string key
    if (argc == 2)
    {
        // check if it's alphabetic
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("%s\n", "Usage: ./vigenere keyword");
                return 1;
            }
        }
        // all alphabet
        string key = argv[1];
        int keys[strlen(key)];
        for (int i = 0; i < strlen(key); i++)
        {
            if (isupper(key[i]))
            {
                keys[i] = (int) (key[i] - 'A');
            }
            else
            {
                keys[i] = (int) (key[i] - 'a');
            }
            printf("%d ", keys[i]);
        }
        printf("\n ");
        cipher(keys, strlen(key));
        
    }
    else
    {
        printf("%s\n", "Usage: ./vigenere keyword");
        return 1;
    }

}
string cipher(int *keys, int size)
{
    string plainTxt = get_string("enter plain text: \n");
    int pos = 0;
    for (int i = 0; i < strlen(plainTxt);i++)
    {
        
        if (isalnum(plainTxt[i]))
        {
            if (isupper(plainTxt[i]))
            {
                printf("pos: %d", pos);
                shift(plainTxt, keys, size, i, (int)'A', (int)'Z', pos);
            }
            else
            {
                printf("pos: %d", pos);
                shift(plainTxt, keys, size, i, (int)'a', (int)'z', pos);
            }
        } 
        else
        {
            pos++;
            printf("pos: %d", pos);
        }
        
    }
    printf("ciphertext: %s\n", plainTxt);
    return plainTxt;
}

string shift(string plainTxt, int* keys, int size, int i, int min, int max, int pos)
{
    int shift = pos;
    int length = size;
    int count = 0;
    printf("shift: %d ", shift);
    printf("length: %d ", length);
    printf("key origin: %d ", i);
    printf("key position: %d ", i % length);
    printf("key: %d \n",keys[i % length] );
    while (count < keys[(i - pos) % length])
    {
        if (plainTxt[i] < max)
        {
            plainTxt[i]++;
        }
        else
        {
            plainTxt[i] = min;
        }
        count++;
    }
    
    return plainTxt;
}
