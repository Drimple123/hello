#include <stdio.h>
#include "rocc.h"
//#include "malloc.h"
//#include "sys/mman.h"

int main(void)
{
    ROCC_INSTRUCTION_SS(0, 0x80000100, 233, 5);
    return 0;
}