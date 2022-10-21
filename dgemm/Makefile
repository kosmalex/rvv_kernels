dgemm.elf: dgemm.c dgemm_as.S
	riscv32-unknown-elf-as --march=rv32gv dgemm_as.S -o dgemm_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv dgemm.c dgemm_as.elf -o dgemm.elf
	riscv32-unknown-elf-objdump -D dgemm.elf > dgemm.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) dgemm.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) dgemm.elf

clean:
	rm *.elf *.dmp
