#include"head.h"//变量在模块0声明，在主体被定义
#include"random.h"

//开局介绍函数
void start() {
	cout << "welcome to 2048 games!" << endl;
	cout << "you can see we have a GRAPHIC window to SHOW,and a CONSOLE window to INTRODUCE!" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "now let us go through the rules of the game:" << endl;
	cout << "1. press direction keys to move numbers,if the two are same numbers,they will add up." << endl;
	cout << "2. if the number is 0,then the moved numbers will replace 0." << endl;
	cout << "3. if the two are not 0 and are different,they will not be moved." << endl;
	cout << "4. each time you move,your score will minus 1,and each time you add up numbers,your score will plus that number." << endl;
	cout << "5. your goal is to add and get the number of 2048,and try to get help score!" << endl;
	cout << "*6. if your final score is larger than 10000,you will get certain special result!!!" << endl;
	cout << endl;
	cout << endl;
	cout << "attention please:  press some special keys may (H)elp or (W)orsen the situation  " << endl;
	cout << endl;
	cout << endl;
	cout << "now let us start.enjoy it!" << endl;
	cout << endl;
	cout << endl;
}

//展示函数
void print_list(int list[4][4]) {
	cout << "combine the number to reach 2048!" << endl;
	cout << "current chessboard:" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << left << setw(5) << list[i][j] << " ";
		}
		cout << endl;
	}
	cout << "current score:" << score << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}


//初始化函数；
void initialize(int list[4][4]) {
	int protect = 1;
	random_device rd;//获取随机种子
	mt19937 generator(rd());//创建MT随机数生成器
	uniform_int_distribution<int> dist1(0, 1);//均匀生成01
	int index[2] = { 0,3 };
	int row1 = index[dist1(generator)];
	int col1 = index[dist1(generator)];
	list[row1][col1] = 2;
	uniform_int_distribution<int> dist2(0, 3);//均匀生成0123
	int row2 = dist2(generator);
	int col2 = dist2(generator);
	//防重复
	while (row1 == row2 && col1 == col2) {
		row2 = dist2(generator);
		col2 = dist2(generator);
		protect++;
		if (protect > 100) {
			list[1][1] = 2;//卡死会默认给(1,1)位置赋值2以代替第二个随机出现的2
			print_list(list);
			return;
		}//防止卡死循环，伪随机以保证函数正常运行
	}
	list[row2][col2] = 2;
	print_list(list);//初始完打印
}

//随机24函数(运用mt19937与二项分布)
void generate(int list[4][4]) {
	//先判断有无生成必要
	bool judge = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (list[i][j] == 0) {
				judge = false;
			}
		}
	}
	if (judge) {
		print_list(list);//结束本轮后打印
		return;//停下函数
	}
	random_device rd;//获取随机种子
	mt19937 generator(rd());//创建MT随机数生成器
	bernoulli_distribution dist(0.8);//4:1
	int num = dist(generator) ? 2 : 4;
	uniform_int_distribution<int> rowDist(0, 3);
	uniform_int_distribution<int> colDist(0, 3); //均匀生成0123
	int row = rowDist(generator);
	int col = colDist(generator);
	//核查是否非0
	while (list[row][col] != 0) {
		row = rowDist(generator);
		col = colDist(generator);
	}
	list[row][col] = num;
	print_list(list);//结束本轮后打印
}