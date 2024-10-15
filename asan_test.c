#include <stdio.h>
#include "rocc.h"
#include "encoding.h"

static inline void write_table1(int addr, int data)
{
	//asm volatile ("fence");
	ROCC_INSTRUCTION_SS(0, addr, data, 1);
}
static inline void write_table2(int addr, int data)
{
	//asm volatile ("fence");
	ROCC_INSTRUCTION_SS(0, addr, data, 2);
}

static inline void start()
{
	//asm volatile ("fence");
	ROCC_INSTRUCTION(0,4);
}
static inline void end()
{
	//asm volatile ("fence");
	ROCC_INSTRUCTION(0,8);
}
// static inline void read_table1(unsigned long addr)
// {   
//     unsigned long data;
// 	//asm volatile ("fence");
// 	ROCC_INSTRUCTION_DSS(0, data, addr, 0, 4);
//     //printf("%ld",data);
// }
// static inline void read_table2(unsigned long addr)
// {   
//     unsigned long data;
// 	//asm volatile ("fence");
// 	ROCC_INSTRUCTION_DSS(0, data, addr, 0, 8);
//     //printf("%ld",data);
// }
static inline unsigned long returnval()
{
	unsigned long count;
	asm volatile ("fence");
	ROCC_INSTRUCTION_D(0,count,0);
	return count;
}
int main()
{   int cycle_start;
    int cycle_end;
    
    unsigned long data;
    //表1初始值清0
    for(int i=0;i<128;i++){
        write_table1(i, 0);
    }

    //写第一张表 hammer asan counter ss 
    //jal和jalr，shadow stack要
   // write_table1(0b1101111, 1);
    //write_table1(0b1100111, 1);
    //load和store， asan和hammer要
    // write_table1(0b0100011, 12);
    // write_table1(0b0000011, 12);
    write_table1(0b0100011, 4);
    write_table1(0b0000011, 4);

    //算术和逻辑指令，custom counter要
   // write_table1(0b0010011, 2);


    //写第二张表 0 ss 1 counter 2 asan 3 hammer
    write_table2(0, 10); //ss wdata and npc
    write_table2(1, 0); //couonter 两个都不要
    write_table2(2, 4);//asan要mdata
    write_table2(3, 1);//hammer要req_addr
    start();
    //cycle_start = read_csr(0xb00);

    //asan的测试
    //申请了一块shadow memory
    // char *p0;
    // p0 = NULL;
    // p0 = (char *)shadow_malloc(134217744);//128M+16个字节
    // if(p0 == NULL){
    //     printf("没成功\n");
    // }
    // else{
    //     printf("%x\n",p0);
    // }
    //ROCC_INSTRUCTION_S(0, p0, 6);

    int *p1;
    p1 = NULL;
    p1 = (int *)malloc(sizeof(int)*16);//sizeof(int)=4
    printf("%x\n",p1);
    for(int i=0; i<16; i++){
        *(p1 + i) = i;
    }
    for(int i=1; i<=5; i++){
        printf("%d ", *(p1 + i));
    }

    // for(int i=8; i<=12; i++){
    //     printf("%d ", *(p1 + i));
    // }
    // printf("\n");
    // for(int i=0; i<16; i++){
    //     *(p1 + i) = i + 1;
    // }
    // for(int i=1; i<=5; i++){
    //     printf("%d ", *(p1 + i));
    // }

    // for(int i=8; i<=12; i++){
    //     printf("%d ", *(p1 + i));
    // }
    // printf("\n");
    //  for(int i=0; i<16; i++){
    //     *(p1 + i) = i + 2;
    // }
    
    // for(int i=0; i<8; i++){
    //     *(p1 + i) = i + 1;
    // }
    // for(int i=0; i<8; i++){
    //     *(p1 + i) = i + 2;
    // }
    // for(int i=0; i<8; i++){
    //     *(p1 + i) = i + 3;
    // }

    // for(int i=1; i<=5; i++){
    //     printf("%d ", *(p1 + i));
    // }

    // for(int i=8; i<=12; i++){
    //     printf("%d ", *(p1 + i));
    // }
    // printf("\n");
    
    //usleep(100);
    free(p1);
    p1 = NULL;
    //cycle_end = read_csr(0xb00);
    //把shadow memory free掉
    // shadow_free(p0);
    // p0 = NULL;

    //printf("hello\n");
    end();
    // cycle_end = read_csr(0xb00);
    // printf("cycle_start: %d cycle_end: %d  cycle: %d\n", cycle_start, cycle_end, (cycle_end - cycle_start));
    return 0;

    //read_table1(0b1101111);
    //read_table1(0b0100011);
    



    //printf("hello, Drimple");
}

int __main(void)
{
    while(1){}
    //volatile int a[100];
    // int a[100];
    // for(int i=0;i<100;i++){
    //     a[i] = i;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 1;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 2;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] = i;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 1;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 2;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] = i;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 1;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 2;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] = i;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 1;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 2;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] = i;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 1;
    // }
    // for(int i=0;i<100;i++){
    //     a[i] += 2;
    // }
    return 0;
}