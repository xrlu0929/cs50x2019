#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    while(height <= 0 || height >= 9) {
        height = get_int("Height: ");
    }
    // printf("Stored: %i\n", height);
    for(int i = height - 1; i >= 0; i--){
        for(int j = 0; j < height; j++){
            if( j < i){
                printf(" ");
            } else {
                printf("#");
            }
 
        }
        printf("\n");
    }
    return 0;
}
