void io_hlt(void);


void HariMain(void)
{
	int i; /* �ϐ��錾�Bi�Ƃ����ϐ��́A32�r�b�g�̐����^ */
	char *p;
	for (i = 0xa0000; i <= 0xaffff; i++) {  /*�Կ��ڴ� VRAM*/
		p = (char*)i; /* �����ַ*/
		*p = i & 0x0f; /*�����㣬ÿ��16λ ��ɫ�ͻ��ظ����֣�����ͼ������ʾ������*/
	}

	for (;;) {
		io_hlt();
	}
}
