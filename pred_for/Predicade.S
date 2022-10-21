# Code using one width for predicate and different width for masked
# compute.
#   int8_t a[]; int32_t b[], c[];
#   for (i=0;  i<n; i++) { b[i] =  (a[i] < 5) ? c[i] : 1; }

.text
.balign 4
.global pred_for

pred_for:
    vsetvli t0, a0, e8, m1, ta, ma
    vle8.v v1, (a1)
        add a1, a1, t0
    vmslt.vi v0, v1, 5

    vsetvli t0, a0, e32, m4, ta, ma
        sub a0, a0, t0
    vmv.v.i v4, 1
    vle32.v v4, (a3), v0.t # c[i]
        slli t1, t0, 2
        add a3, a3, t1
    vse32.v v4, (a2)
        add a2, a2, t1
        bnez a0, pred_for
ret