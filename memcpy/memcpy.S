#void *memcpy(void* dest, const void* src, size_t n)
# a0=dest, a1=src, a2=n

.text
.align 4
.global memcpy

memcpy:
    vsetvli a3, a2, e32, m1, ta, ma
    vle32.v v0, (a1)
    vse32.v v0, (a0)
        sub a2, a2, a3
        slli a3, a3, 2
        add a1, a1, a3
        add a0, a0, a3
        bnez a2, memcpy
ret
