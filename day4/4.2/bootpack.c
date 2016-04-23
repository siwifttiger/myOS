void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
	int i; /* 曄悢愰尵丅i偲偄偆曄悢偼丄32價僢僩偺惍悢宆 */

	for (i = 0xa0000; i <= 0xaffff; i++) {  /*显卡内存 VRAM*/
		write_mem8(i, i & 0x0f); /*与运算，每隔16位 颜色就会重复出现，条纹图案就显示出来了*/
	}

	for (;;) {
		io_hlt();
	}
}
