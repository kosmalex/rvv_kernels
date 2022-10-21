pred_for.elf: pred_for.c Predicade.S
	riscv32-unknown-elf-as --march=rv32gv Predicade.S -o Predicade.elf
	riscv32-unknown-elf-gcc -march=rv32gv pred_for.c Predicade.elf -o pred_for.elf
	riscv32-unknown-elf-objdump -D pred_for.elf > pred_for.dmp

sim:
	spike --varch=vlen:128,elen:32 $(shell which pk) pred_for.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) pred_for.elf

clean:
	rm *.elf *.dmp
