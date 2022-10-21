saxpy.elf: saxpy.c saxpy_as.S
	riscv32-unknown-elf-as --march=rv32gv saxpy_as.S -o saxpy_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv saxpy.c saxpy_as.elf -o saxpy.elf
	riscv32-unknown-elf-objdump -D saxpy.elf > saxpy.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) saxpy.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) saxpy.elf

clean:
	rm *.elf *.dmp
