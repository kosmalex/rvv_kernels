dgemv.elf: dgemv.c dgemv_as.S
	riscv32-unknown-elf-as --march=rv32gv dgemv_as.S -o dgemv_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv dgemv.c dgemv_as.elf -o dgemv.elf
	riscv32-unknown-elf-objdump -D dgemv.elf > dgemv.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) dgemv.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) dgemv.elf

clean:
	rm *.elf *.dmp
