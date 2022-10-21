cvm.elf: cvm.c cvm_as.S
	riscv32-unknown-elf-as --march=rv32gv cvm_as.S -o cvm_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv cvm.c cvm_as.elf -o cvm.elf
	riscv32-unknown-elf-objdump -D cvm.elf > cvm.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) cvm.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) cvm.elf

clean:
	rm *.elf *.dmp
