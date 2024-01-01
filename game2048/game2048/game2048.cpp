#include<graphics.h>//easyx图形库
#include"head.h"//模块0
#include"random.h"//模块1
#include"movement.h"//模块2
#include"judge.h"//模块3

#define GRID_W 100//每格边长
#define MYSIZE 4//格数
#define INTEVAL 15//间隔
#define WIN_SIZE MYSIZE*GRID_W+INTEVAL*(MYSIZE+1)//窗口边长
enum Color {
	//枚举格子颜色
	zero=RGB(205, 193, 180), //0的颜色
	twoTo1=RGB(238, 228, 218),//2的颜色
	twoTo2=RGB(237, 224, 200),//4的颜色
	twoTo3=RGB(242, 177, 121),//8的颜色
	twoTo4=RGB(245, 149, 99),//16的颜色
	twoTo5=RGB(246, 124, 95),//32的颜色
	twoTo6=RGB(246, 94, 59),//64的颜色
	twoTo7=RGB(242, 177, 121),//128的颜色
	twoTo8=RGB(237, 204, 97),//256的颜色
	twoTo9=RGB(255, 0, 128),//512的颜色
	twoTo10=RGB(145, 0, 72),//1024的颜色
	twoTo11=RGB(242, 17, 158),//2048的颜色
	back=RGB(187, 173, 160),//背景颜色
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };


//在主体定义全局变量score和list，全局声明在模块0头文件里
int list[4][4] = { 0 };
int score = 0;

//简单的图形化函数
void gamedraw() {
	setbkcolor(RGB(187,173,160));//设置背景颜色
	cleardevice();
	//分格并设置填充颜色
	for (int i = 0; i < MYSIZE; i++) {
		for (int j = 0; j < MYSIZE; j++) {
			int x=j*GRID_W+(j+1)*INTEVAL;
			int y=i*GRID_W+(i+1)*INTEVAL;
			int index;
			if (list[i][j] == 0) {
				index = 0;
			}
			else {
				index = (int)log2((double)list[i][j]);
			}
			COLORREF tcolor=arr[index];
			setfillcolor(tcolor);
			solidroundrect(x, y, x + GRID_W, y + GRID_W,10,10);

			int temp= list[i][j];
			if(temp!=0){
				settextstyle(44, 0, "黑体");//字体
				setbkmode(TRANSPARENT);//文本背景透明
				settextcolor(RGB(119, 110, 120));//字体颜色
				//以下一大串是数字转字符串
				char str[10] = "";
				sprintf_s(str, "%d", temp);
				//文本居中
				int tw = textwidth(str);
				int th = textheight(str);
				int tx = (GRID_W - tw) / 2;
				int ty = (GRID_W - th) / 2;
				outtextxy(x + tx, y + ty, str);
			}
		}
	}
}

int main() {
	start();
	initialize(list);

	initgraph(WIN_SIZE, WIN_SIZE,SHOWCONSOLE);
	gamedraw();

	while ((!win_judge(list)) && (!lose_judge(list))) {
		check_direction();
		generate(list);
		gamedraw();
	}
	if (win_judge(list)) {
		cout << "Congratulations!You Win!!   Final Score:" << score << endl;
		if (score > 10000) {
			cout << "OHHHHHHHHH!Unbelievable Achievement!!!!!" << endl;
		}
	}
	else {
		cout << "You Lose,But Don't Feel Discouraged.Try Again!   Final Score:" << score << endl;
		if (score > 10000) {
			cout << "Glorious defeat!!!" << endl;
		}
	}
	killgame();
	closegraph();//关闭图形化界面
	return 0;
}