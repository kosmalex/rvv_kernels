# int idx = 0;
# float max = -INFINITY;
# for (int i = 0; i < SIZE; i++) {
#     if (x[i] > max) {
#         max = x[i];
#         idx = i;
#     }
# }

#void *imax_as(int N, float* array, int* idx, float* val);

.text
.align 4
.global imax_as

imax_as:
        lui t2, 0xFF800
        fmv.w.x fa0, t2 #max = -INFINITY
        li t2, 0 #idx = 0
        li t1, 0 #to be used as rd for fp compare
        li t4, 0 #keeps count of the #(previous elements)
    Loop:
        vsetvli t0, a0, e32, m1, ta, ma
            sub a0, a0, t0
        vle32.v v0, (a1)
        vfredmax.vs v1, v0, v0
        vfmv.f.s fa1, v1
            fle.s t1, fa1, fa0 #We strictly need the first occurance of the max, that's why fle(<=) instead of flt(<)
            bnez t1, skip 
        fmv.s fa0, fa1
        vmfeq.vf v2, v0, fa0
        vfirst.m t2, v2
            add t2, t2, t4 
        skip:
            add t4, t4, t0
            slli t0, t0, 2
            add a1, a1, t0
            bnez a0, Loop
    #Loop_end
    sw t2, (a2)
    fsw fa0, (a3)
ret
