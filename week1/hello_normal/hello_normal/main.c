//
//  main.c
//  hello_normal
//
//  Created by Xinrui Lu on 8/24/19.
//  Copyright © 2019 AXL. All rights reserved.
//

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
