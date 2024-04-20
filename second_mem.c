#include <stdio.h>
#include "rocc.h"
//#include "malloc.h"
//#include "sys/mman.h"

int main(void)
{   
    char *p0;
    p0 = NULL;
    p0 = (char *)malloc(64);
    ROCC_INSTRUCTION_SS(0, p0, 233, 5);
    printf("%x\n",p0);
    free(p0);
    p0 = NULL;
    return 0;
}

int __main(void)
{
    while(1){}
    return 0;
}