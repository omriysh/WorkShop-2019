#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>

#define L3_SIZE 3145728

uint64_t start, end;

void NOP_write(volatile char* ch)
{
	*ch = 'z';
}

uint64_t rdtsc()
{
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

uint64_t record_access_time(volatile char* ch)
{
	start = rdtsc();
	NOP_write(ch);
	end = rdtsc();
	return end - start;
}

int flush_L3(volatile char* flusher)
{
	int i;
	for (i = 0; i < L3_SIZE; i++)
	{
		flusher[i] = 'z';
	}
}

int main()
{
	unsigned int no_flush_time = 0;
	unsigned int yes_flush_time = 0;
	unsigned int i;
	volatile char* ch, *flusher;
	long time;

	ch = (char*)malloc(sizeof(char));
	flusher = (char*)malloc(L3_SIZE*20);
	for (i = 0; i < 1000; i++)
	{
		NOP_write(ch);
		no_flush_time += record_access_time(ch);
		flush_L3(flusher);
		yes_flush_time += record_access_time(ch);
	}
	printf("Clicks before flush - %d\n", no_flush_time/1000);
	printf("Clicks after flush  - %d\n", yes_flush_time/1000);
}