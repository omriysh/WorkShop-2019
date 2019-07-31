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

#define BUFFER_SIZE 100000
#define INTERVAL    100

int main()
{
    volatile int random;
    volatile int buffer[100000] = {0};

    srand(time(NULL));

    random = rand();
    while (1)
    {
        usleep(INTERVAL);
        buffer[rand() % BUFFER_SIZE]++;
    }
}