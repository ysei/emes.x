;----------------------------------------------------------------------------------------------
; MSX Emulator for X680x0 - emes.x
;
;    Copyright 1997-1998 nir
;


	.xdef _SegmentsMemMap,_MemoryMapperTbl
	.xdef _IndexMemoryMapper
	
	SET_OFFSET_IO	IndexMemoryMapper

	.even


*----------------------------------------------------------------------------------------------

*-- �������}�b�p�̃Z�O�����g��
_SegmentsMemMap:
	.dc.w	0

	.rept 128
	.dc.l	0
	.endm
_MemoryMapperTbl:
	.rept 128
	.dc.l	0
	.endm

;-- �X���b�g�Ǘ��e�[�u���̃������}�b�p�̈ʒu
_IndexMemoryMapper:
	.dc.w	0

