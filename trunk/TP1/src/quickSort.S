#include <mips/regdef.h>

	.globl quickSort

quickSort:
	subu 	sp,sp,56 	#Armo stack de 56 bytes:
	
	sw	ra,48(sp)
	sw	$fp,44(sp)
	sw	gp,40(sp)
	move	$fp,sp
				#guardo los parametros en el stack frame
	sw	a0,56($fp) #izq
	sw	a1,60($fp) #der
	sw	a2,64($fp) #num
	
	move	s3,a0   # izq
	move	s4,a1	# der
	
	move	s0,a1 # pivot
	move	s1,a0 #pri
	move	s2,a1 #ult

	slt 	t2,s4,s3 #der<izq seteo t2
	bne	t2,zero,qsortEnd

while1:
	blt	t1,t0,qsortContinuation

while2:
	#inicio while (pri<ult)

	#inicio while(pri<ult+1 && !esMayor(*pri,pivot,num))
	addu	t3,s2,4

	sge	t4,s1,t3 #pri<ult+1 (negado)

	move  	a0,s1 #pri
	move	a1,s0
			    #a2 no lo cargo, siempre vale lo mismo
	jal	esMayor

	addu	t6,t4,v0 #esto es el && tienen que dar los dos 0
	bne	t6,zero,while3
	add     s1,s1,4 #pri++
	j	while2

while3:
	#inicio while(ult>pri-1 && esMayor(*ult,pivot,num))
	subu	t3,s1,4

	slt  	t4,t3,s2 #ult>pri-1

	move    a0,s2 #ult
	move	a1,s0
		    #a2 no lo cargo, siempre vale lo mismo
	jal	esMayor

	addu	t6,t4,v0 #esto es el && tienen que dar los dos 1 (2 en total)
	bne	t6,2,if
	subu    s2,s2,4 #ult--
	j	while3

if:
	slt	t3,s1,s2 #pri<ult
	beq	t3,zero,while1 #si ult>pri no hago el swap y me voy al while 1 para chequear la condicion
	#inicio swap
	move	a0,s1
	move	a1,s2
	jal	swap
	#fin swap
	j	while1

qsortContinuation: #esta es la seccion que hace el swap y las llamadas recursivas
	#inicio swap
	
	move	a0,s3
	move	a1,s2
	jal	swap
	#fin swap

	#aca las 2 llamadas recursivas
	move 	a0,s3
	subu	t3,s2,4
	move	a1,t3

	jal	quickSort

	add	t3,s2,4
	move	a0,t3
	move	a1,s4
	jal	quickSort

qsortEnd:
	#aca muere el qsort
	move	sp,$fp
	lw	ra,48(sp)
	lw	$fp,44(sp)
	addu	sp,sp,56
	j	ra
	
#-------------------------------Funcion es mayor---------------------------#	
	.globl esMayor
esMayor:
	subu	sp,sp,48
	sw	ra,40(sp)
	sw	$fp,36(sp)
	sw	gp,32(sp)
	move    $fp,sp
	sw	a0,48($fp)
	sw	a1,52($fp)
	sw	a2,56($fp)
	
	lw 	t0,48($fp)
	lw 	t1,52($fp)
	
	sw	t0,4($fp)
	sw	t1,8($fp)
        sw 	zero,12($fp) #subindice para recorrer los string
	
	beq     a2,zero,esMayorChars
	
esMayorInt: #este castea a int y compara
	lw	a0,8($fp) #cargo argumentos para castToInt
	la 	t7,stringToInt
	jalr	t7
	sw	v0,48($fp)
	
	lw	a0,16($fp) #cargo argumentos para castToInt
	la 	t7,stringToInt
	jalr	t7
	sw	v0,52($fp)
	
	lw	t0,48($fp) #cargo los 2 ints convertidos para comparar
	lw	t1,52($fp)
	
	slt	v0,t1,t0 
	
	b	finEsMayor
	
esMayorChars:
	lw 	t5,4($fp) #levanto en $t3 el char del primer string
	lw 	t3,12($fp)
	addu 	t3,t5,t3
	lbu 	t3,0(t3) 
	
	lw 	t5,8($fp) #levanto en $t4 el char del segundo string
	lw 	t4,12($fp)
	addu 	t4,t5,t4	
	lbu 	t4,0(t4)
	
	#si alguno es '\0' lo asignamos como menor
	beq 	t3,zero,t0menor
	beq 	t4,zero,t1menor

	#$t0 es menor
	slt 	v0,t3,t4
	bne 	v0,zero,finEsMayor

	#$t1 es menor
	slt 	v0,t4,t3
	bne 	v0,zero,t1menor

	#si llegamos aca es porq los 2 caracteres son iguales
	lw 	t5,12($fp) #aumento el subindice  
	addu 	t5,t5,1
	sw 	t5,12($fp)	
	j 	esMayorChars

t0menor:
	li      v0,0
	b 	finEsMayor

t1menor:
	li 	v0,1
	b 	finEsMayor

#x (t0) menor--> 1 en $v0
#y (t1) menor--> 0 en $v0
	
finEsMayor: #se llama cuando termina la comparacion (sea de ints o chars)
	move    sp,$fp
	lw	ra,40(sp)
        lw      $fp,36(sp)
        addu    sp,sp,48
        jr      ra

#-------------------------------Funcion es mayor---------------------------#
#-------------------------------Funcion stringToInt---------------------------#
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
#-------------------------------Funcion stringToInt---------------------------#


#calculo tamanio stack frame:
#16 bytes de (ra+$fp+gp+4bytes align) + 16 bytes argument build area (es non leaf) + 8bytes unspecified + 16 bytes variables locales = 56bytes
