#include"head.h"//������ģ��0�����������屻����
#include"judge.h"

//����Ƿ�Ӯ����Ϸ
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

//����Ƿ������Ϸ
bool lose_judge(int list[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// ����Ƿ�Ϊ0  
			if (list[i][j] == 0) {
				return false;
			}
			// ����������������Ƿ���ͬ  
			if (j > 0 && list[i][j] == list[i][j - 1]) {
				return false;
			}
			// ����������������Ƿ���ͬ  
			if (i > 0 && list[i][j] == list[i - 1][j]) {
				return false;
			}
		}
	}
	return true;
}

//��ֹ�ն������رյĺ���
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