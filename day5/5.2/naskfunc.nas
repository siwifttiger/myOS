; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; �I�u�W�F�N�g�t�@�C������郂�[�h	
[INSTRSET "i486p"]				; 486�̖��߂܂Ŏg�������Ƃ����L�q
[BITS 32]						; 32�r�b�g���[�h�p�̋@�B�����点��
[FILE "naskfunc.nas"]			; �\�[�X�t�@�C�������

		GLOBAL	_io_hlt, _io_cli, _io_sti, _io_stihlt		; ���̃v���O�����Ɋ܂܂��֐���
		global  _io_in8, _io_in16, _io_in32
		global  _io_out8, _io_out_16, _io_out32
		global  _io_load_eflags, _io_store_eflags
		


[SECTION .text]		; �I�u�W�F�N�g�t�@�C���ł͂���������Ă���v���O����������

_io_hlt:	; void io_hlt(void);
		HLT
		RET

_io_cli:       ;void io_cli(void);
		cli
		ret

_io_sti:       ;void io_sti(void)
		sti
		ret

_io_stihlt:    ;void io_stihlt(void)
		sti
		hlt
		ret
		
_io_in8:       ;int io_in8(int port)
		mov edx,[esp+4]    ;port
		mov eax,0
		in al,dx           ;����ֵ�ڼĴ���al��
		ret

_io_in16:      ; int io_in8(int port)
	       mov edx,[esp+4]     ;port
	       mov eax,0  
	       in ax,dx            ;����ֵ�ڼĴ���ax��
	       ret
	       
_io_in32:      ;int io_in32(int port)
	       mov edx,[esp+4]
	       in eax,dx
	       ret
	       
_io_out8:     ;void io_out8(int port, int data)   ;���˸о������data�����char���ͣ�����8λ��Ҫ��
		mov edx,[esp+4]   ;port
		mov al,[esp+8]   ;data
		out dx,al
		ret

_io_out16:    ;void io_out16(int port, int data)
		mov edx,[esp+4]    ;port
		mov eax,[esp+8]     ;data
		out dx,ax
		ret

_io_out32:    ;void  io_out32(int port, int data)  ;˵ʵ����ʱû�㶮16λ��32λ���������ģ��Ӵ����Ͽ���Ч��������һ����
						   ;��Ϊout�Ĵ�������dx
	      mov edx,[esp+4]
	      mov eax,[esp+8]
	      out dx,eax
	      ret
_io_load_eflags:     ;int io_load_eflags(void)
		pushfd       ;push eflags
		pop eax      ;�������eax�Ĵ�����
		ret


_io_store_eflags:       ;void io_store_eflags(int eflags)          ;һ��ʼ ��eflags��С��д����elfags��һֱ��ʾ����������ͼ��������2��Сʱ��bug�����������Ӱ���������
		mov eax,[esp+4]   ;eflags
		push  eax
		popfd  
		ret 
						   
	       
		
