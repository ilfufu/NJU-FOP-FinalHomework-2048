#include"head.h"//变量在模块0声明，在主体被定义
#include"movement.h"

//上移函数
void up(int list[4][4]) {
	score--;
	for (int n = 1; n <= 3; n++) {//类似冒泡方法，一层层往下套，下同，不多赘述
		for (int j = n; j > 0; j--) {
			for (int i = 0; i <= 3; i++) {
				if (list[j][i] == 0) {
					continue;//0不必移动
				}
				else if (list[j - 1][i] == 0) {
					swap(list[j - 1][i], list[j][i]);//上为零下不为，上下交换
				}
				else if (list[j - 1][i] == list[j][i]) {
					score += list[j][i];//加分
					list[j - 1][i] *= 2;//合并
					list[j][i] = 0;//重置
				}
			}
		}
	}
}

//下移函数
void down(int list[4][4]) {
	score--;
	for (int n = 2; n >= 0; n--) {
		for (int j = n; j < 3; j++) {
			for (int i = 0; i <= 3; i++) {
				if (list[j][i] == 0) {
					continue;//0不必移动
				}
				else if (list[j + 1][i] == 0) {
					swap(list[j + 1][i], list[j][i]);//下为零上不为，上下交换
				}
				else if (list[j + 1][i] == list[j][i]) {
					score += list[j][i];//加分
					list[j + 1][i] *= 2;//合并
					list[j][i] = 0;//重置
				}
			}
		}
	}
}

//左移函数
void left(int list[4][4]) {
	score--;
	for (int n = 1; n <= 3; n++) {
		for (int i = n; i > 0; i--) {
			for (int j = 0; j <= 3; j++) {
				if (list[j][i] == 0) {
					continue;//0不必移动
				}
				else if (list[j][i - 1] == 0) {
					swap(list[j][i - 1], list[j][i]);//左为零右不为，左右交换
				}
				else if (list[j][i - 1] == list[j][i]) {
					score += list[j][i];//加分
					list[j][i - 1] *= 2;//合并
					list[j][i] = 0;//重置
				}
			}
		}
	}
}

//右移函数
void right(int list[4][4]) {
	score--;
	for (int n = 2; n >= 0; n--) {
		for (int i = n; i < 3; i++) {
			for (int j = 0; j <= 3; j++) {
				if (list[j][i] == 0) {
					continue;//0不必移动
				}
				else if (list[j][i + 1] == 0) {
					swap(list[j][i + 1], list[j][i]);//右为零左不为，左右交换
				}
				else if (list[j][i + 1] == list[j][i]) {
					score += list[j][i];//加分
					list[j][i + 1] *= 2;//合并
					list[j][i] = 0;//重置
				}
			}
		}
	}
}

//interesting功能开始
//helper函数，功能是随机抽取一个数翻倍，但会扣除至多2048分
void H(int list[4][4]) {
	random_device rd;//种子
	mt19937 generator(rd());//MT随机数
	uniform_int_distribution<int> dist(0, 3);//随机生成0123
	int r = dist(generator);
	int c = dist(generator);
	list[r][c] *= 2;
	cout << "###The number in ("<<r<<","<<c<<") plus 2!" << endl;
	uniform_int_distribution<int> d2(0, 11);//随机生成0~11
	int ran = d2(generator);
	int d = pow(2, ran);
	score -= d;
	cout << "###Your score decrease " << d << "!" << endl;
}

//worsen函数，功能是当前最大值减半
// 要是只有2，这时触发不了最大值减半，故只能从你的分数里减去2048了
// 但是一旦触发最大值减半，score会加上当前最大值数字的两倍！
void W(int list[4][4]) {
	int max_row = 0, max_col = 0;
	int max = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (list[i][j] > max) {
				max = list[i][j];
				max_row = i;
				max_col = j;
			}
		}
	}
	if (max <= 2) {
		score -= 2048;
		cout << "###The worsener did not function normally!2048 was stolen from yourscore!!" << endl;
		return;
	}
	else {
		score += 2*list[max_row][max_col];
		list[max_row][max_col] /= 2;
		cout << "###The number in (" << max_row << "," << max_col << ")/=2, but your score add 2*that!!" << endl;
	}
}
//interesting功能结束

//获取移动方向并导向对应移动函数
void check_direction() {
	static int count1 = 1;
	static int count2 = 1;
	//四个阶段的句子不同
	if (count1 == 1 && count2 == 1) {
		cout << "press direction keys to move the numbers.maybe press other keys will (H)elp or will (W)orsen the situation?" << endl;
	}
	else if (count2 == 1) {
		cout << "press direction keys to move the numbers.maybe press certain key will (W)orsen the situation?" << endl;
	}
	else if (count1 == 1) {
		cout << "press direction keys to move the numbers.maybe press certain key will (H)elp?" << endl;
	}
	else {
		cout << "press keys to operate the numbers." << endl;
	}
	char ch;
	while (true) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 72) {
				up(list);
				break;
			}
			else if (ch == 80) {
				down(list);
				break;
			}
			else if (ch == 75) {
				left(list);
				break;
			}
			else if (ch == 77) {
				right(list);
				break;
			}
			//interesing部分
			else if (ch == 'h'||ch=='H') {
				H(list);
				//只会在第一次发现时告知你规则
				if (count1 == 1) {
					count1--;
					cout << "********" << endl;
					cout << "You've found the first hidden rule!" << endl;
					cout << "Press 'h' to call helper,it will randomly multiple 2 to a number."<<endl;
					cout << "But it will also randomly decrease your score(at most 2048)."<<endl;
					cout << "********" << endl;
				}
				break;
			}
			else if (ch == 'w'||ch=='W') {
				W(list);
				//同上
				if (count2 == 1) {
					count2--;
					cout << "********" << endl;
					cout << "You've found the second hidden rule!" << endl;
					cout << "Press 'w' to call worsener,which will make (your largest number)/2 but add 2*it to your score!" << endl;
					cout << "But if you only have 2 and 0,the worsener will not function normally." << endl;
					cout << "Attenton please:if worsener cannot function normally,it will steal 2048 from your score!" << endl;
					cout << "********" << endl;
				}
				break;
			}
		}
	}
}