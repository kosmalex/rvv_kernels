	.text
	.balign 4
	.global csaxpy

csaxpy:
	
	# a0 holds N, a1 holds *mask, a2 holds *x, a3 holds *y, a4 holds scalar a
	# y += a*x

	vsetvli t0, a0,  e16, m2, ta, ma    	# eew16, m2 

	vle16.v   v8, (a1) 			# load mask
	vmsne.vi  v0,  v8, 0 		# we pass mask array to a vector mask

	vsetvli x0, x0, e32, m8, ta, ma 	# eew32, m8, we just change those two

	vle32.v v8,  (a2) 			# load x
	vle32.v v16, (a3)			# load y

	vmacc.vx v16, a4, v8, v0.t		# y += a*x
	
	vse32.v v16, (a3) 			# save y

	sub a0, a0, t0 				# AVL' = AVL - VL
	add a1, a1, t0 				# adjust new address for mask, ee8
	
	slli t0, t0, 2 				# adjust pointer, *4
	add a2, a2, t0 				# adjust new address for x, ee32
	add a3, a3, t0 				# adjust new address for y, ee32

	bnez a0, csaxpy
	ret

