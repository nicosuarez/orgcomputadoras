#include <mips/regdef.h>

	.globl qsort

qsort:
	subu 	$sp,$sp,56 	#Armo stack de 56 bytes:
	sw	$ra,48($sp)
	sw	$fp,44($sp)
	sw	$gp,40($sp)
	move	$fp,$sp
				#guardo los parametros en el stack frame
	sw	$a0,56($fp) #izq
	sw	$a1,60($fp) #der
	sw	$a2,64($fp) #num
	sw	$a0,68($fp) # pivot
	
	lw	$t0,56($fp)	# pri
	lw	$t1,60($fp)	# ult
	
	slt 	$t2,$t0,$t1 #der<izq seteo t2
	bne	$t2,$zero,qsortEnd
	
while1:
	blt	$t1,$t0,qsortContinuation

while2:
	#inicio while (pri<ult)
	
	#inicio while(pri<ult+1 && !esMayor(*pri,pivot,num))
	addu	$t3,$t1,1
	
	sge	$t4,$t0,$t3 #pri<ult+1 (negado)
	
	lw      $a0,56($fp) #pri
	lw	$a1,68($fp) #pivot
			    #a2 no lo cargo, siempre vale lo mismo
	la 	$t9,esMayor
	jal	$t9
	
	addu	$t6,$t4,$v0 #esto es el && tienen que dar los dos 0
	bne	$t6,$zero,while3
	addi    $t6,$t0,1 #pri++
	move    $t0,$t6
	j	while2	

while3:
	#inicio while(ult>pri-1 && esMayor(*ult,pivot,num))
	addu	$t3,$t0,-1

	slt  	$t4,$t3,$t1 #ult>pri-1
	
	lw      $a0,60($fp) #pri
	lw	$a1,68($fp) #pivot
			    #a2 no lo cargo, siempre vale lo mismo
	la 	$t9,esMayor
	jal	$t9

	addu	$t6,$t4,$v0 #esto es el && tienen que dar los dos 1 (2 en total)
	bne	$t6,2,if
	addi    $t6,$t1,-1 #ult--
	move    $t1,$t6 #guardo el ult
	j	while3
	
if:
	slt	$t3,$t0,$t1 #pri<ult
	beq	$t3,$zero,while1 #si ult>pri no hago el swap y me voy al while 1 para chequear la condicion
	#inicio swap
	move	$t7,$t0
	move 	$t0,$t1
	move 	$t1,$t7
	#fin swap
	j	while1
	
qsortContinuation: #esta es la seccion que hace el swap y las llamadas recursivas
	#inicio swap
	move	$t7,$t1
	lw	$t4,60($fp)
	move 	$t1,$t4
	sw	$t7,60($fp)
	#fin swap
	
	#aca las 2 llamadas recursivas
	addu	$t3,$t1,-1
	move	$a1,$t3

	la	$t9,qsort
	jal	$ra,$t9
	
	addu	$t3,$t1,1
	move	$a0,$t3

	la	$t9,qsort
	jal	$ra,$t9

qsortEnd:
	#aca muere el qsort
	move	$sp,$fp
	lw	$ra,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$ra
	.end    qsort
#-------------------------------Funcion es mayor---------------------------#	
esMayor:
	subu	$sp,$sp,24
	sw	$fp,20($sp)
	sw	$gp,16($sp)
	move    $fp,$sp
	sw	$a0,24($sp)
	sw	$a1,28($sp)
	sw	$a2,32($sp)
	
	lw 	$t0,24($sp)
	lw 	$t1,28($sp)
	
	sw 	$zero,12($fp) #subindice para recorrer los string
	
	beq     $a2,$zero,esMayorChars
	
esMayorInt: #este castea a int y compara
	lw	$a0,24($fp) #cargo argumentos para castToInt
	la 	$t9,stringToInt
	jal	$ra,$t9
	sw	$v0,24($fp)
	
	lw	$a1,28($fp) #cargo argumentos para castToInt
	la 	$t9,stringToInt
	jal	$ra,$t9
	sw	$v0,28($fp)
	
	lw	$t0,24($fp) #cargo los 2 ints convertidos para comparar
	lw	$t1,28($fp)
	
	slt	$v0,$t0,$t1 
	
	b	finEsMayor
	
esMayorChars:
	lw $t5,0($t0) #levanto en $t3 el char del primer string
	lw $t3,12($fp)
	addu $t3,$t5,$t3
	lbu $t3,0($t3) 
	
	lw $t5,0($t1) #levanto en $t4 el char del segundo string
	lw $t4,12($fp)
	addu $t4,$t5,$t4	
	lbu $t4,0($t4)
	
	#si alguno es '\0' lo asignamos como menor
	beq $t3,$zero,t0menor
	beq $t4,$zero,t1menor

	#$t0 es menor
	slt $v0,$t3,$t4
	bne $v0,$zero,finEsMayor

	#$t1 es menor
	slt $v0,$t4,$t3
	bne $v0,$zero,t1menor

	#si llegamos aca es porq los 2 caracteres son iguales
	lw $t5,12($fp) #aumento el subindice  
	addu $t5,$t5,1
	sw $t5,12($fp)	
	j esMayorChars

t0menor:
	li $v0,1
	b finEsMayor

t1menor:
	li $v0,0
	b finEsMayor

#x (t0) menor--> 1 en $v0
#y (t1) menor--> 0 en $v0
	
finEsMayor: #se llama cuando termina la comparacion (sea de ints o chars)
	move    $sp,$fp
        lw      $fp,20($sp)
        addu    $sp,$sp,24
        j       $ra
#-------------------------------Funcion es mayor---------------------------#

#-------------------------------Funcion stringToInt---------------------------#
stringToInt:
        subu    $sp,$sp,24
        sw      $fp,20($sp)
        sw      $gp,16($sp)
        move    $fp,$sp
        sw      $a0,24($fp)
        sw      $zero,8($fp)
        sw      $zero,12($fp)
while:
        lw      $v1,24($fp)
        lw      $v0,8($fp)
        addu    $v0,$v1,$v0
        lb      $v0,0($v0)
        beq     $v0,$zero,salir
        lw      $v1,12($fp)
        move    $v0,$v1
        sll     $v0,$v0,2   #multiplicacion por 10
        addu    $v0,$v0,$v1
        sll     $v0,$v0,1
        sw      $v0,12($fp)
        lw      $v1,24($fp)
        lw      $v0,8($fp)
        addu    $v0,$v1,$v0
        lb      $v1,0($v0)
        lw      $v0,12($fp)
        addu    $v0,$v1,$v0
        addu    $v0,$v0,-48
        sw      $v0,12($fp)
        lw      $v0,8($fp)
        addu    $v0,$v0,1
        sw      $v0,8($fp)
        b       while
salir:
        lw      $v0,12($fp)
        move    $sp,$fp
        lw      $fp,20($sp)
        addu    $sp,$sp,24
        j       $ra
#-------------------------------Funcion stringToInt---------------------------#

#calculo tamanio stack frame:
#16 bytes de (ra+fp+gp+4bytes align) + 16 bytes argument build area (es non leaf) + 8bytes unspecified + 16 bytes variables locales = 56bytes
