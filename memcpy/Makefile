memcpy.elf: memcpy.c memcpy.S
	riscv32-unknown-elf-as --march=rv32gv memcpy.S -o memcpy_as.elf
	riscv32-unknown-elf-gcc -march=rv32gv memcpy.c memcpy_as.elf -o memcpy.elf
	riscv32-unknown-elf-objdump -D memcpy.elf > memcpy.dmp

sim:
	spike $(shell which pk) memcpy.elf

simd:
	spike -d $(shell which pk) memcpy.elf

clean:
	rm *.elf *.dmp
