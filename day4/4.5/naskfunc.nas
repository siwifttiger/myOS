; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; オブジェクトファイルを作るモード	
[INSTRSET "i486p"]				; 486の命令まで使いたいという記述
[BITS 32]						; 32ビットモード用の機械語を作らせる
[FILE "naskfunc.nas"]			; ソースファイル名情報

		GLOBAL	_io_hlt, _io_cli, _io_sti, _io_stihlt		; このプログラムに含まれる関数名
		global  _io_in8, _io_in16, _io_in32
		global  _io_out8, _io_out_16, _io_out32
		global  _io_load_eflags, _io_store_eflags
		


[SECTION .text]		; オブジェクトファイルではこれを書いてからプログラムを書く

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
		in al,dx           ;ｷｵｻﾘﾖｵﾔﾚｼﾄｴ貳�alﾖﾐ
		ret

_io_in16:      ; int io_in8(int port)
	       mov edx,[esp+4]     ;port
	       mov eax,0  
	       in ax,dx            ;ｷｵｻﾘﾖｵﾔﾚｼﾄｴ貳�axﾖﾐ
	       ret
	       
_io_in32:      ;int io_in32(int port)
	       mov edx,[esp+4]
	       in eax,dx
	       ret
	       
_io_out8:     ;void io_out8(int port, int data)   ;ｸ�ﾈﾋｸﾐｾ�ﾕ簑�ｵﾄdataﾗ�ｺﾃﾓﾃcharﾀ獎ﾍ｣ｬｷ�ｺﾏ8ﾎｻｵﾄﾒｪﾇ�
		mov edx,[esp+4]   ;port
		mov al,[esp+8]   ;data
		out dx,al
		ret

_io_out16:    ;void io_out16(int port, int data)
		mov edx,[esp+4]    ;port
		mov eax,[esp+8]     ;data
		out dx,ax
		ret

_io_out32:    ;void  io_out32(int port, int data)  ;ﾋｵﾊｵｻｰﾔﾝﾊｱﾃｻｸ羝ｮ16ﾎｻｺﾍ32ﾎｻｵﾄﾇ�ｱ�ﾔﾚﾄﾄ｣ｬｴﾓｴ�ﾂ�ﾉﾏｿｴﾀｴﾐｧｹ�ｺﾃﾏ�ﾊﾇﾒｻﾑ�ｵﾄ
						   ;ﾒ�ﾎｪoutｼﾄｴ貳�ｶｼﾊﾇdx
	      mov edx,[esp+4]
	      mov eax,[esp+8]
	      out dx,eax
	      ret
_io_load_eflags:     ;int io_load_eflags(void)
		pushfd       ;push eflags
		pop eax      ;ｽ盪�ｴ贇ﾚeaxｼﾄｴ貳�ﾖﾐ
		ret


_io_store_eflags:       ;void io_store_eflags(int eflags)          ;ﾒｻｿｪﾊｼ ｰﾑeflagsｲｻﾐ｡ﾐﾄﾐｴｳﾉﾁﾋelfags｣ｬﾒｻﾖｱﾏﾔﾊｾｲｻｳ�ﾀｴﾌ�ﾎﾆﾍｼｰｸ｣ｬﾕﾒﾁﾋ2ｸ�ﾐ｡ﾊｱｵﾄbug｡｣｡｣｡｣｡｣｡｣ｿﾓｰ｡｣｡｣｡｣｡｣｡
		mov eax,[esp+4]   ;eflags
		push  eax
		popfd  
		ret 
						   
	       
		
