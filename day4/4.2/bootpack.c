void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
	int i; /* �ϐ��錾�Bi�Ƃ����ϐ��́A32�r�b�g�̐����^ */

	for (i = 0xa0000; i <= 0xaffff; i++) {  /*�Կ��ڴ� VRAM*/
		write_mem8(i, i & 0x0f); /*�����㣬ÿ��16λ ��ɫ�ͻ��ظ����֣�����ͼ������ʾ������*/
	}

	for (;;) {
		io_hlt();
	}
}
