#include <mips/regdef.h>          

		.text 	
		.globl qsort
qsort:
		subu 	sp,sp,56 	#Armo stack de 56 bytes: 
		sw		$ra,48($sp)
		sw		$fp,44($sp)
		sw		$gp,40($sp)
		move	$fp,$sp
		
		sw		$a0,56($fp) #guardo los parametros en el stack frame
		sw		$a1,60($fp) 	
		sw		$a2,64($fp) 	
		
		
		
		
		
		
		
#calculo tamanio stack frame: 
#16 bytes de (ra+fp+gp+4bytes align) + 16 bytes argument build area (es non leaf) + 8bytes unspecified + 16 bytes variables locales = 56bytes