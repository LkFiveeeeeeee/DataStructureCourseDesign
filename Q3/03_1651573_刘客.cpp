#include <iostream>
#include <random>
#include <vector>
#define SIZE 1000
using namespace std;

char initArray[] = { '#','0','0','0','0' };
//����·���ڵ�
struct Point {
	int x;
	int y;

	Point(int tx, int ty) {
		x = tx;
		y = ty;
	}

	Point() {

	}
};


Point judgeDirection(Point start, bool** judge);
//����ջ;
struct Stack {
	Point pVector[SIZE];
	int currentIndex;
	Stack() {
		currentIndex = 0;
	}
	void pop(Point& point) {
		point = pVector[--currentIndex];
	}
	void push(Point point) {
		pVector[currentIndex++] = point;
	}
	bool isEmpty() { return currentIndex == 0; }
};


void drawMap(char**map, bool**judge, int width, int height) {
	cout << "\n\n�Թ���ͼ\n\n";
	for (int i = 0; i < width; i++) {
		cout << "\t" << i << "��";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		cout << i << "��\t";
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1) {
				map[i][j] = initArray[0];
				judge[i][j] = false;
				cout << map[i][j] << "\t";
				continue;
			}
			if (j == 0 || j == width - 1) {
				//�����ͼԪ��
				map[i][j] = initArray[0];
				judge[i][j] = false;
				cout << map[i][j] << "\t";
				continue;
			}
			if (i == 1 && j == 1) {
				//�������;
				//�����ͼԪ��
				map[i][j] = 'S';
				judge[i][j] = true;
				cout << map[i][j] << "\t";
				continue;
			}
			if (j == width - 2 && i == height - 2) {
				//���ó���
				//�����ͼԪ��
				map[i][j] = 'E';
				judge[i][j] = true;
				cout << map[i][j] << "\t";
				continue;
			}
			//ͨ����������ɵ�ͼ�ϰ�
			map[i][j] = initArray[rand() % 5];
			map[i][j] == '#' ? judge[i][j] = false : judge[i][j] = true;
			cout << map[i][j] << "\t";
		}
		cout << "\n\n";
	}
}

bool searchForExitPath(char **map, bool ** judge, Stack& countStack) {
	Point start(1, 1);

	countStack.push(start);
	Point temp = start;
	while (!countStack.isEmpty()) {
		temp = judgeDirection(temp, judge);
		if (temp.x != -1 && temp.y != -1) {
			//��������ʾ�ҵ��˺��ǰ������
			if (map[temp.x][temp.y] == 'E') {
				countStack.push(temp);
				return true;
			}
			countStack.push(temp);
		}
		else {
			countStack.pop(temp);
		}
	}
	return false;
}



int main() {
	char **map;
	bool **judgeV;

	Stack countStack;
	srand((unsigned)time_t(NULL));
	int width, height;
	cout << "�������Թ��Ŀ�͸�(����ʾ�� 3 5,��͸߱������3����): ";
	cin >> width >> height;
	while (width <= 3 || height <= 3) {
		cout << "������������,�������������: ";
		cin >> width >> height;
	}
	map = new char*[height ];
	judgeV = new bool*[height ];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width + 1];
		judgeV[i] = new bool[width + 1];
	}
	drawMap(map, judgeV, width, height);
	if (searchForExitPath(map, judgeV, countStack)) {
		Point temp;
		Stack tempStack;
		while (!countStack.isEmpty()) {
			countStack.pop(temp);
			//ˢ�µ�ͼ��Ϣ;
			if (map[temp.x][temp.y] != 'S' && map[temp.x][temp.y] != 'E') {
				map[temp.x][temp.y] = 'X';
			}
			//��������һ��ջ,������·�߷���
			tempStack.push(temp);
		}
		cout << "\n\n";
		cout << "·����ͼ\n\n";
		for (int i = 0; i < width; i++) {
			cout << "\t" << i << "��";
		}
		cout << "\n\n";
		for (int i = 0; i < height; i++) {
			cout << i << "��\t";
			
			for (int j = 0; j < width; j++) {
				cout << map[i][j] << "\t";
			}
			cout << "\n\n";
		}
		cout << "�Թ�·��\n";
		//���ڻ���ͳ��
		int count = 1;
		tempStack.pop(temp);
		cout << "<" << temp.x << "," << temp.y << ">";
		while (!tempStack.isEmpty()) {
			cout << "----->";
			tempStack.pop(temp);
			cout << "<" << temp.x << "," << temp.y << ">";

			count++;
			if (count % 5 == 0) {
				cout << "\n";
			}
		}
	}
	else {
		cout << "\n\n���Թ���·���ߣ�";
	}

	//�ͷ��ڴ�
	for (int i = 0; i < height; i++) {
		delete []judgeV[i];
		delete []map[i];
	}
	delete[]judgeV;
	delete[] map;

	getchar();
	getchar();
	return 0;
}


Point judgeDirection(Point start, bool **judge) {
	int x = start.x;
	int y = start.y;
	Point tempPoint;
	Point direction[] = { Point(1,0),Point(0,1),Point(-1,0),Point(0,-1) };

	for (int i = 0; i < 4; i++) {
		tempPoint.x = x + direction[i].x;
		tempPoint.y = y + direction[i].y;
		if (judge[tempPoint.x][tempPoint.y]) {
			judge[tempPoint.x][tempPoint.y] = false;
			return tempPoint;
		}
	}
	return Point(-1, -1); //������·����
}
