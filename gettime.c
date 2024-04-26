//#define _GNU_SOURCE 
#define __riscv 1
#include <stdio.h>
#include "encoding.h"
//#include <time.h>
//struct timespec start, end;

int main(void)
{   
    //clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    //printf("start: %lu\n", start.tv_nsec);

    int cycle;
    
    printf("hello Drimple\n");
    cycle = read_csr(0xb00);
    printf("cycle: %d\n", cycle);
    cycle = read_csr(0xb00);
    printf("cycle: %d\n", cycle);


    //clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    //printf("end: %lu\n", end.tv_nsec);
    return 0;
}
int __main(void)
{
    while(1){}
    return 0;
}