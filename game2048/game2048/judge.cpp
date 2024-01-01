#include"head.h"//变量在模块0声明，在主体被定义
#include"judge.h"

//检查是否赢得游戏
bool win_judge(int list[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (list[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}

//检查是否输掉游戏
bool lose_judge(int list[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 检查是否为0  
			if (list[i][j] == 0) {
				return false;
			}
			// 检查左右相邻数字是否相同  
			if (j > 0 && list[i][j] == list[i][j - 1]) {
				return false;
			}
			// 检查上下相邻数字是否相同  
			if (i > 0 && list[i][j] == list[i - 1][j]) {
				return false;
			}
		}
	}
	return true;
}

//防止终端立即关闭的函数
void killgame() {
	cout << "press enter to quit the game......" << endl;
	char ch;
	while (true) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == '\r') {
				return;
			}
		}
	}
}