#include "nodeList.h"

void cin_num(NodeList* list);

void outIntersection(NodeList* s1, NodeList* s2);

int main() {
	NodeList * S1 = new NodeList();
	if (S1 == NULL) {
		cerr << "�����ڴ�ʧ��,������" << endl;
	}
	NodeList * S2 = new NodeList();
	if (S2 == NULL) {
		cerr << "�����ڴ�ʧ��,������" << endl;
	}
	cin_num(S1);
	cin_num(S2);

	outIntersection(S1, S2);
	//ʹ�����,����̬�ڴ��ջ�,��ֹ�ڴ�й©
	delete S1;
	delete S2;
	getchar();
	getchar();

	return 0;
}


void cin_num(NodeList* list) {
	cout << "����������������!�ǽ���!����,����-1������������" << endl;
	int num;
	bool minus = false;
	do {
		cin >> num;
		if (num == -1) {
			if(minus){
				cout << "������������!!!����������\n";
				list->deleteNode();
				minus = false;
				continue;
			}
			break;
		}
		if (num < 0) {
			minus = true;
		}
		Node* tempNode = new Node(num);
		if (tempNode == NULL) {
			cerr << "��ǰ����ڵ�����ڴ�ʧ��,������";
			return;
		}
		list->Insert(tempNode);
	} while (1);
}

void outIntersection(NodeList* s1, NodeList* s2) {
	//ȡS1������Ԫ��(��ͷ���)
	Node* First1 = s1->getFirst()->getNext();
	//ȡS2������Ԫ��(��ͷ���)
	Node* First2 = s2->getFirst()->getNext();
	//��������,���Ƿ��ڱ���������,����Ϊ��
	int count = 0;
	

	//�����Ԫ�ز�����
	if (First1 == NULL || First2 == NULL) {
		cout << "NULL";
		return;
	}

	do {
		//�������Ԫ�����,�����,��������ָ��ͬʱ�ƶ�
		if (First1->getNum() == First2->getNum()) {
			cout << First1->getNum() << " ";
			First1 = First1->getNext();
			First2 = First2->getNext();
			count++;
		}
		//���S1Ԫ��>S2Ԫ��,��S2ָ���ƶ�
		else if (First1->getNum() > First2->getNum()) {
			First2 = First2->getNext();
		}
		//��֮,S1ָ���ƶ�
		else {
			First1 = First1->getNext();
		}
		//������һ�ű��������ʱ,��������
	} while (First1 != NULL && First2 != NULL);

	//���������֮�󲢼�Ϊ��,�����NULL
	if (count == 0) {
		cout << "NULL";
	}
}