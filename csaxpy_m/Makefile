csaxpy.dmp: csaxpy
	riscv32-unknown-elf-objdump -d csaxpy > csaxpy.dmp	
	subl csaxpy.dmp 

csaxpy: main_csaxpy.c csaxpy.o
	riscv32-unknown-elf-gcc -Wall main_csaxpy.c csaxpy.o -o csaxpy.elf
	#spike --isa=rv32gcv pk csaxpy

csaxpy.o: csaxpy.s
	riscv32-unknown-elf-as --march=rv32gv csaxpy.s -o csaxpy.o

clean: 
	rm *.o csaxpy csaxpy.dmp
