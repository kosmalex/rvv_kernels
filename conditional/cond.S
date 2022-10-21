# (int16) z[i] = ((int8) x[i] < 5) ? (int16) a[i] : (int16) b[i];
#void *conditional(int N, int *a, int *b, int *x, int *z);

.text
.align 4
.global conditional

conditional:
    vsetvli a5, a0, e8, m1, ta, ma
    vle8.v v1, (a3)
        add a3, a3, a5
    vmslt.vi v0, v1, 5

    vsetvli a5, a0, e16, m2, ta, ma
    vle16.v v2, (a2)
        sub a0, a0, a5
        slli a5, a5, 1
        add a2, a2, a5 
    vle16.v v4, (a1)
        add a1, a1, a5
    vmerge.vvm v6, v2, v4, v0
    vse16.v v6, (a4)
        add a4, a4, a5
        bnez a0, conditional
ret