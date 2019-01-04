#include "nodeList.h"

void cin_num(NodeList* list);

void outIntersection(NodeList* s1, NodeList* s2);

int main() {
	NodeList * S1 = new NodeList();
	if (S1 == NULL) {
		cerr << "分配内存失败,请重试" << endl;
	}
	NodeList * S2 = new NodeList();
	if (S2 == NULL) {
		cerr << "分配内存失败,请重试" << endl;
	}
	cin_num(S1);
	cin_num(S2);

	outIntersection(S1, S2);
	//使用完毕,将动态内存收回,防止内存泄漏
	delete S1;
	delete S2;
	getchar();
	getchar();

	return 0;
}


void cin_num(NodeList* list) {
	cout << "请输入您的正整数!非降序!序列,输入-1则代表输入结束" << endl;
	int num;
	bool minus = false;
	do {
		cin >> num;
		if (num == -1) {
			if(minus){
				cout << "请输入正整数!!!请重新输入\n";
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
			cerr << "当前输入节点分配内存失败,请重试";
			return;
		}
		list->Insert(tempNode);
	} while (1);
}

void outIntersection(NodeList* s1, NodeList* s2) {
	//取S1表中首元素(非头结点)
	Node* First1 = s1->getFirst()->getNext();
	//取S2表中首元素(非头结点)
	Node* First2 = s2->getFirst()->getNext();
	//用来计数,看是否在遍历过程中,交集为空
	int count = 0;
	

	//如果首元素不存在
	if (First1 == NULL || First2 == NULL) {
		cout << "NULL";
		return;
	}

	do {
		//如果两个元素相等,则输出,并两个表指针同时移动
		if (First1->getNum() == First2->getNum()) {
			cout << First1->getNum() << " ";
			First1 = First1->getNext();
			First2 = First2->getNext();
			count++;
		}
		//如果S1元素>S2元素,则S2指针移动
		else if (First1->getNum() > First2->getNum()) {
			First2 = First2->getNext();
		}
		//反之,S1指针移动
		else {
			First1 = First1->getNext();
		}
		//当存在一张表被便利完毕时,结束程序
	} while (First1 != NULL && First2 != NULL);

	//如果遍历完之后并集为空,则输出NULL
	if (count == 0) {
		cout << "NULL";
	}
}