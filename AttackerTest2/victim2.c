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

// L3 size:         3145728
#define BUFFER_SIZE 2000000
#define INTERVAL    1

int main()
{
    volatile int random;
    volatile int buffer[BUFFER_SIZE] = {0};
    volatile int index;

    srand(time(NULL));

    random = rand();
    while (1)
    {
        usleep(INTERVAL);
        index = rand() % BUFFER_SIZE;
        //printf("chosen index: %d\n", index);
        buffer[index]++;
    }
}