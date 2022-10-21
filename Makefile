strip_mine.elf: strip_mine.c sLoop.S
	riscv32-unknown-elf-as --march=rv32gv sLoop.S -o sLoop.elf
	riscv32-unknown-elf-gcc -march=rv32gv strip_mine.c sLoop.elf -I ../utils -o strip_mine.elf
	riscv32-unknown-elf-objdump -D strip_mine.elf > strip_mine.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) strip_mine.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) strip_mine.elf

clean:
	rm *.elf *.dmp
