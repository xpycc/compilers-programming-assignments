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
str_const8:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const5
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	8
	.word	String_dispTab
	.word	int_const7
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"./not.cl"
	.byte	0	
	.align	2
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	6
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
	.word	1
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	100
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispTab
	.word	0
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
	.word	str_const2
	.word	str_const3
	.word	str_const4
	.word	str_const5
	.word	str_const6
	.word	str_const7
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
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
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
	.word	3
	.word	Main_dispTab
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispTab
	.word	int_const0
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
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 bool_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
label0:
	lw	$a0 -4($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	blt	$t1 $a0 label2
	la	$a0 bool_const0
	b	label3
label2:
	la	$a0 bool_const1
label3:
	addiu	$sp $sp 4
	lw	$a0 12($a0)
	beq	$a0 $zero label1
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	bne	$a0 $zero label4
	la	$a0 bool_const1
	b	label5
label4:
	la	$a0 bool_const0
label5:
	lw	$a0 12($a0)
	bne	$a0 $zero label6
	la	$a0 bool_const1
	b	label7
label6:
	la	$a0 bool_const0
label7:
	lw	$a0 12($a0)
	bne	$a0 $zero label8
	la	$a0 bool_const1
	b	label9
label8:
	la	$a0 bool_const0
label9:
	lw	$a0 12($a0)
	bne	$a0 $zero label10
	la	$a0 bool_const1
	b	label11
label10:
	la	$a0 bool_const0
label11:
	lw	$a0 12($a0)
	bne	$a0 $zero label12
	la	$a0 bool_const1
	b	label13
label12:
	la	$a0 bool_const0
label13:
	lw	$a0 12($a0)
	bne	$a0 $zero label14
	la	$a0 bool_const1
	b	label15
label14:
	la	$a0 bool_const0
label15:
	lw	$a0 12($a0)
	bne	$a0 $zero label16
	la	$a0 bool_const1
	b	label17
label16:
	la	$a0 bool_const0
label17:
	lw	$a0 12($a0)
	bne	$a0 $zero label18
	la	$a0 bool_const1
	b	label19
label18:
	la	$a0 bool_const0
label19:
	lw	$a0 12($a0)
	bne	$a0 $zero label20
	la	$a0 bool_const1
	b	label21
label20:
	la	$a0 bool_const0
label21:
	lw	$a0 12($a0)
	bne	$a0 $zero label22
	la	$a0 bool_const1
	b	label23
label22:
	la	$a0 bool_const0
label23:
	lw	$a0 12($a0)
	bne	$a0 $zero label24
	la	$a0 bool_const1
	b	label25
label24:
	la	$a0 bool_const0
label25:
	lw	$t1 4($sp)
	beq	$t1 $a0 label26
	move	$t2 $a0
	la	$a0 bool_const1
	la	$a1 bool_const0
	jal	equality_test
	b	label27
label26:
	la	$a0 bool_const1
label27:
	addiu	$sp $sp 4
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	bne	$a0 $zero label28
	la	$a0 bool_const1
	b	label29
label28:
	la	$a0 bool_const0
label29:
	lw	$a0 12($a0)
	bne	$a0 $zero label30
	la	$a0 bool_const1
	b	label31
label30:
	la	$a0 bool_const0
label31:
	lw	$a0 12($a0)
	bne	$a0 $zero label32
	la	$a0 bool_const1
	b	label33
label32:
	la	$a0 bool_const0
label33:
	lw	$a0 12($a0)
	bne	$a0 $zero label34
	la	$a0 bool_const1
	b	label35
label34:
	la	$a0 bool_const0
label35:
	lw	$a0 12($a0)
	bne	$a0 $zero label36
	la	$a0 bool_const1
	b	label37
label36:
	la	$a0 bool_const0
label37:
	lw	$a0 12($a0)
	bne	$a0 $zero label38
	la	$a0 bool_const1
	b	label39
label38:
	la	$a0 bool_const0
label39:
	lw	$a0 12($a0)
	bne	$a0 $zero label40
	la	$a0 bool_const1
	b	label41
label40:
	la	$a0 bool_const0
label41:
	lw	$a0 12($a0)
	bne	$a0 $zero label42
	la	$a0 bool_const1
	b	label43
label42:
	la	$a0 bool_const0
label43:
	lw	$a0 12($a0)
	bne	$a0 $zero label44
	la	$a0 bool_const1
	b	label45
label44:
	la	$a0 bool_const0
label45:
	lw	$a0 12($a0)
	bne	$a0 $zero label46
	la	$a0 bool_const1
	b	label47
label46:
	la	$a0 bool_const0
label47:
	lw	$a0 12($a0)
	bne	$a0 $zero label48
	la	$a0 bool_const1
	b	label49
label48:
	la	$a0 bool_const0
label49:
	lw	$t1 4($sp)
	beq	$t1 $a0 label50
	move	$t2 $a0
	la	$a0 bool_const1
	la	$a1 bool_const0
	jal	equality_test
	b	label51
label50:
	la	$a0 bool_const1
label51:
	addiu	$sp $sp 4
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	bne	$a0 $zero label52
	la	$a0 bool_const1
	b	label53
label52:
	la	$a0 bool_const0
label53:
	lw	$a0 12($a0)
	bne	$a0 $zero label54
	la	$a0 bool_const1
	b	label55
label54:
	la	$a0 bool_const0
label55:
	lw	$a0 12($a0)
	bne	$a0 $zero label56
	la	$a0 bool_const1
	b	label57
label56:
	la	$a0 bool_const0
label57:
	lw	$a0 12($a0)
	bne	$a0 $zero label58
	la	$a0 bool_const1
	b	label59
label58:
	la	$a0 bool_const0
label59:
	lw	$a0 12($a0)
	bne	$a0 $zero label60
	la	$a0 bool_const1
	b	label61
label60:
	la	$a0 bool_const0
label61:
	lw	$a0 12($a0)
	bne	$a0 $zero label62
	la	$a0 bool_const1
	b	label63
label62:
	la	$a0 bool_const0
label63:
	lw	$a0 12($a0)
	bne	$a0 $zero label64
	la	$a0 bool_const1
	b	label65
label64:
	la	$a0 bool_const0
label65:
	lw	$a0 12($a0)
	bne	$a0 $zero label66
	la	$a0 bool_const1
	b	label67
label66:
	la	$a0 bool_const0
label67:
	lw	$a0 12($a0)
	bne	$a0 $zero label68
	la	$a0 bool_const1
	b	label69
label68:
	la	$a0 bool_const0
label69:
	lw	$a0 12($a0)
	bne	$a0 $zero label70
	la	$a0 bool_const1
	b	label71
label70:
	la	$a0 bool_const0
label71:
	lw	$a0 12($a0)
	bne	$a0 $zero label72
	la	$a0 bool_const1
	b	label73
label72:
	la	$a0 bool_const0
label73:
	lw	$t1 4($sp)
	beq	$t1 $a0 label74
	move	$t2 $a0
	la	$a0 bool_const1
	la	$a1 bool_const0
	jal	equality_test
	b	label75
label74:
	la	$a0 bool_const1
label75:
	addiu	$sp $sp 4
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	bne	$a0 $zero label76
	la	$a0 bool_const1
	b	label77
label76:
	la	$a0 bool_const0
label77:
	lw	$a0 12($a0)
	bne	$a0 $zero label78
	la	$a0 bool_const1
	b	label79
label78:
	la	$a0 bool_const0
label79:
	lw	$a0 12($a0)
	bne	$a0 $zero label80
	la	$a0 bool_const1
	b	label81
label80:
	la	$a0 bool_const0
label81:
	lw	$a0 12($a0)
	bne	$a0 $zero label82
	la	$a0 bool_const1
	b	label83
label82:
	la	$a0 bool_const0
label83:
	lw	$a0 12($a0)
	bne	$a0 $zero label84
	la	$a0 bool_const1
	b	label85
label84:
	la	$a0 bool_const0
label85:
	lw	$a0 12($a0)
	bne	$a0 $zero label86
	la	$a0 bool_const1
	b	label87
label86:
	la	$a0 bool_const0
label87:
	lw	$a0 12($a0)
	bne	$a0 $zero label88
	la	$a0 bool_const1
	b	label89
label88:
	la	$a0 bool_const0
label89:
	lw	$a0 12($a0)
	bne	$a0 $zero label90
	la	$a0 bool_const1
	b	label91
label90:
	la	$a0 bool_const0
label91:
	lw	$a0 12($a0)
	bne	$a0 $zero label92
	la	$a0 bool_const1
	b	label93
label92:
	la	$a0 bool_const0
label93:
	lw	$a0 12($a0)
	bne	$a0 $zero label94
	la	$a0 bool_const1
	b	label95
label94:
	la	$a0 bool_const0
label95:
	lw	$a0 12($a0)
	bne	$a0 $zero label96
	la	$a0 bool_const1
	b	label97
label96:
	la	$a0 bool_const0
label97:
	lw	$t1 4($sp)
	beq	$t1 $a0 label98
	move	$t2 $a0
	la	$a0 bool_const1
	la	$a1 bool_const0
	jal	equality_test
	b	label99
label98:
	la	$a0 bool_const1
label99:
	addiu	$sp $sp 4
	lw	$a0 -8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	bne	$a0 $zero label100
	la	$a0 bool_const1
	b	label101
label100:
	la	$a0 bool_const0
label101:
	lw	$a0 12($a0)
	bne	$a0 $zero label102
	la	$a0 bool_const1
	b	label103
label102:
	la	$a0 bool_const0
label103:
	lw	$a0 12($a0)
	bne	$a0 $zero label104
	la	$a0 bool_const1
	b	label105
label104:
	la	$a0 bool_const0
label105:
	lw	$a0 12($a0)
	bne	$a0 $zero label106
	la	$a0 bool_const1
	b	label107
label106:
	la	$a0 bool_const0
label107:
	lw	$a0 12($a0)
	bne	$a0 $zero label108
	la	$a0 bool_const1
	b	label109
label108:
	la	$a0 bool_const0
label109:
	lw	$a0 12($a0)
	bne	$a0 $zero label110
	la	$a0 bool_const1
	b	label111
label110:
	la	$a0 bool_const0
label111:
	lw	$a0 12($a0)
	bne	$a0 $zero label112
	la	$a0 bool_const1
	b	label113
label112:
	la	$a0 bool_const0
label113:
	lw	$a0 12($a0)
	bne	$a0 $zero label114
	la	$a0 bool_const1
	b	label115
label114:
	la	$a0 bool_const0
label115:
	lw	$a0 12($a0)
	bne	$a0 $zero label116
	la	$a0 bool_const1
	b	label117
label116:
	la	$a0 bool_const0
label117:
	lw	$a0 12($a0)
	bne	$a0 $zero label118
	la	$a0 bool_const1
	b	label119
label118:
	la	$a0 bool_const0
label119:
	lw	$a0 12($a0)
	bne	$a0 $zero label120
	la	$a0 bool_const1
	b	label121
label120:
	la	$a0 bool_const0
label121:
	lw	$t1 4($sp)
	beq	$t1 $a0 label122
	move	$t2 $a0
	la	$a0 bool_const1
	la	$a1 bool_const0
	jal	equality_test
	b	label123
label122:
	la	$a0 bool_const1
label123:
	addiu	$sp $sp 4
	lw	$a0 -4($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	jal	Object.copy
	lw	$t1 12($a0)
	lw	$t2 4($sp)
	lw	$t2 12($t2)
	add	$t1 $t2 $t1
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 -4($fp)
	b	label0
label1:
	lw	$a0 -8($fp)
	lw	$a0 12($a0)
	beq	$a0 $zero label124
	move	$a0 $s0
	bne	$a0 $zero label126
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label126:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	b	label125
label124:
	la	$a0 int_const0
label125:
	addiu	$sp $sp 4
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	

# end of generated code
