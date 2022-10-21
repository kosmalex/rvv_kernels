# void
# saxpy(size_t n, const float a, const float *x, float *y)
# {
#   size_t i;
#   for (i=0; i<n; i++)
#     y[i] = a * x[i] + y[i];
# }

.text
.align 4
.global saxpy

saxpy:
    vsetvli t0, a0, e32, m1, ta, ma
        sub a0, a0, t0
    vle32.v v0, (a1)
        slli t0, t0, 2
        add a1, a1, t0
    vfmul.vf v0, v0, fa0
    vle32.v v1, (a2)
    vfadd.vv v0, v0, v1
    vse32.v v0, (a2)
        add a2, a2, t0
        bnez a0, saxpy
ret