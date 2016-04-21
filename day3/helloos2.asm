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
		
		
;新增部分 读取软盘第2个扇区
		mov ax,0x0820
		mov es,ax                        ;es*16+bx
		mov ch,0	                 ;柱面0
		mov dh,0                         ;磁头0
		mov cl,2                         ;扇区2
		
		mov ah,0x02                      ;ah=0x02 读盘功能
		mov al,1                         ;读一个扇区
		mov bx,0                         ;es:bx = 缓冲地址 就是内存地址，从软盘读出的数据将要放到这个地址
		mov dl,0x00                      ;A驱动器
		int 0x13                         ;调用磁盘BIOS 0x13中断
		jc error                         ;进位标志是1的话，就跳转
						 ;如果能正常调用int 0x13中断读软盘的话，进位标志就是0
						 ;否则进位标志就是1（进位标志为FLACS.CF）
	fin:
		hlt                              ;如果正常加载成功的话，就finish 进入停机状态
		jmp fin
	error:
		mov si,msg
	putloop:
		mov al,byte[si]
		add si,1
		cmp al,0
		je fin                           ;输出完提示信息后，也进入停机
		mov ah,0x0e
		mov bx,15h
		int 0x10
		jmp putloop

	msg:
		db 0x0a,0x0a
		db "load error!"
		db 0x0a
		db 0
	resb 0x1fe-($-$$)
	db 0x55,0xaa		


;启动区以外的输出

		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	4600
		DB		0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
		RESB	1469432
