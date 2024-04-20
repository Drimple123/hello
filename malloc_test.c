#include <stdio.h>
#include "malloc.h"
#include "rocc.h"
//#include "sys/mman.h"

int main(void)
{   
    //申请了一块shadow memory
    char *p0;
    p0 = NULL;
    p0 = (char *)shadow_malloc(134217744);//128M+16个字节
    if(p0 == NULL){
        printf("没成功\n");
    }
    else{
        printf("%x\n",p0);
    }
    ROCC_INSTRUCTION_S(0, p0, 6);
    
    

    int *p1;
    p1 = NULL;
    p1 = (int *)malloc(sizeof(int));
    // char *p2;
    // p2 = NULL;
    // p2 = (char *)malloc(6);
    // char *p3;
    // p3 = NULL;
    // p3 = (char *)malloc(7);
    printf("%x\n",p1);

    *p1 = 233;
    *p1 += 3;

    // printf("%x\n",p2);
    // printf("%x\n",p3);
    free(p1);
    p1 = NULL;
    // free(p2);
    // p2 = NULL;
    // free(p3);
    // p3 = NULL;

    // p1 = (char *)malloc(8);
    // p2 = (char *)malloc(8);
    // p3 = (char *)malloc(8);
    // printf("%x\n",p1);
    // printf("%x\n",p2);
    // printf("%x\n",p3);
    // free(p1);
    // p1 = NULL;
    // free(p2);
    // p2 = NULL;
    // free(p3);
    // p3 = NULL;

    //把shadow memory free掉
    shadow_free(p0);
    p0 = NULL;
    return 0;
}