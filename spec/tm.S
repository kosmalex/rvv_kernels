# void *test(int N, int* arr);

.text
.align 4
.global test

test:
    vsetvli a2, a0, e32, m1, ta, mu
        sub a0, a0, a2
    vle32.v v2, (a1)
        slli a2, a2, 2
    vmslt.vi v0, v2, 4
    vle32.v v1, (a1), v0.t 
        add a1, a1, a2
        bnez a0, test
ret