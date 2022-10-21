#void *spma_as(int AVL, float *data, int *idx, float *dataC, int* idx, int* l);

.text
.align 4
.global spma_as

spma_as:
    addi sp, sp, -4
    sw ra, (sp)
    call save_to_stack          #Save s0-s11 for later use, clearly not the best approach
    lw t1, (a5)                 #l
    
    Loop:
        vsetvli t0, a0, e32, ta, ma
            sub a0, a0, t0
            add t1, t1, t0
        vle32.v v0, (a1)
        vle32.v v1, (a2)
            slli t0, t0, 2
            add a1, a1, t0
            add a2, a2, t0
        vse32.v v0, (a3)
        vse32.v v1, (a4)
            add a1, a1, t0
            add a2, a2, t0
            bnez a0, Loop
    #Loop_end

    sw t1, (a5)
    call load_from_stack        #Load s0-s11
    lw ra, (sp)
    addi sp, sp, 4
ret

save_to_stack:
    addi sp, sp, -48
    sw s0, 44(sp)
    sw s1, 40(sp)
    sw s2, 36(sp)
    sw s3, 32(sp)
    sw s4, 28(sp)
    sw s5, 24(sp)
    sw s6, 20(sp)
    sw s7, 16(sp)
    sw s8, 12(sp)
    sw s9, 8(sp)
    sw s10, 4(sp)
    sw s11, 0(sp)
ret

load_from_stack:
    lw s0,  44(sp)
    lw s1,  40(sp)
    lw s2,  36(sp)
    lw s3,  32(sp)
    lw s4,  28(sp)
    lw s5,  24(sp)
    lw s6,  20(sp)
    lw s7,  16(sp)
    lw s8,  12(sp)
    lw s9,  8(sp)
    lw s10, 4(sp)
    lw s11, 0(sp)
    addi sp, sp, 48
ret
