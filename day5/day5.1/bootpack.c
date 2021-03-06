void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

/* 実は同じソースファイルに書いてあっても、定義する前に使うのなら、
	やっぱり宣言しておかないといけない。 */

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
/********************
vram:ﾓﾃﾓﾚｷﾃﾎﾊﾏﾔｴ豬ﾘﾖｷ
xsize:ﾒｻﾐﾐﾏ�ﾋﾘｵﾄｸ�ﾊ�
c:ﾔ､ﾏﾈﾉ雜ｨｺﾃｵﾄｵ�ﾉｫｰ蠍ﾔﾓｦｵﾄﾑﾕﾉｫﾐ�ｺﾅ
x0,y0:ｾﾘﾐﾎﾗ�ﾉﾏｽﾇﾗ�ｱ�
x1,y1:ｾﾘﾐﾎﾓﾒﾏﾂｽﾇﾗ�ｱ�
*********************/
void boxfill8(unsigned char* vram, int xsize, unsigned char c,int x0, int y0, int x1, int y1);
void init_screen(int xsize,int ysize, char* vram);
void putfont8(char *vram,int xsize,int x, int y,char c, char* font);


/*ｶｨﾒ衽ﾕﾉｫﾐ�ｺﾅ*/
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
	static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
	};

	init_palette();

	init_screen(bootinfo->scrnx,bootinfo->scrny,bootinfo->vram);
	putfont8(bootinfo->vram,bootinfo->scrnx,10,10,COLO8_WHITE,font_A);

	for (;;) {
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:黒 */
		0xff, 0x00, 0x00,	/*  1:明るい赤 */
		0x00, 0xff, 0x00,	/*  2:明るい緑 */
		0xff, 0xff, 0x00,	/*  3:明るい黄色 */
		0x00, 0x00, 0xff,	/*  4:明るい青 */
		0xff, 0x00, 0xff,	/*  5:明るい紫 */
		0x00, 0xff, 0xff,	/*  6:明るい水色 */
		0xff, 0xff, 0xff,	/*  7:白 */
		0xc6, 0xc6, 0xc6,	/*  8:明るい灰色 */
		0x84, 0x00, 0x00,	/*  9:暗い赤 */
		0x00, 0x84, 0x00,	/* 10:暗い緑 */
		0x84, 0x84, 0x00,	/* 11:暗い黄色 */
		0x00, 0x00, 0x84,	/* 12:暗い青 */
		0x84, 0x00, 0x84,	/* 13:暗い紫 */
		0x00, 0x84, 0x84,	/* 14:暗い水色 */
		0x84, 0x84, 0x84	/* 15:暗い灰色 */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char 命令は、データにしか使えないけどDB命令相当 */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* 割り込み許可フラグの値を記録する */
	io_cli(); 					/* 許可フラグを0にして割り込み禁止にする */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* 割り込み許可フラグを元に戻す */
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
/*varm :ﾏﾔｴ豕�ﾊｼﾎｻﾖﾃ
  xsize:1ﾐﾐｵﾄﾏ�ﾋﾘﾔｪﾋﾘｸ�ﾊ�
  x｣ｬy: ﾖﾆｶｨﾗﾖｷ�ﾏﾔﾊｾｵﾄﾗ�ｱ�*/
void putfont8(char* vram,int xsize, int x, int y, char c, char *font){
	int i;
	char *p; /*ﾓﾃﾓﾚﾖｸｶｨｶﾔﾓｦｵﾄﾄﾚｴ豬ﾘﾖｷ*/
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

