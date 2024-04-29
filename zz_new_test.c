#include <stdio.h>
#include "rocc.h"

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
{   
    unsigned long data;

    //写第一张表 hammer asan counter ss 
    //jal和jalr，shadow stack要
    write_table1(0b1101111, 1);
    write_table1(0b1100111, 1);
    //load和store， asan和hammer要
    write_table1(0b0100011, 12);
    write_table1(0b0000011, 12);

    //算术和逻辑指令，custom counter要
    write_table1(0b0010011, 2);


    //写第二张表 0 ss 1 counter 2 asan 3 hammer
    write_table2(0, 3); //ss mdata和wdata都要
    write_table2(1, 0); //couonter 两个都不要
    write_table2(2, 1);//asan要mdata
    write_table2(3, 1);//hammer要mdata
    start();
    ROCC_INSTRUCTION_S(0, 1234, 6);
    ROCC_INSTRUCTION_SS(0, 12, 34, 5);
    printf("hello\n");
    end();
    return 0;

    //read_table1(0b1101111);
    //read_table1(0b0100011);
    



    //printf("hello, Drimple");
}