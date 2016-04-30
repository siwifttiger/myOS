#include <stdio.h>
void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

/* ���͓����\�[�X�t�@�C���ɏ����Ă����Ă��A��`����O�Ɏg���̂Ȃ�A
	����ς�錾���Ă����Ȃ��Ƃ����Ȃ��B */

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
/********************
vram:���ڷ����Դ��ַ
xsize:һ�����صĸ���
c:Ԥ���趨�õĵ�ɫ���Ӧ����ɫ���
x0,y0:�������Ͻ�����
x1,y1:�������½�����
*********************/
void boxfill8(unsigned char* vram, int xsize, unsigned char c,int x0, int y0, int x1, int y1);
void init_screen(int xsize,int ysize, char* vram);
void putfont8(char *vram,int xsize,int x, int y,char c, char* font);
void putsfont8_asc(char *vram, int xsize, int x, int y, char c, unsigned char* s); //��ʾ�ַ���
void init_mouse_cursor8(char *mouse, char bc); //��ʼ�����ͼ��
/*vram���Դ��ַ
vxsizee��ÿ�����ظ���
pxsize��pysize����Ҫ��ʾ��ͼ���Ĵ�С
px0��py0��ͼ����ʾ��λ��
buf��������Ӧ����ɫ��Ϣ
bxsize����pxsize������ͬ*/
void putblock8_8(char *vram, int vxsize, int pxsize, int pysize,
		 int px0, int py0, char *buf, int bxsize);
/*��������*/
extern char hankaku[4096];

/*������ɫ���*/
#define COLO8_BLACK             0
#define COLO8_BRIGHT_RED        1
#define COLO8_BRIGHT_GREEN      2
#define COLO8_BRIGHT_YELLOW     3
#define COLO8_BRIGHT_BULUE      4
#define COLO8_BRIGHT_PURPLE     5
#define COLO8_BRIGHT_LIGHT_BULE 6
#define COLO8_WHITE             7
#define COLO8_BRIGHT_GRAY       8
#define COLO8_DARK_RED          9
#define COLO8_DARK_GREEN        10
#define COLO8_DARK_YELLOW       11
#define COLO8_DARK_BLUE         12
#define COLO8_DARK_PURPLE       13
#define COLO8_DARK_LIGHT_BLUE   14
#define COLO8_DARK_GRAY         15



struct Bootinfo{
	char cyls,leds,vmode,reserve;
	short scrnx,scrny;
	char *vram;
};

