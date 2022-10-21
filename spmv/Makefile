spmv.elf: spmv.cc spmv_as.S
	riscv32-unknown-elf-as --march=rv32gv spmv_as.S -o spmv_as.o
	riscv32-unknown-elf-g++ -march=rv32gv spmv.cc spmv_as.o -I ../utils -o spmv.elf
	@#riscv32-unknown-elf-objdump -D spmv.elf > spmv.dmp

comp_cpp:
	gcc spmv.cc -I ../utils/ -o spmv_c.elf

sim:
	spike --varch=vlen:128,elen:32 --dc=16:2:32 --log-cache-miss $(shell which pk) spmv.elf

simd:
	spike --varch=vlen:128,elen:32 -d $(shell which pk) spmv.elf

clean:
	rm *.elf *.dmp
