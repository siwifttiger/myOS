void io_hlt(void);


void HariMain(void)
{
	int i; /* 変数宣言。iという変数は、32ビットの整数型 */
	char *p;
	for (i = 0xa0000; i <= 0xaffff; i++) {  /*ﾏﾔｿｨﾄﾚｴ� VRAM*/
		p = (char*)i; /* ｴ�ﾈ�ｵﾘﾖｷ*/
		*p = i & 0x0f; /*ﾓ�ﾔﾋﾋ罐ｬﾃｿｸ�16ﾎｻ ﾑﾕﾉｫｾﾍｻ瞶ﾘｸｴｳ�ﾏﾖ｣ｬﾌ�ﾎﾆﾍｼｰｸｾﾍﾏﾔﾊｾｳ�ﾀｴﾁﾋ*/
	}

	for (;;) {
		io_hlt();
	}
}
