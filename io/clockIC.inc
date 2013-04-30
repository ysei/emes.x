;----------------------------------------------------------------------------------------------
; MSX Emulator for X680x0 - emes.x
;
;    Copyright 1997-1998 nir
;



_readClockIC:
	
	move.w	ClockIC_block(regZjmp),d0		* 12
	beq.s	@f					* 10/ 8 (T/F)
	
	*-- Block 1,2,3 �ǂݍ���
	lea	_ClockIC_memory(pc),a0			*  8
	adda.w	d0,a0					*  8
	adda.w	ClockIC_adr(regZjmp),a0			* 
	
	move.b	(a0),d1					*  8
;	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
@@:	*-- Block 0 �ǂݍ���
	*
	*	   +-------------+
	*	 0 | �b�i�P�̈ʁj|
	*	   +-------------+
	*	 1 | �b�i10�̈ʁj|
	*	   +-------------+
	*	 2 | ���i�P�̈ʁj|
	*	   +-------------+
	*	 3 | ���i10�̈ʁj|
	*	   +-------------+
	*	 4 | ���i�P�̈ʁj|
	*	   +-------------+
	*	 5 | ���i10�̈ʁj|
	*	   +-------------+
	*	 6 | �j��        |
	*	   +-------------+
	*	 7 | ���i�P�̈ʁj|
	*	   +-------------+
	*	 8 | ���i10�̈ʁj|
	*	   +-------------+
	*	 9 | ���i�P�̈ʁj|
	*	   +-------------+
	*	10 | ���i10�̈ʁj|
	*	   +-------------+
	*	11 | �N�i�P�̈ʁj|
	*	   +-------------+
	*	12 | �N�i10�̈ʁj|
	*	   +-------------+
	
	move.w	ClockIC_adr(regZjmp),d0			* 12
	
	cmpi.w	#6,d0					* 
	bcc.s	@f					* 10/ 8 (T/F)
	
	*-- �����b
	cmpi.w	#5,d0					* 
	bne	1f					* 
	
	*-- ���i10�̈ʁj
	moveq.l	#$54,d0					*  4
	trap	#15					* 	_TIMEGET
	
	lsr.w	#8,d0					* 
	lsr.w	#4,d0					* 
	move.b	d0,d1					* 
	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
1:	*
	add.w	d0,d0					*  4
	add.w	d0,d0					*  4
	move.w	d0,d1					*  4
	
	moveq.l	#$56,d0					*  4
	trap	#15					* 	_TIMEGET
	
	lsr.l	d1,d0					* 
	move.b	d0,d1					*  4
	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
@@:	
	cmpi.w	#6,d0					* 
	bne.s	@f					* 10/ 8 (T/F)
	
	*-- �j��
	moveq.l	#$54,d0					*  4
	trap	#15					* 	_DATEGET
	
	swap.w	d0					*  4
	lsr.w	#8,d0					* 
	move.b	d0,d1					*  4
	
	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
@@:	
	cmpi.w	#13,d0					* 
	bcc.s	@f					* 10/ 8 (T/F)
	
	*-- �N����
	subi.w	#7,d0					* 
	add.w	d0,d0					* 
	add.w	d0,d0					* 
	move.w	d0,d1					* 
	
	moveq.l	#$54,d0					*  4
	trap	#15					* 	_DATEGET
	
	lsr.l	d1,d0					* 
	move.b	d0,d1					*  4
	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
@@:	
	cmpi.w	#13,d0					* 
	bne.s	@f					* 10/ 8 (T/F)
	
	*-- ���[�h���W�X�^
	move.w	ClockIC_modeReg(regZjmp),d1		* 12
	ori.b	#%1111_0000,d1				*  8
	
	rts						* 16
	
@@:	
	*-- �s���ȃA�h���X
	move.b	#$ff,d1					* 
	
	rts						* 16


*----------------------------------------------------------------------------------------------
_ClockIC_memory:
	*--- BLOCK 0
	.dc.b	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	
	*--- BLOCK 1
	.dc.b	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	
	*--- BLOCK 2
	.dc.b	0	*  0: ID
	.dc.b	0	*  1: Adjust X (-8 ~ +7)
	.dc.b	0	*  2: Adjust Y (-8 ~ +7)
	.dc.b	0	*  3: Interlace Mode, Screen Mode
	.dc.b	0	*  4: WIDTH�̒l (Lo)
	.dc.b	0	*  5: WIDTH�̒l (Hi)
	.dc.b	15	*  6: �O�i�F
	.dc.b	4	*  7: �w�i�F
	.dc.b	4	*  8: ���ӐF
	.dc.b	0	*  9: Cassette Speed, Printer Mode, Key Click, Key ON/OFF
	.dc.b	0	* 10: BEEP ���F, BEEP ����
	.dc.b	0	* 11: �^�C�g���J���[
	.dc.b	0	* 12: ���ʃR�[�h
	.dc.b	0	* 13:
	.dc.b	0	* 14:
	.dc.b	0	* 15:
	
	*-- BLOCK 3
	.dc.b	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
