# struct Complex {
#   float real;
#   float imag;
# };

# for (i = 0; i < m; i++) {
#   c[i].real = (a[i].real * b[i].real) - (a[i].imag * b[i].imag);
#   c[i].imag = (a[i].imag * b[i].real) + (a[i].real * b[i].imag);
# }

# void *cmplxmult_as(int, struct Complex*, struct Complex*, struct Complex*);

.text
.align 4
.global cmplxmult_as

cmplxmult_as:
    j cmplxmult_as_v2 #comment out, to run this version

    vsetvli t0, a0, e32, m1, ta, ma
        sub a0, a0, t0
    vlseg2e32.v v0, (a1)
    vlseg2e32.v v2, (a2)
        slli t0, t0, 3 # #elements(t0) * #(fields per element) * #(bytes per field) 
        add a1, a1, t0
        add a2, a2, t0
    vfmul.vv v4, v0, v2 # c[i].real = (a[i].real * b[i].real) - (a[i].imag * b[i].imag);
    vfmul.vv v5, v1, v3
    vfsub.vv v4, v4, v5
    vfmul.vv v6, v0, v3 # c[i].imag = (a[i].imag * b[i].real) + (a[i].real * b[i].imag);
    vfmul.vv v7, v1, v2   
    vfadd.vv v5, v6, v7
    vsseg2e32.v v4, (a3)
        add a3, a3, t0
        bnez a0, cmplxmult_as
ret

#Another variant with accumulation
cmplxmult_as_v2:
    vsetvli t0, a0, e32, m1, ta, ma
        sub a0, a0, t0
    vlseg2e32.v v0, (a1)
    vlseg2e32.v v2, (a2)
        slli t0, t0, 3 # #elements(t0) * #(fields per element) * #(bytes per field) 
        add a1, a1, t0
        add a2, a2, t0
    vfmul.vv v4, v0, v2 # (a[i].real * b[i].real)
    vfnmsac.vv v4, v1, v3 # v4 <-- -1*(a[i].imag * b[i].imag) + v4
    vfmul.vv v5, v0, v3 # (a[i].real * b[i].imag);
    vfmacc.vv v5, v1, v2 # v5 <-- (a[i].imag * b[i].real) + v5
    vsseg2e32.v v4, (a3)
        add a3, a3, t0
        bnez a0, cmplxmult_as
ret