void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
	int i; /* �ϐ��錾�Bi�Ƃ����ϐ��́A32�r�b�g�̐����^ */

	for (i = 0xa0000; i <= 0xaffff; i++) {  /*�Կ��ڴ� VRAM*/
		write_mem8(i, 14); /* MOV BYTE [i],14  ��ɫ */
	}

	for (;;) {
		io_hlt();
	}
}