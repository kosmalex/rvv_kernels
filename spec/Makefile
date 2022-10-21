agnostic.elf: agnostic.c tm.S
	riscv32-unknown-elf-as --march=rv32gv tm.S -o tm.elf
	riscv32-unknown-elf-gcc -march=rv32gv agnostic.c tm.elf -o agnostic.elf
	riscv32-unknown-elf-objdump -D agnostic.elf > agnostic.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) agnostic.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) agnostic.elf

clean:
	rm *.elf *.dmp
