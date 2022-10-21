# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<VLEN=128 bits, ELEN=32 bits>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#for (int j=ptr[i]; j<ptr[i+1]; j++)
#   y[i] += data[j] * x[idx[j]];

#void *spmv_as(int R, int *row_ptr, int* col_idx, float* x, float* data, float* y);

.text
.align 4
.global spmv_as

spmv_as:
    li t0, 0
    L0:
        bge t0, a0, L0_end
        lw t1, (a1)                         #row_ptr[i+1]
        lw t2, 4(a1)                        #row_ptr[i]
        addi a1, a1, 4                      #address incr
        sub t1, t2, t1                      #AVL=row_ptr[i+1]-row_ptr[i];
        L1:
            vsetvli t2, t1, e32, m4, ta, ma
                sub t1, t1, t2              #loop control
            vle32.v v0, (a2)                #col_idx
            vle32.v v4, (a4)                #row_nz_elements
                slli t2, t2, 2              # #(number of elements operated on) * 4 bytes per element
                add a2, a2, t2              #address incr  
                add a4, a4, t2              #address incr
            vsll.vi v0, v0, 2               #convert indices to byte offsets
            vluxei32.v v8, (a3), v0         #x
            vand.vi v0, v0, 0               #v0 = {128{1'b0}}
            vfmacc.vv v0, v4, v8            #v0[i] = v0[i] + (v4[i] * v8[i])
            vfredosum.vs v12, v0, v12       #v12[0] += v0[0 to MAXLEN]
                bnez t1, L1                 #loop control
        #L1_end
        vfmv.f.s fa0, v12                   #pass v12 to float register
        vand.vi v12, v12, 0                 #v12 = {128{1'b0}}
            fsw fa0, (a5)                   #store to y[i]
            addi a5, a5, 4                  #address incr
            addi t0, t0, 1                  #iterator incr
            j L0                            #loop control
    L0_end:
ret
