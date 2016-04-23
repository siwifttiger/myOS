void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
	int i; /* 変数宣言。iという変数は、32ビットの整数型 */

	for (i = 0xa0000; i <= 0xaffff; i++) {  /*ﾏﾔｿｨﾄﾚｴ� VRAM*/
		write_mem8(i, 14); /* MOV BYTE [i],14  ｻﾆﾉｫ */
	}

	for (;;) {
		io_hlt();
	}
}
