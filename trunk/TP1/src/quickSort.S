#include <mips/regdef.h>

	.globl	quickSort

quickSort:
	subu 	sp,sp,56 	#Armo stack de 56 bytes
	sw 	s0,52(sp)
	sw 	s1,48(sp)	#Guardo registros save en el stack
	sw      s2,44(sp)
	sw 	s3,40(sp)
	sw 	s4,36(sp)

	sw 	ra,32(sp)
	sw 	$fp,28(sp)
	sw	gp,24(sp)	
	move 	$fp,sp

	sw      a0,56($fp) #izq
	sw      a1,60($fp) #der
	sw      a2,64($fp) #num

	bge 	a0,a1,fin_quickSort	# if(izq>=der)return;
	lw	s0,0(a1)		# pivot = *der;
	move	s1,a1			# sup = der;
	sub	s2,a0,4			# inf = izq-1;

	#guardo los 2 primeros registros pasados en temporales para usarlos despues
	move	s3,a0
	move	s4,a1

while1:			#while(1)
		
while2:			# do
	add	s2,s2,4			#++inf;
							
	lw 	a0,0(s2)
	move 	a1,s0
	beqz 	a2,comparacionChars1
	jal 	esMayorInt	#comp = esMayor(*inf,pivot);
	j    	salidaComparacion1

comparacionChars1:
	jal	esMayorChar
salidaComparacion1:
	bnez	v0,while2		#while(comp)

while3:			#do
	subu	s1,s1,4			#--sup;
				
	move 	a0,s0
	lw 	a1,0(s1)
	beqz 	a2,comparacionChars2
	jal 	esMayorInt	#comp = esMayor(*inf,pivot);
	j    	salidaComparacion2
	
comparacionChars2:
	jal	esMayorChar

salidaComparacion2:
	beq 	s2,s1,fin_while3	#	if(sup==izq)break;
	bnez	v0,while3		#while(comp)

fin_while3:
		
	bge 	s2,s1,fin_while1	# if(inf>=sup ) break;
		
	move 	a0,s2
	move 	a1,s1
	jal  	swap	#swap(inf,sup);
	j	while1	#}

fin_while1:
	move 	a0,s2
	move 	a1,s4
	jal  	swap	#swap(inf,der);
	
	beq 	s2,s1,increment	# if(inf==sup ) inf++
	j	fin_while1Cont

increment:
	add	s2,s2,4

fin_while1Cont:
	move 	a0,s3
	move 	a1,s1
	jal 	quickSort	#quickSort(izq, sup, num);
	
	move 	a0,s2
	move 	a1,s4
	jal 	quickSort	#quickSort(inf, der, num);			

fin_quickSort:
	move 	sp,$fp		
	lw 	s0,52(sp)
	lw 	s1,48(sp)
	lw 	s2,44(sp)	#Salvo valores
	lw 	s3,40(sp)
	lw 	s4,36(sp)

	lw 	ra,32(sp)
	lw 	$fp,28(sp)
	lw	gp,24(sp)

	addu 	sp, sp,56
	j	ra
	
#-------------------------------Funcion esMayorChar---------------------------#
	.globl  esMayorChar
	.ent	esMayorChar
esMayorChar:
	subu	sp,sp,32
	sw	$fp,28(sp)
	sw	gp,24(sp)
	move	$fp,sp
	sw	a0,8($fp)	#almaceno char* x
	sw	a1,12($fp)	#almaceno char* y
	sw	zero,16($fp)	#indice
	b	comparo
comparo:
	lw 	t0,16($fp) #cargo en t0 el valor del indice

	#cargo en t1 el char de x
	lw 	t1,8($fp)
	addu 	t1,t1,t0
	lb 	t1,0(t1)

	#cargo en t2 el char de y
	lw 	t2,12($fp)
	addu 	t2,t2,t0
	lb 	t2,0(t2)

	#si alguno es '\0' lo asignamos como menor
	beq	t1,zero,xMenor
	beq	t2,zero,yMenor

	#Chequeo si x es menor que y
	slt 	t3,t1,t2
	bne 	t3,zero,xMenor

	#Chequeo si y es menor que x
	slt 	t3,t2,t1
	bne 	t3,zero,yMenor

	#si llegamos aca es porq los 2 caracteres son iguales
	lw	t0,16($fp) #aumento el subindice
	addu	t0,t0,1
	sw 	t0,16($fp)
	j 	comparo

xMenor:
	li 	v0,0
	b 	finEsMayor
yMenor:
	li 	v0,1
	b 	finEsMayor

finEsMayor:
	move	sp,$fp
	lw	$fp,28(sp)
	addu	sp,sp,32
	j	ra
	.end	esMayorChar
#-------------------------------Funcion esMayorInt---------------------------#
	.globl  esMayorInt
	.ent	esMayorInt
esMayorInt:
	subu	sp,sp,48
	sw	ra,40(sp)
	sw	$fp,36(sp)
	sw	gp,32(sp)
	move	$fp,sp
	sw	a0,48($fp) #almaceno x
	sw	a1,52($fp) #almaceno y

	lw	a0,48($fp) #convierto x a entero
	la	t9,stringToInt
	jal	ra,t9
	sw	v0,24($fp)

	lw	a0,52($fp) #convierto y a entero
	la	t9,stringToInt
	jal	ra,t9
	sw	v0,28($fp)

	lw	t0,24($fp)
	lw	t1,28($fp)
	slt	v0,t1,t0

	move	sp,$fp
	lw	ra,40(sp)
	lw	$fp,36(sp)
	addu	sp,sp,48
	j	ra
	.end	esMayorInt
#-------------------------------Funcion stringToInt---------------------------#
	.globl  stringToInt
	.ent	stringToInt
stringToInt:
        subu    sp,sp,24
        sw      $fp,20(sp)
        sw      gp,16(sp)
        move    $fp,sp
        sw      a0,24($fp)
        sw      zero,8($fp)
        sw      zero,12($fp)
while:
        lw      v1,24($fp)
        lw      v0,8($fp)
        addu    v0,v1,v0
        lb      v0,0(v0)
        beq     v0,zero,salir
        lw      v1,12($fp)
        move    v0,v1
        sll     v0,v0,2   #multiplicacion por 10
        addu    v0,v0,v1
        sll     v0,v0,1
        sw      v0,12($fp)
        lw      v1,24($fp)
        lw      v0,8($fp)
        addu    v0,v1,v0
        lb      v1,0(v0)
        lw      v0,12($fp)
        addu    v0,v1,v0
        addu    v0,v0,-48
        sw      v0,12($fp)
        lw      v0,8($fp)
        addu    v0,v0,1
        sw      v0,8($fp)
        b       while
salir:
        lw      v0,12($fp)
        move    sp,$fp
        lw      $fp,20(sp)
        addu    sp,sp,24
        jr      ra
    	.end	stringToInt#-------------------------------Funcion swap---------------------------#
	.globl swap
	.ent	swap
swap:
	subu	sp,sp,24
	sw	$fp,20(sp)
	sw	gp,16(sp)
	move	$fp,sp
	sw	a0,24($fp)
	sw	a1,28($fp)
	lw	v0,24($fp)
	lw	v0,0(v0)
	sw	v0,8($fp)
	lw	v1,24($fp)
	lw	v0,28($fp)
	lw	v0,0(v0)
	sw	v0,0(v1)
	lw	v1,28($fp)
	lw	v0,8($fp)
	sw	v0,0(v1)
	move	sp,$fp
	lw	$fp,20(sp)
	addu	sp,sp,24
	j	ra
	.end	swap

