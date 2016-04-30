; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; 僆僽僕僃僋僩僼傽僀儖傪嶌傞儌乕僪	
[INSTRSET "i486p"]				; 486偺柦椷傑偱巊偄偨偄偲偄偆婰弎
[BITS 32]						; 32價僢僩儌乕僪梡偺婡夿岅傪嶌傜偣傞
[FILE "naskfunc.nas"]			; 僜乕僗僼傽僀儖柤忣曬

		GLOBAL	_io_hlt, _io_cli, _io_sti, _io_stihlt		; 偙偺僾儘僌儔儉偵娷傑傟傞娭悢柤
		global  _io_in8, _io_in16, _io_in32
		global  _io_out8, _io_out_16, _io_out32
		global  _io_load_eflags, _io_store_eflags
		


[SECTION .text]		; 僆僽僕僃僋僩僼傽僀儖偱偼偙傟傪彂偄偰偐傜僾儘僌儔儉傪彂偔

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
		in al,dx           ;返回值在寄存器al中
		ret

_io_in16:      ; int io_in8(int port)
	       mov edx,[esp+4]     ;port
	       mov eax,0  
	       in ax,dx            ;返回值在寄存器ax中
	       ret
	       
_io_in32:      ;int io_in32(int port)
	       mov edx,[esp+4]
	       in eax,dx
	       ret
	       
_io_out8:     ;void io_out8(int port, int data)   ;个人感觉这里的data最好用char类型，符合8位的要求
		mov edx,[esp+4]   ;port
		mov al,[esp+8]   ;data
		out dx,al
		ret

_io_out16:    ;void io_out16(int port, int data)
		mov edx,[esp+4]    ;port
		mov eax,[esp+8]     ;data
		out dx,ax
		ret

_io_out32:    ;void  io_out32(int port, int data)  ;说实话暂时没搞懂16位和32位的区别在哪，从代码上看来效果好像是一样的
						   ;因为out寄存器都是dx
	      mov edx,[esp+4]
	      mov eax,[esp+8]
	      out dx,eax
	      ret
_io_load_eflags:     ;int io_load_eflags(void)
		pushfd       ;push eflags
		pop eax      ;结果存在eax寄存器中
		ret


_io_store_eflags:       ;void io_store_eflags(int eflags)          ;一开始 把eflags不小心写成了elfags，一直显示不出来条纹图案，找了2个小时的bug。。。。。坑啊！！！！
		mov eax,[esp+4]   ;eflags
		push  eax
		popfd  
		ret 
						   
	       
		
