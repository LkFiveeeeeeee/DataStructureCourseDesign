#include<iostream>
using namespace std;
//�Զ������
struct myQuene
{
	int num[1001];
	int first;  //������ָ��
	int last;   //����βָ��
};

int main() {
	myQuene queneA;
	myQuene queneB;
	//��ʼ��A��B������βָ��
	queneA.first = 0; 
	queneB.first = 0;
	queneA.last = 0;
	queneB.last = 0;

	int peopleNum;
	int customerNum;
	//���������ʱ������Ϊ1,��ÿ��countTimeΪż��ʱ,��B���н��д���
	int countTime = 1;
	cout << "������˿�����: ";
	cin >> peopleNum;
	if (peopleNum != 0) {
		cout << "������˿ͱ��: ";
	}
	//����˿ͱ��
	for (auto i = 1; i <= peopleNum; i++) {
		cin >> customerNum;
		if (customerNum % 2 != 0) {
			//��βָ�����,�洢����
			queneA.num[queneA.last++] = customerNum;
		}
		else {
			queneB.num[queneB.last++] = customerNum;
		}
	}

	//�����ж��Ƿ����������,�Դ����ж��Ƿ���Ҫ���" "(���һλ��Ӧ������ո�)
	bool judgeAend = (queneA.first == queneA.last);
	bool judgeBend = (queneB.first == queneB.last);
	
	if (peopleNum != 0) {
		cout << "����˳��Ϊ: ";
	}
	else {
		cout << "�޹˿�,����Ҫ���д���!";
	}

	while (!judgeAend || !judgeBend) {
		if (!judgeAend) {
			//��A����δ�������ʱ,���д���
			cout << queneA.num[queneA.first++];
			//�������һ����ź�,���ֶ����Ѿ��������
			if (queneA.first == queneA.last) {
				//����־������Ϊtrue
				judgeAend = true;
				if (judgeBend) {
					//���BҲ�Ѿ��������,��������еĹ˿ͱ�Ŷ��Ѿ��������,��ʱ����Ҫ����ո�,ֱ��break;
					break;
				}
			}
			//�����Ȼ,������ո�
			cout << " ";
		}
		//��ΪA���е��ٶ���B���е�����,����ֻ�м�ʱΪż��ʱ(countTime��ʼֵΪ1),�Ŷ�B���д���,�����߼���A������ͬ
		if (countTime % 2 == 0 && !judgeBend) {
			cout << queneB.num[queneB.first++];
			if (queneB.first == queneB.last) {
				judgeBend = true;
				if (judgeAend) {
					break;
				}
			}
			cout << " ";
		}
		countTime++;
	}

	getchar();
	getchar();
	return 0;


}