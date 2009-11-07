#include <mips/regdef.h>

	.globl	quickSort

#izq = a0
#der = a1
#num = a2
quickSort:
	subu 	 sp,sp,56 	#Armo stack de 56 bytes
	sw 	 s0,52(sp)
	sw 	 s1,48(sp)	#Guardo registros save en el stack
	sw 	 s2,44(sp)
	sw 	 s3,40(sp)
	sw 	 s4,36(sp)

	sw 	 ra,32(sp)
	sw 	 $fp,28(sp)
	sw	 gp,24(sp)	
	move 	 $fp,sp

	sw       a0,56($fp)
	sw       a1,60($fp)
	sw       a2,64($fp)

	
	bge 	 a0,a1,fin_quickSort	# if(izq>=der)return;
	lw	 s0,0(a1)		# pivote = *der;
	move	 s1,a1			# sup = der;
	sub	 s2,a0,4		#inf = izq-1;

	#guardo los 2 primeros registros pasados en temporales para usarlos despues
	move	s3,a0
	move	s4,a1

while1:			#while(1)
		
while2:			# do
	add	s2,s2,4			#++inf;
							
	lw a0,0(s2)
	move a1,s0
	jal esMayor	#comp = compNum(*inf,pivote);

	bnez	v0,while2		#while(comp)

while3:			#do
	subu	s1,s1,4			#--sup;
				
	move a0,s0
	lw a1,0(s1)
	jal esMayor	#comp = compNum(pivote,*sup);	
	beq s2,s1,fin_while3	#	if(sup==izq)break;
	bnez	v0,while3		#while(comp)

fin_while3:
		
	bge s2,s1,fin_while1	# if(inf>=sup ) break;
		
	move a0,s2
	move a1,s1
	jal  swap	#swap(inf,sup);
	j	while1	#}

fin_while1:
	move a0,s2
	move a1,s4
	jal  swap	#swap(inf,der);
	
	move a0,s3
	move a1,s1
	jal quickSort	#quickSort(izq, sup, num);
	
	move a0,s2
	move a1,s4
	jal quickSort	#quickSort(inf, der, num);			

fin_quickSort:
	move 	 sp,$fp		#Tendria que salvar valores y etceteras
	lw 	 s0,52(sp)
	lw 	 s1,48(sp)
	lw 	 s2,44(sp)
	lw 	 s3,40(sp)
	lw 	 s4,36(sp)

	lw 	 ra,32(sp)
	lw 	 $fp,28(sp)
	lw	 gp,24(sp)

	addu 	 sp, sp,56
	j	 ra
	
