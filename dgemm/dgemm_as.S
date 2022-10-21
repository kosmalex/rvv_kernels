# void *dgemm_as(int N, float* A, float* B, float* C_as);

# for (int i = 0; i < n; i++) {
#         for (int j = 0; j < n; j++) { <- VECTORIZES THIS LOOP
#             for (int k = 0; k < n; k++) {
#                 C[i][j] += A[i][k] * B[k][j];
#             }
#         }
#     }

.text
.align 4
.global dgemm_as

dgemm_as:
    mv t0, a0
    mv t1, a0
    mv t2, a0
    L0:
        addi t0, t0, -1
        L1: #<- THE j LOOP
            vsetvli t3, t1, e32, m1, ta, ma
                sub t1, t1, t3
                slli t3, t3, 2
                mv t4, a2 
            L2:
                    addi t2, t2, -1
                vle32.v v0, (t4)    #B[k][j]
                    flw ft0, (a1)   #A[i][k]
                    add t4, t4, t3
                    add a1, a1, 4
                vfmacc.vf v1, ft0, v0
                    bnez t2, L2
            #L2_end
            vse32.v v1, (a3)
            vmv.v.i v1, 0 #reset vector to all zeros
                add a3, a3, t3
                mv t4, a2
                mv t2, a0
                bnez t1, L1
        #L1_end

        mv t1, a0
        bnez t0, L0
    #L0_end
ret
