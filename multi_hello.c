#include <stdio.h>
#include "spin_lock.h"
//#include "malloc.h"
//#include "sys/mman.h"
int uart_lock;

int main(void)
{   
    int hartid;
    //用内联汇编读取hartid
    asm volatile ("csrr %0, mhartid":"=r"(hartid));
    lock_acquire(&uart_lock);
    printf("hello Drimple from %d\n",hartid);
    lock_release(&uart_lock);
    printf("\n");
    return 0;
}
int __main(void)
{   
    int hartid;
    // lock_acquire(&uart_lock);
    // printf("hello Drimple\n");
    // lock_release(&uart_lock);
    //用内联汇编读取hartid
    asm volatile ("csrr %0, mhartid":"=r"(hartid));
    
    lock_acquire(&uart_lock);
    printf("hello Drimple from %d\n",hartid);
    lock_release(&uart_lock);
    
    return 0;
}

