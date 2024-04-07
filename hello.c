#include <stdio.h>
#include "malloc.h"
//#include "sys/mman.h"

int main(void)
{
    char *p;
    p = NULL;
    p = (char *)malloc(100);
    printf("Hello, Drimple!\n");
    free(p);
    p = NULL;
    return 0;
}