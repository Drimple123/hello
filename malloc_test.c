#include <stdio.h>
#include "malloc.h"
//#include "sys/mman.h"

int main(void)
{
    char *p1;
    p1 = NULL;
    p1 = (char *)malloc(5);
    char *p2;
    p2 = NULL;
    p2 = (char *)malloc(5);
    char *p3;
    p3 = NULL;
    p3 = (char *)malloc(5);
    printf("%x\n",p1);
    printf("%x\n",p2);
    printf("%x\n",p3);
    free(p1);
    p1 = NULL;
    free(p2);
    p2 = NULL;
    free(p3);
    p3 = NULL;
    return 0;
}