hello.riscv:hello.o malloc.o
	riscv64-unknown-elf-gcc  -static -specs=htif_nano.specs hello.o malloc.o -Wl,--allow-multiple-definition -o hello.riscv

hello.o:hello.c
	riscv64-unknown-elf-gcc  -fno-common -fno-builtin-printf -specs=htif_nano.specs -c hello.c

malloc.o:malloc.c
	riscv64-unknown-elf-gcc  -fno-common -fno-builtin-printf -specs=htif_nano.specs -DUSE_PUBLIC_MALLOC_WRAPPERS -c malloc.c 


clean:
	rm *.o
	rm hello.riscv