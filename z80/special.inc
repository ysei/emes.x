;----------------------------------------------------------------------------------------------
; MSX Emulator for X680x0 - emes.x
;
;    Copyright 1997-1998 nir
;
;
; ���ꖽ��



	SET_OFFSET	SlotTable
	SET_OFFSET	SlotTablePage0
	SET_OFFSET	SlotTablePage1
	SET_OFFSET	SlotTablePage2
	SET_OFFSET	SlotTablePage3

	SET_OFFSET	regSave
	SET_OFFSET	Z80_DIEI



;----------------------------------------------------------------------------------------------
; �w��ۯĂ���P�޲ēǂݏo��
;
; IN:	A:  �ۯĎw��
;	HL: ���ڽ
; OUT:	A:  �ǂݏo�����l
; BREAK:AF,BC,DE

_Special_RDSLT:
	;-- �ǂݍ����߰��
	lea	SlotTable(regFtbl),a0			*  8
	move.w	regHL,d0				*  4
	andi.w	#%1100_0000_0000_0000,d0		*  8
	lsr.w	#6,d0					* 
	adda.w	d0,a0					*  8
	
	;--
	cmpi.w	#%0000_0000_0000_0000,d0		*  8
	bne.s	@f					* 10/ 8 (T/F)
	lea	SlotPage0(regZjmp),a1			*  8
	bra	1f					* 10
	
@@:	cmpi.w	#%0000_0001_0000_0000,d0		*  8
	bne.s	@f					* 10/ 8 (T/F)
	lea	SlotPage1(regZjmp),a1			*  8
	bra	1f					* 10

@@:	cmpi.w	#%0000_0010_0000_0000,d0		*  8
	bne.s	@f					* 10/ 8 (T/F)
	lea	SlotPage2(regZjmp),a1			*  8
	bra	1f					* 10
@@:
	lea	SlotPage3(regZjmp),a1			*  8
1:
	
	;-- �ǂݍ��݊�{�ۯ�
	moveq.l	#%0000_0011,d0				*  4
	and.b	regA,d0					*  4
	ror.b	#2,d0					* 
	
	;-- �ǂݍ��݊g���ۯ�
	moveq.l	#%0000_1100,d1				*  4
	and.b	regA,d1					*  4
	lsl.b	#2,d1					* 
	
	;-- �w��ۯ�(��{)�͕\�ɏo�Ă��邩?
	cmp.w	(a1),d0					* 
	bne.s	@f					* 
	
	;-- �w��ۯ�(�g��)�͕\�ɏo�Ă��邩?
	cmp.w	(a0,d0.w),d1				* 
	bne.s	@f					* 
	
	;-- �\���ް���ǂݍ���
	movea.l	regHL,a0				* 
	move.b	(a0),regA				* 
	
	FETCH						* 
	
	
	;-- ���̽ۯĂ���ǂݍ���
@@:
	;-- �ۯĊǗ�ð��ق̱��ڽ
	or.b	d1,d0					*  4
	adda.w	d0,a0					*  8
	
	;-- ��������؂̏ꍇ�͓ǂݍ��܂Ȃ�
	tst.b	SLOTINFO_MEMTYPE(a0)			* 
	bmi.s	@f					* 
	

;!!!!! 8KB �P�ʂɕ����������߁A���̃`�F�b�N���K�v

	;-- ��؂̱��ڽ
	movea.l	SLOTINFO_MEMADR_Low(a0),a1		* 
	
	;-- �̾�Čv�Z
	move.w	regHL,d0				*  4
	andi.w	#%0011_1111_1111_1111,d0		*  8
	
	;-- �ǂݍ���
	move.b	(a1,d0.w),regA				* 
	
@@:
	FETCH						* 

