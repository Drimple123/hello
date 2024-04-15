gcc64 = riscv64-unknown-elf-gcc
gcc32 = riscv32-unknown-elf-gcc
march32 = -march=rv32imafd
march64 = -march=rv64imafd

multi_hello.o:multi_hello.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c multi_hello.c

multi_hello.riscv:multi_hello.o
	${gcc64}  -static -specs=htif_nano.specs multi_hello.o -o multi_hello.riscv

hello.o:hello.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c hello.c

hello.riscv:hello.o
	${gcc64}  -static -specs=htif_nano.specs hello.o -o hello.riscv

malloc_test.riscv:malloc_test.o malloc.o
	${gcc64}  -static -specs=htif_nano.specs malloc_test.o malloc.o -Wl,--allow-multiple-definition -o malloc_test.riscv

malloc_test.o:malloc_test.c
	${gcc64} -fno-common -fno-builtin-printf -specs=htif_nano.specs -c malloc_test.c

malloc.o:malloc.c
	${gcc64}  -fno-common -fno-builtin-printf -specs=htif_nano.specs -DUSE_PUBLIC_MALLOC_WRAPPERS -c malloc.c 


clean:
	rm *.o
	rm *.riscv