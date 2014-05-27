# start of generated code
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	2
_bool_tag:
	.word	3
_string_tag:
	.word	4
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const13:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bazz"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Razz"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Bar"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Foo"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const6
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const7
	.ascii	"do nothing"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const8
	.ascii	"./hairyscary.cl"
	.byte	0	
	.align	2
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	15
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const3:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const2:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
bool_const0:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const3
	.word	str_const4
	.word	str_const5
	.word	str_const6
	.word	str_const7
	.word	str_const12
	.word	str_const11
	.word	str_const10
	.word	str_const9
	.word	str_const8
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	Main_protObj
	.word	Main_init
	.word	Bazz_protObj
	.word	Bazz_init
	.word	Razz_protObj
	.word	Razz_init
	.word	Bar_protObj
	.word	Bar_init
	.word	Foo_protObj
	.word	Foo_init
class_faTab:
	.word	-2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1
	.word	9
	.word	7
	.word	6
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
Bazz_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Bazz.doh
Razz_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
Bar_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
Foo_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	-1
Main_protObj:
	.word	5
	.word	7
	.word	Main_dispTab
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-1
Bazz_protObj:
	.word	6
	.word	6
	.word	Bazz_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	-1
Razz_protObj:
	.word	7
	.word	10
	.word	Razz_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	-1
Bar_protObj:
	.word	8
	.word	12
	.word	Bar_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	int_const2
	.word	0
	.word	-1
Foo_protObj:
	.word	9
	.word	8
	.word	Foo_dispTab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const2
	.word	0
	.word	-1
Bool_protObj:
	.word	3
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	jr	$ra	
IO_init:
	jr	$ra	
Int_init:
	jr	$ra	
Bool_init:
	jr	$ra	
String_init:
	jr	$ra	
main:
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	la	$a0 Bazz_protObj
	jal	Object.copy
	jal	Bazz_init
	sw	$a0 12($s0)
	la	$a0 Foo_protObj
	jal	Object.copy
	jal	Foo_init
	sw	$a0 16($s0)
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	sw	$a0 20($s0)
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	sw	$a0 24($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	la	$a0 int_const1
	sw	$a0 12($s0)
	move	$a0 $s0
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label0:
	lw	$t2 0($a0)
	li	$t3 -2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
label1:
	li	$t1 6
	beq	$t1 $t2 label2
	li	$t1 7
	beq	$t1 $t2 label3
	li	$t1 9
	beq	$t1 $t2 label4
	li	$t1 8
	beq	$t1 $t2 label5
	sll	$t2 $t2 2
	la	$t1 class_faTab
	add	$t2 $t1 $t2
	lw	$t2 0($t2)
	bne	$t2 $t3 label1
	jal	_case_abort
label2:
	la	$a0 Foo_protObj
	jal	Object.copy
	jal	Foo_init
	b	label6
label3:
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label6
label4:
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	b	label6
label5:
	lw	$a0 -4($fp)
	b	label6
label6:
	addiu	$sp $sp 4
	sw	$a0 16($s0)
	move	$a0 $s0
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label7:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz.printh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label8
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label8:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	la	$a0 int_const2
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bazz.doh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 12($s0)
	lw	$a0 -4($fp)
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Razz_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Foo_init
	move	$a0 $s0
	bne	$a0 $zero label9
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label9:
	lw	$t2 0($a0)
	li	$t3 -2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
label10:
	li	$t1 7
	beq	$t1 $t2 label11
	li	$t1 8
	beq	$t1 $t2 label12
	sll	$t2 $t2 2
	la	$t1 class_faTab
	add	$t2 $t1 $t2
	lw	$t2 0($t2)
	bne	$t2 $t3 label10
	jal	_case_abort
label11:
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label13
label12:
	lw	$a0 -4($fp)
	b	label13
label13:
	addiu	$sp $sp 4
	sw	$a0 32($s0)
	lw	$a0 24($s0)
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label14:
	jal	Bazz.doh
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($s0)
	bne	$a0 $zero label16
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label16:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label17
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label17:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 36($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bar_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Razz_init
	move	$a0 $s0
	bne	$a0 $zero label19
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label19:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 40($s0)
	move	$a0 $s0
	bne	$a0 $zero label20
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label20:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 44($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Foo_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Bazz_init
	move	$a0 $s0
	bne	$a0 $zero label21
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label21:
	lw	$t2 0($a0)
	li	$t3 -2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
label22:
	li	$t1 7
	beq	$t1 $t2 label23
	li	$t1 9
	beq	$t1 $t2 label24
	li	$t1 8
	beq	$t1 $t2 label25
	sll	$t2 $t2 2
	la	$t1 class_faTab
	add	$t2 $t1 $t2
	lw	$t2 0($t2)
	bne	$t2 $t3 label22
	jal	_case_abort
label23:
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label26
label24:
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	b	label26
label25:
	lw	$a0 -4($fp)
	b	label26
label26:
	addiu	$sp $sp 4
	sw	$a0 24($s0)
	lw	$a0 24($s0)
	bne	$a0 $zero label27
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label27:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label28
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label28:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label29
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label29:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label30
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label30:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 28($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Foo.doh:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 12($s0)
	lw	$a0 -4($fp)
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	

# end of generated code
