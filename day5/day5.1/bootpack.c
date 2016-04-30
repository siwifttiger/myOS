void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

/* 幚偼摨偠僜乕僗僼傽僀儖偵彂偄偰偁偭偰傕丄掕媊偡傞慜偵巊偆偺側傜丄
	傗偭傁傝愰尵偟偰偍偐側偄偲偄偗側偄丅 */

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
/********************
vram:用于访问显存地址
xsize:一行像素的个数
c:预先设定好的调色板对应的颜色序号
x0,y0:矩形左上角坐标
x1,y1:矩形右下角坐标
*********************/
void boxfill8(unsigned char* vram, int xsize, unsigned char c,int x0, int y0, int x1, int y1);
void init_screen(int xsize,int ysize, char* vram);
void putfont8(char *vram,int xsize,int x, int y,char c, char* font);


/*定义颜色序号*/
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
		0x00, 0x00, 0x00,	/*  0:崟 */
		0xff, 0x00, 0x00,	/*  1:柧傞偄愒 */
		0x00, 0xff, 0x00,	/*  2:柧傞偄椢 */
		0xff, 0xff, 0x00,	/*  3:柧傞偄墿怓 */
		0x00, 0x00, 0xff,	/*  4:柧傞偄惵 */
		0xff, 0x00, 0xff,	/*  5:柧傞偄巼 */
		0x00, 0xff, 0xff,	/*  6:柧傞偄悈怓 */
		0xff, 0xff, 0xff,	/*  7:敀 */
		0xc6, 0xc6, 0xc6,	/*  8:柧傞偄奃怓 */
		0x84, 0x00, 0x00,	/*  9:埫偄愒 */
		0x00, 0x84, 0x00,	/* 10:埫偄椢 */
		0x84, 0x84, 0x00,	/* 11:埫偄墿怓 */
		0x00, 0x00, 0x84,	/* 12:埫偄惵 */
		0x84, 0x00, 0x84,	/* 13:埫偄巼 */
		0x00, 0x84, 0x84,	/* 14:埫偄悈怓 */
		0x84, 0x84, 0x84	/* 15:埫偄奃怓 */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char 柦椷偼丄僨乕僞偵偟偐巊偊側偄偗偳DB柦椷憡摉 */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* 妱傝崬傒嫋壜僼儔僌偺抣傪婰榐偡傞 */
	io_cli(); 					/* 嫋壜僼儔僌傪0偵偟偰妱傝崬傒嬛巭偵偡傞 */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* 妱傝崬傒嫋壜僼儔僌傪尦偵栠偡 */
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
/*varm :显存初始位置
  xsize:1行的像素元素个数
  x，y: 制定字符显示的坐标*/
void putfont8(char* vram,int xsize, int x, int y, char c, char *font){
	int i;
	char *p; /*用于指定对应的内存地址*/
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

