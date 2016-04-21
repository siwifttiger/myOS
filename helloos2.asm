	org 0x7c00    ;程序装载地址
;以下程序指明FAT12格式的软盘

		jmp entry
		db 0x90
		DB		"HELLOIPL"		;启动区名称 8字节
		DW		512				;每个sector的大小 512字节
		DB		1				;簇（cluster）大小 1个扇区
		DW		1				;FAT起始位置
		DB		2				;FAT个数
		DW		224				;根目录大小
		DW		2880			;磁盘大小 2880sector
		DB		0xf0			;磁盘种类
		DW		9				;FAT长度
		DW		18				;1 track多少扇区
		DW		2				;磁头数
		DD		0				;不使用分区
		DD		2880			;重写磁盘大小
		DB		0,0,0x29		;固定
		DD		0xffffffff		;卷标
		DB		"Slef-OS    "	;磁盘名称 11字节
		DB		"FAT12   "		;磁盘格式名称 8字节
		RESB	18				;空18字节
	entry:
		mov ax,0
		mov ss,ax
		mov sp,0x7c00
		mov ds,ax
		mov es,ax
		
		mov si,msg
	putloop:
		mov al,byte[si]
		add si,1
		cmp al,0
		je fin
		mov ah,0x0e
		mov bx,15h
		int 0x10
		jmp putloop
	fin:
		hlt
		jmp fin
	msg:
		db 0x0a,0x0a
		db "Hello,world"
		db 0x0a
		db 0
	resb 0x1fe-($-$$)
	db 0x55,0xaa		

;启动区以外的输出

		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	4600
		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	1469432

