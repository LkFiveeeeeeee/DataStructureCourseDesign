#include "studentList.h"
void initStuInfo(int num, studentList* studentSystem);
studentNode* createStuInfo();
int outOperation(studentList* studentSystem);
void insertStuInfo(studentList* studentSystem);
void deleteStuInfo(studentList* studentSystem);
void findStuInfo(studentList* studentSystem);
void fixStuInfo(studentList* studentSystem);
void outAllInfo(studentList* studentSystem);

int main() {
	studentList * studentSystem = new studentList();

	int studentNum;
	cout << "�����뽨������ϵͳ!\n";
	do {
		cout << "�����뿼������:";
		cin >> studentNum;
		if (studentNum < 0) {
			cout << "������������Ϊ��!! ";
		}
	} while (studentNum < 0);
	initStuInfo(studentNum, studentSystem);
	cout << "��ѡ����Ҫ���еĲ���(1Ϊ����,2Ϊɾ��,3Ϊ����,4Ϊ�޸�,5Ϊͳ��,0Ϊȡ������)" << endl;

	while (outOperation(studentSystem) != 0);

	return 0;

}


//��ʼ����Ϣ
void initStuInfo(int num,studentList* studentSystem) {
	cout << "���Դ����뿼���Ŀ��š��������Ա������Լ��������!" << endl;
		
	for (auto i = 0; i < num; i++) {
		auto tempNode = createStuInfo();
		if (tempNode == NULL) {
			cout << "����ѧ����Ϣʧ��,û���㹻����Դ��̬����ѧ���ڵ�" << endl;
			return;
		}
		studentSystem->insertStu(tempNode,i + 1);
	}

	studentSystem->outPutStuInfo();
}

//��������
int outOperation(studentList* studentSystem) {
	int num;
	do {
		cout << "��ѡ����Ҫ���еĲ���:";
		cin >> num;
		switch (num)
		{
		case 1:
			insertStuInfo(studentSystem);
			break;
		case 2:
			deleteStuInfo(studentSystem);
			break;
		case 3:
			findStuInfo(studentSystem);
			break;
		case 4:
			fixStuInfo(studentSystem);
			break;
		case 5:
			outAllInfo(studentSystem);
			break;
		case 0:
			return 0;
		default:
			cout << "���Ĳ��������,���������� ";
			break;
		}
	} while (num < 0 || num > 5);
	return 1;
}

//����һ��ѧ����Ϣ�ڵ�
void insertStuInfo(studentList* studentSystem) {
	int pos;
	cout << "��������Ҫ����Ŀ�����λ��:";
	cin >> pos;
	cout << "���Դ�����Ҫ����Ŀ����Ŀ���,����,�Ա�,�����Լ��������\n";
	auto tempNode = createStuInfo();
	if (tempNode == NULL) {
		cout << "����ѧ����Ϣʧ��,û���㹻����Դ��̬����ѧ���ڵ�" << endl;
		return;
	}
	if (studentSystem->insertStu(tempNode, pos)) {
		outAllInfo(studentSystem);
	}
	else {
		delete tempNode;//�ͷ���
		cerr << "����ʧ��\n";
	}
}

//ɾ��һ��ѧ����Ϣ�ڵ�
void deleteStuInfo(studentList* studentSystem) {
	int num;
	cout << "������Ҫɾ���Ŀ����Ŀ���:";
	cin >> num;
	if (studentSystem->deleteStu(num)) {
		outAllInfo(studentSystem);
	}
}

//Ѱ��һ��ѧ����Ϣ�ڵ�
void findStuInfo(studentList* studentSystem) {
	int num;
	cout << "������Ҫ��ѯ�Ŀ����Ŀ���";
	cin >> num;
	auto node = studentSystem->findPosByNum(num);
	if (node == NULL) {
		return;
	}
	cout << "����\t" << "����\t" << "�Ա�\t" << "����\t" << "�������\n";
	studentSystem->outPutStuInfoOneLine(node->getNext());
	cout << "\n";
}


//�޸�һ��ѧ����Ϣ�ڵ�
void fixStuInfo(studentList* studentSystem) {
	int num;
	cout << "������Ҫ�޸ĵ�ѧ���Ŀ���:";
	cin >> num;
	cout << "�����������޸ĺ�Ŀ����Ŀ���,����,�Ա�,�����Լ���������\n";
	auto tempNode = createStuInfo();
	if (tempNode == NULL) {
		cout << "�½�ѧ����Ϣʧ��,û���㹻����Դ��̬����ѧ���ڵ�" << endl;
		return;
	}
	if (studentSystem->fixStuInfo(num, tempNode)) {
		outAllInfo(studentSystem);
	}
	else {
		//�ͷ��ڴ�
		delete tempNode; 
	}
}

//���ѧ����Ϣ��
void outAllInfo(studentList* studentSystem) {
	studentSystem->outPutStuInfo();
	cout << "\n";
}

//����һ��ѧ����Ϣ�ڵ�
studentNode* createStuInfo() {
	int testNum;
	string name;
	string sex;
	int age;
	string type;
	cin >> testNum >> name >> sex >> age >> type;
	auto tempNode = new studentNode(testNum, name, sex, age, type);
	return tempNode;
}