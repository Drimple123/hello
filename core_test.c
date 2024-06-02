#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <math.h>
#include "rocc.h"
#include "encoding.h"

// 定义测试次数
#define NUM_ITERATIONS 1000


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
// 计时器函数
// double get_time() {
//     struct timespec ts;
//     clock_gettime(CLOCK_MONOTONIC, &ts);
//     return ts.tv_sec + ts.tv_nsec * 1e-9;
// }

// 整数运算测试
void integer_test() {
    volatile int a = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        a += i;
        a *= 2;
        a -= i;
        a /= 2;
    }
    printf("Integer test result: %d\n", a);
}

// 浮点运算测试
void float_test() {
    volatile double a = 0.0;
    for (int i = 0; i < NUM_ITERATIONS/4; i++) {
        a += sqrt((double)i);
        a *= 2.0;
        a -= sqrt((double)i);
        a /= 2.0;
        // if (i % (NUM_ITERATIONS / 10) == 0) {  // 每10%的进度打印一次
        //     printf("a: %lf\n", a);
        //     fflush(stdout);  // 刷新输出缓冲区
        // }
    }
    printf("Float test result: %lf\n", a);
}

// 内存访问测试
void memory_test() {
    volatile  *array = (int *)malloc(NUM_ITERATIONS * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        array[i] = i;
    }
    volatile long sum = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sum += array[i];
    }
    printf("Memory test result: %ld\n", sum);
    free(array);
}

int main() {


    int cycle_start;
    int cycle_end;
    
    unsigned long data;
    //表1初始值清0
    for(int i=0;i<128;i++){
        write_table1(i, 0);
    }

    //写第一张表 hammer asan counter ss 
    //jal和jalr，shadow stack要
    // write_table1(0b1101111, 1);
    // write_table1(0b1100111, 1);
    //load和store， asan和hammer要
    // write_table1(0b0100011, 12);
    // write_table1(0b0000011, 12);
    // write_table1(0b0100011, 4);
    // write_table1(0b0000011, 4);
    //write_table1(0b0100011, 8);
    //write_table1(0b0000011, 8);

    //算术和逻辑指令，custom counter要
    //write_table1(0b0010011, 2);
    //custom counter要个访存指令看看效果
    write_table1(0b0100011, 2);
    write_table1(0b0000011, 2);


    //写第二张表 0 ss 1 counter 2 asan 3 hammer
    write_table2(0, 10); //ss wdata and npc
    write_table2(1, 0); //couonter 两个都不要
    write_table2(2, 4);//asan要mdata
    write_table2(3, 1);//hammer要req_addr
    char *p0;
    p0 = NULL;
    p0 = (char *)shadow_malloc(134217744);
    start();
    //double start_time, end_time;

    // 整数运算测试
    cycle_start = read_csr(0xb00);
    integer_test();
    cycle_end = read_csr(0xb00);
    //end_time = get_time();
    printf("Integer test cycle: %d cycles\n", cycle_end - cycle_start);

    // 浮点运算测试
    //start_time = get_time();
    // cycle_start = read_csr(0xb00);
    // float_test();
    // //end_time = get_time();
    // cycle_end = read_csr(0xb00);
    // printf("Float test cycle: %d cycles\n", cycle_end - cycle_start);

    // 内存访问测试
    //start_time = get_time();
    cycle_start = read_csr(0xb00);
    memory_test();
    //end_time = get_time();
    cycle_end = read_csr(0xb00);
    printf("Memory test cycle: %d cycles\n", cycle_end - cycle_start);

    shadow_free(p0);
    p0 = NULL;
    return 0;
}

int __main(){
    while(1){}
    return 0;
}
