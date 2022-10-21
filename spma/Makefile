spma.elf: spma.c spma_as.S
	riscv32-unknown-elf-as --march=rv32gv spma_as.S -o spma_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv spma.c spma_as.elf -I ../utils -o spma.elf
	riscv32-unknown-elf-objdump -D spma.elf > spma.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) spma.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) spma.elf

clean:
	rm *.elf *.dmp
