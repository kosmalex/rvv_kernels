.text
.balign 4
.global sLoop

sLoop:
    vsetvli a4, a0, e32, m1, ta, ma
    vle32.v v1, (a1)
    sub a0, a0, a4
    slli a4, a4, 2
    add a1, a1, a4
    vle32.v v2, (a2)
    add a2, a2, a4
    vadd.vv v3, v1, v2
    vse32.v v3, (a3)
    add a3, a3, a4
    bnez a0, sLoop
end:
    ret