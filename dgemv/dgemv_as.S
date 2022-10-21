# for (j = 0; j < n; j++) {
#     y[i] += A[i][j] * x[j];
# }

#void *dgemv_as(int N, int M, float* mat, float* arr, float* res);

.text
.align 4
.global dgemv_as

dgemv_as:
    mv t5, a0 
    mv t3, a3
    out_loop:
            addi a1, a1, -1
        in_loop:
            vsetvli t0, t5, e32, m1, ta, ma
                sub t5, t5, t0
            vle32.v v0, (t3)   #x
            vle32.v v1, (a2)   #A_row
                slli t0, t0, 2
                add a2, a2, t0
                add t3, t3, t0
            vfmul.vv v0, v0, v1
            vfredosum.vs v2, v0, v2 #If not reset to 0, this will accumulate every partial sum
                bnez t5, in_loop
        #in_loop_end

            mv t5, a0 #restore the column number 
            mv t3, a3 #restore the address of the float *arr
        vfmv.f.s fa0, v2
        vmv.s.x v2, zero #reset to zero to prevent accumulation of partial sums
            fsw fa0, (a4)
            addi a4, a4, 4

            bnez a1, out_loop
    #out_loop_end
ret