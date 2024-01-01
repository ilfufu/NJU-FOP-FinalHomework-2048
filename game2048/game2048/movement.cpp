#include"head.h"//������ģ��0�����������屻����
#include"movement.h"

//���ƺ���
void up(int list[4][4]) {
	score--;
	for (int n = 1; n <= 3; n++) {//����ð�ݷ�����һ��������ף���ͬ������׸��
		for (int j = n; j > 0; j--) {
			for (int i = 0; i <= 3; i++) {
				if (list[j][i] == 0) {
					continue;//0�����ƶ�
				}
				else if (list[j - 1][i] == 0) {
					swap(list[j - 1][i], list[j][i]);//��Ϊ���²�Ϊ�����½���
				}
				else if (list[j - 1][i] == list[j][i]) {
					score += list[j][i];//�ӷ�
					list[j - 1][i] *= 2;//�ϲ�
					list[j][i] = 0;//����
				}
			}
		}
	}
}

//���ƺ���
void down(int list[4][4]) {
	score--;
	for (int n = 2; n >= 0; n--) {
		for (int j = n; j < 3; j++) {
			for (int i = 0; i <= 3; i++) {
				if (list[j][i] == 0) {
					continue;//0�����ƶ�
				}
				else if (list[j + 1][i] == 0) {
					swap(list[j + 1][i], list[j][i]);//��Ϊ���ϲ�Ϊ�����½���
				}
				else if (list[j + 1][i] == list[j][i]) {
					score += list[j][i];//�ӷ�
					list[j + 1][i] *= 2;//�ϲ�
					list[j][i] = 0;//����
				}
			}
		}
	}
}

//���ƺ���
void left(int list[4][4]) {
	score--;
	for (int n = 1; n <= 3; n++) {
		for (int i = n; i > 0; i--) {
			for (int j = 0; j <= 3; j++) {
				if (list[j][i] == 0) {
					continue;//0�����ƶ�
				}
				else if (list[j][i - 1] == 0) {
					swap(list[j][i - 1], list[j][i]);//��Ϊ���Ҳ�Ϊ�����ҽ���
				}
				else if (list[j][i - 1] == list[j][i]) {
					score += list[j][i];//�ӷ�
					list[j][i - 1] *= 2;//�ϲ�
					list[j][i] = 0;//����
				}
			}
		}
	}
}

//���ƺ���
void right(int list[4][4]) {
	score--;
	for (int n = 2; n >= 0; n--) {
		for (int i = n; i < 3; i++) {
			for (int j = 0; j <= 3; j++) {
				if (list[j][i] == 0) {
					continue;//0�����ƶ�
				}
				else if (list[j][i + 1] == 0) {
					swap(list[j][i + 1], list[j][i]);//��Ϊ����Ϊ�����ҽ���
				}
				else if (list[j][i + 1] == list[j][i]) {
					score += list[j][i];//�ӷ�
					list[j][i + 1] *= 2;//�ϲ�
					list[j][i] = 0;//����
				}
			}
		}
	}
}

//interesting���ܿ�ʼ
//helper�����������������ȡһ��������������۳�����2048��
void H(int list[4][4]) {
	random_device rd;//����
	mt19937 generator(rd());//MT�����
	uniform_int_distribution<int> dist(0, 3);//�������0123
	int r = dist(generator);
	int c = dist(generator);
	list[r][c] *= 2;
	cout << "###The number in ("<<r<<","<<c<<") plus 2!" << endl;
	uniform_int_distribution<int> d2(0, 11);//�������0~11
	int ran = d2(generator);
	int d = pow(2, ran);
	score -= d;
	cout << "###Your score decrease " << d << "!" << endl;
}

//worsen�����������ǵ�ǰ���ֵ����
// Ҫ��ֻ��2����ʱ�����������ֵ���룬��ֻ�ܴ���ķ������ȥ2048��
// ����һ���������ֵ���룬score����ϵ�ǰ���ֵ���ֵ�������
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
//interesting���ܽ���

//��ȡ�ƶ����򲢵����Ӧ�ƶ�����
void check_direction() {
	static int count1 = 1;
	static int count2 = 1;
	//�ĸ��׶εľ��Ӳ�ͬ
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
			//interesing����
			else if (ch == 'h'||ch=='H') {
				H(list);
				//ֻ���ڵ�һ�η���ʱ��֪�����
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
				//ͬ��
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