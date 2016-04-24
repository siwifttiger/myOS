# myOS
ubuntu下30天自制操作系统（#吹牛逼的，不知道要多少天）
#学习ing!!!
这是一张day3的图片
![image](https://github.com/siwifttiger/myOS/image/day3.png)
##day3文件说明
###test.asm 和 test2.asm分别为两个用户程序，test.asm显示hello world test2.asm 设置显卡模式
###两个test的bin文件是编译出来的二进制文件，要写入软盘
###WangOS_day3_a/b/c/d.asm 分别为4个不同的引导程序   最终用到的是d,读入一张软盘10个柱面正反两面的所有扇区
(两个用户程序不是一起由引导程序加载的),我直接将用户程序的bin文件写入到软盘的第二个扇区，所以用户程序直接加载到内存0x8200处 ，而不是加上0x4200的文件位置偏移量，暂时还不知道这会不会对以后的开发造成影响，因为linux直接用dd命令写软盘很方便，制作软盘也相对方便。这和书上有区别

####浪费了两天时间，还是没能建立起自己在linux下的开发环境，后来利用作者的工具，只用简单修改以下Makefile就能轻松运行，简直想死，还是用作者的工具进行开发吧，等读完一遍后试试自己来搭建环境

day4 的一张截图
![day4](https://github.com/siwifttiger/myOS/blob/master/image/day4.5.png)
