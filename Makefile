gcc64 = riscv64-unknown-elf-gcc
gcc32 = riscv32-unknown-elf-gcc
gcc_linux = riscv64-unknown-linux-gnu-gcc -O3 -static -DRISCV
march32 = -march=rv32imafd
march64 = -march=rv64imafd


gcd.o:gcd.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c gcd.c

gcd:gcd.o
	${gcc64}  -static -specs=htif_nano.specs gcd.o -o gcd.riscv

hello_linux:hello_linux.c
	${gcc_linux} hello_linux.c -o hello_linux.riscv
	
second_mem.o:second_mem.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c second_mem.c

second_mem.riscv:second_mem.o malloc.o
	${gcc64}  -static -specs=htif_nano.specs second_mem.o malloc.o -Wl,--allow-multiple-definition -o second_mem.riscv

rocc_chuan.o:rocc_chuan.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c rocc_chuan.c

rocc_chuan.riscv:rocc_chuan.o
	${gcc64}  -static -specs=htif_nano.specs rocc_chuan.o -o rocc_chuan.riscv

multi_hello.o:multi_hello.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c multi_hello.c

multi_hello.riscv:multi_hello.o
	${gcc64}  -static -specs=htif_nano.specs multi_hello.o -o multi_hello.riscv

gettime.o:gettime.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c gettime.c

gettime.riscv:gettime.o
	${gcc64}  -static -specs=htif_nano.specs gettime.o -o gettime.riscv

zz_new_test.o:zz_new_test.c
	${gcc64} -O3 -fno-common -fno-builtin-printf -specs=htif_nano.specs -c zz_new_test.c

zz_new_test.riscv:zz_new_test.o
	${gcc64} -O3 -static -specs=htif_nano.specs zz_new_test.o -o zz_new_test.riscv

hello.o:hello.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c hello.c

hello.riscv:hello.o
	${gcc64}  -static -specs=htif_nano.specs hello.o -o hello.riscv

malloc_test1.riscv:malloc_test1.o malloc.o
	${gcc64}  -static -specs=htif_nano.specs malloc_test1.o malloc.o -Wl,--allow-multiple-definition -o malloc_test1.riscv

malloc_test1.o:malloc_test1.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c malloc_test1.c

malloc_test.riscv:malloc_test.o malloc.o
	${gcc64}  -static -specs=htif_nano.specs malloc_test.o malloc.o -Wl,--allow-multiple-definition -o malloc_test.riscv

malloc_test.o:malloc_test.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c malloc_test.c

malloc.o:malloc.c
	${gcc64} -O3 -fno-common -fno-builtin-printf -specs=htif_nano.specs -DUSE_PUBLIC_MALLOC_WRAPPERS -c malloc.c 

zz_new_test_asan.o:zz_new_test_asan.c
	${gcc64} -O3 -fno-common -fno-builtin-printf -specs=htif_nano.specs -c zz_new_test_asan.c

zz_new_test_asan.riscv:zz_new_test_asan.o malloc.o
	${gcc64} -O3 -static -specs=htif_nano.specs zz_new_test_asan.o malloc.o -Wl,--allow-multiple-definition -o zz_new_test_asan.riscv

core_test.o:core_test.c
	${gcc64} -O3 -fno-common -fno-builtin-printf -specs=htif_nano.specs -c core_test.c

core_test:core_test.o malloc.o
	${gcc64} -O3 -static -specs=htif_nano.specs core_test.o malloc.o -Wl,--allow-multiple-definition -o core_test.riscv -lm

charcount.o:charcount.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c charcount.c

charcount:charcount.o
	${gcc64}  -static -specs=htif_nano.specs charcount.o -o charcount.riscv

asan_test.o:asan_test.c
	${gcc64} -O3 -fno-common -fno-builtin-printf -specs=htif_nano.specs -c asan_test.c

asan_test:asan_test.o malloc.o
	${gcc64} -O3 -static -specs=htif_nano.specs asan_test.o malloc.o -Wl,--allow-multiple-definition -o asan_test.riscv -Wl,-Map,output.map

clean:
	rm *.o
	rm *.riscv
