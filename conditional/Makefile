conditional.elf: conditional.c cond.S
	riscv32-unknown-elf-as --march=rv32gcv cond.S -o cond.elf
	riscv32-unknown-elf-gcc -march=rv32gcv conditional.c cond.elf -o conditional.elf
	riscv32-unknown-elf-objdump -D conditional.elf > conditional.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) conditional.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) conditional.elf

clean:
	rm *.elf *.dmp