void HariMain(void)
{
	
	struct Bootinfo *bootinfo = (struct Bootinfo*)0x0ff0;
	char s[40];
	char mcursor[256];
	int mx,my;
	mx = (bootinfo->scrnx-16) / 2;
	my = (bootinfo->scrny - 28 - 16) / 2;
	init_palette();

	init_screen(bootinfo->scrnx,bootinfo->scrny,bootinfo->vram);
	init_mouse_cursor8(mcursor,COLO8_DARK_LIGHT_BLUE);

	sprintf(s,"scrnx = %d",bootinfo->scrnx);
	putblock8_8(bootinfo->vram,bootinfo->scrnx,16,16,mx,my,mcursor,16);
	putsfont8_asc(bootinfo->vram,bootinfo->scrnx,16,64,COLO8_WHITE,s);
	for (;;) {
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:�� */
		0xff, 0x00, 0x00,	/*  1:���邢�� */
		0x00, 0xff, 0x00,	/*  2:���邢�� */
		0xff, 0xff, 0x00,	/*  3:���邢���F */
		0x00, 0x00, 0xff,	/*  4:���邢�� */
		0xff, 0x00, 0xff,	/*  5:���邢�� */
		0x00, 0xff, 0xff,	/*  6:���邢���F */
		0xff, 0xff, 0xff,	/*  7:�� */
		0xc6, 0xc6, 0xc6,	/*  8:���邢�D�F */
		0x84, 0x00, 0x00,	/*  9:�Â��� */
		0x00, 0x84, 0x00,	/* 10:�Â��� */
		0x84, 0x84, 0x00,	/* 11:�Â����F */
		0x00, 0x00, 0x84,	/* 12:�Â��� */
		0x84, 0x00, 0x84,	/* 13:�Â��� */
		0x00, 0x84, 0x84,	/* 14:�Â����F */
		0x84, 0x84, 0x84	/* 15:�Â��D�F */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char ���߂́A�f�[�^�ɂ����g���Ȃ�����DB���ߑ��� */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* ���荞�݋��t���O�̒l���L�^���� */
	io_cli(); 					/* ���t���O��0�ɂ��Ċ��荞�݋֎~�ɂ��� */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* ���荞�݋��t���O�����ɖ߂� */
	return;
}


void boxfill8(unsigned char* vram, int xsize, unsigned char c,int x0, int y0, int x1, int y1){
	int x,y;
	for(y=y0; y <=y1; y++){
		for(x=x0;x <= x1; x++){
			vram[y*xsize + x] = c;
		}
	}
	return;
}
/*varm :�Դ��ʼλ��
  xsize:1�е�����Ԫ�ظ���
  x��y: �ƶ��ַ���ʾ������*/
void putfont8(char* vram,int xsize, int x, int y, char c, char *font){
	int i;
	char *p; /*����ָ����Ӧ���ڴ��ַ*/
	char d;
	for(i = 0; i < 16; i++){
		p = vram + (y+i)*xsize +x;
		d = font[i];
		if((0x80 & d) != 0) p[0] = c;
		if((0x40 & d) != 0) p[1] = c;
		if((0x20 & d) != 0) p[2] = c;
		if((0x10 & d) != 0) p[3] = c;
		if((0x08 & d) != 0) p[4] = c;
		if((0x04 & d) != 0) p[5] = c;
		if((0x02 & d) != 0) p[6] = c;
		if((0x01 & d) != 0) p[7] = c;
	}
	return;
}

void putsfont8_asc(char* vram, int xsize, int x, int y, char c, unsigned char* s){
	for(;*s != 0x00; s++){
		putfont8(vram,xsize,x,y,c,hankaku + *s*16);
		x += 8;
	}
}

void init_screen(int xsize,int ysize,char* vram){

	boxfill8(vram, xsize, COLO8_DARK_LIGHT_BLUE,  0,         0,          xsize -  1, ysize - 29);
	boxfill8(vram, xsize, COLO8_BRIGHT_GRAY,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill8(vram, xsize, COLO8_WHITE ,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill8(vram, xsize, COLO8_BRIGHT_GRAY,  0,         ysize - 26, xsize -  1, ysize -  1);

	boxfill8(vram, xsize, COLO8_WHITE ,  3,         ysize - 24, 59,         ysize - 24);
	boxfill8(vram, xsize, COLO8_WHITE ,  2,         ysize - 24,  2,         ysize -  4);
	boxfill8(vram, xsize, COLO8_DARK_GRAY,  3,         ysize -  4, 59,         ysize -  4);
	boxfill8(vram, xsize, COLO8_DARK_GRAY, 59,         ysize - 23, 59,         ysize -  5);
	boxfill8(vram, xsize, COLO8_BLACK,  2,         ysize -  3, 59,         ysize -  3);
	boxfill8(vram, xsize, COLO8_BLACK, 60,         ysize - 24, 60,         ysize -  3);

	boxfill8(vram, xsize, COLO8_DARK_GRAY, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, COLO8_DARK_GRAY, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, COLO8_WHITE, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, COLO8_WHITE, xsize -  3, ysize - 24, xsize -  3, ysize -  3);
}


void init_mouse_cursor8(char *mouse, char bc)
/* ��ʼ�����ͼ����������Ӧ���ַ���ӦΪ��Ӧ����ɫ */
{
	static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (cursor[y][x] == '*') {
				mouse[y * 16 + x] = COLO8_BLACK;
			}
			if (cursor[y][x] == 'O') {
				mouse[y * 16 + x] = COLO8_WHITE;
			}
			if (cursor[y][x] == '.') {
				mouse[y * 16 + x] = bc;
			}
		}
	}
	return;
}

void putblock8_8(char *vram, int vxsize, int pxsize, int pysize,
		 int px0, int py0, char *buf, int bxsize)
{
	int x,y;
	for(y = 0; y < pysize; y++){
		for(x = 0; x < pxsize; x++){
			vram[(py0+y)*vxsize + px0 + x] = buf[y*bxsize + x];
		}
	}	
	return;
}
