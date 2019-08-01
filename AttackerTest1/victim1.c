//
// Created by User on 31/7/2019.
//
// This victim starts by generating a random bit. It then runs in a loop, and
// calls an Even function or an Odd function, based on the parity of the bit.
// Both functions are padded with many i=0 statements (i is volatile), but only Even
// contains an i=6 statement. The Attacker has to find out which function was called.
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