imax.elf: imax.c imax_as.S
	riscv32-unknown-elf-as --march=rv32gv imax_as.S -o imax_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv imax.c imax_as.elf -o imax.elf
	riscv32-unknown-elf-objdump -D imax.elf > imax.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) imax.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) imax.elf

clean:
	rm *.elf *.dmp
