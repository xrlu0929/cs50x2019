#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    while(!height || height < 0 || height > 8)
    {
        height = get_int("Height: ");
    }
    
    for(int i = height; i > 0; i--)
    {
        for(int j = 0; j < height; j++)
        {
            if(j < i - 1) 
            {
                printf(" ");
            } else
            {
                printf("#");
            } 
            
        }
        printf("  ");
        for(int j = 0; j < height; j++)
        {
            if(j <= height - i)
            {
                printf("#");
            } 
        }
        printf("\n");
    }
}
