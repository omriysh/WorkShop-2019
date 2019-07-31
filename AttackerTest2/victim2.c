//
// Created by User on 31/7/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <time.h>

void even()
{
    volatile int i;

    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 6;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
}

void odd()
{
    volatile int i;

    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 5;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
    i = 0;
}

int main()
{
    volatile int random;

    srand(time(NULL));

    random = rand();
    if (random % 2 == 0) printf("Even\n");
    else printf("Odd\n");
    while (1)
    {
        usleep(100);//for (i = 0; i < TIME_WASTER; i++);
        if (random % 2 == 0)
        {
            even();
        }
        else
        {
            odd();
        }
    }
}