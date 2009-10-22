#include <mips/regdef.h>          

		.text 	
		.globl qsort
qsort:
		subu 	sp,sp,40 	#Armo stack de 40 bytes
		sw		$ra,32($sp)
		sw		$fp,28($sp)
		sw		$gp,24($sp)
		move	$fp,$sp
		sw		$a0,40($fp)

		sw		a1,32($fp) 	#guardo los parametros en el stack frame
		sw		a2,36($fp) 	
		