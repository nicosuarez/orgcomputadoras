#include <mips/regdef.h>

	.text
	.globl  stringToInt

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
	sw	$a2,64($fp)

	lw	$t0,56($fp)	# pri
	lw	$t1,60($fp)	# ult

	slt	$t2,$t0,$t1 #der<izq seteo t0
	bne	$t2,$zero,while1 #si no se cumple esa condicion sigo y me meto en el while

	#¿¿aca no habria que setear $ra para que el "j" de swap nos
	#lleve a las llamadas recursivas??

	#aca swap

	#aca las 2 llamadas recursivas
	addu	$t3,$t1,-1
	move	$a1,$t3

	la	$t9,qsort
	jal	$ra,$t9

	addu	$t3,$t1,1
	move	$a0,$t3

	la	$t9,qsort
	jal	$ra,$t9

	#aca muere el qsort
	move	$sp,$fp
	lw	$ra,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$ra

while1:
	#inicio while (pri<ult)

	#inicio while(pri<ult+1 && !esMayor(*pri,pivot,num))
	lw	$t2,60($fp) #pivot(izq)
	addi	$t3,$t2,1

	slt	$t4,$t0,$t3 #pri<ult+1
	slt	$t5,$t0,$t2 #pri mayor a pivot (negado)

	addu	$t6,$t4,$t5 #esto es el &&
	beq	$t6,$zero,while2

	#fin while(pri<ult+1 && !esMayor(*pri,pivot,num))

	#inicio while(ult>pri-1 && esMayor(*ult,pivot,num))
	addu	$t3,$t0,-1

	slt	$t4,$t3,$t1 #ult>pri-1
	slt	$t5,$t1,$t2 #ult mayor a pivot (negado)

	addu	$t6,$t4,$t5 #esto es el &&
	bne	$t6,$zero,while3

	#fin while(ult>pri-1 && esMayor(*ult,pivot,num))

	slt	$t3,$t0,$t1 #pri<ult
	beq	$t3,$zero,noswap #si ult>pri no hago el swap
	#aca llamada a swap
	move	$t7,$t0
	move 	$t0,$t1
	move 	$t1,$t7

noswap:
	slt	$t3,$t0,$t1 #pri<ult
	bne	$t3,$zero,while

	#fin while (pri<ult)

	#aca llamada a swap
	lw	$t9,56($fp)
	move	$t7,$t0
	move 	$t0,$t9
	move 	$t9,$t7
	#aca habria que hacer un store de izq??

while2:
	addu 	$t0,$t0,1

	slt	$t4,$t0,$t3 #pri<ult+1
	slt	$t5,$t0,$t2 #pri mayor a pivot (negado)

	addu	$t6,$t4,$t5 #esto es el &&

	beq	$t6,$zero,while2

while3:
	addu	$t1,$t1,-1

	slt	$t4,$t3,$t1 #ult>pri-1
	slt	$t5,$t1,$t2 #ult mayor a pivot (negado)

	addu	$t6,$t4,$t5 #esto es el &&
	bne	$t6,$zero,while3

#calculo tamanio stack frame:
#16 bytes de (ra+fp+gp+4bytes align) + 16 bytes argument build area (es non leaf) + 8bytes unspecified + 16 bytes variables locales = 56bytes
