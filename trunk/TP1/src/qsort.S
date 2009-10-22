#include <mips/regdef.h>          

		.text 	
		.globl qsort
qsort:
		subu 	sp,sp,56 	#Armo stack de 56 bytes: 
		sw		$ra,48($sp)
		sw		$fp,44($sp)
		sw		$gp,40($sp)
		move	$fp,$sp
							#guardo los parametros en el stack frame
		sw		$a0,56($fp) #der
		sw		$a1,60($fp) #izq	
		sw		$a2,64($fp) 	
		
		lw		$t1,56($fp)	# der 	
		lw		$t2,60($fp)	# izq	
		
		slt		$t3,$t1,$t2 #der<izq seteo t0
		bne		$t3,$ZERO, while #si no se cumple esa condicion sigo y me meto en el while
		
		#aca muere el qsort
		move	$sp,$fp
		lw		$ra,48($sp)
		lw		$fp,44($sp)
		addu	$sp,$sp,56
		j		$ra

while:		
		#aca primero el codigo del while
		#al final la condicion del while
		slt		$t3,$t2,$t1 #pri<ult 
		bne		$t3,$ZERO,while
		#aca llamada a swap
		
		
		
		
#calculo tamanio stack frame: 
#16 bytes de (ra+fp+gp+4bytes align) + 16 bytes argument build area (es non leaf) + 8bytes unspecified + 16 bytes variables locales = 56bytes