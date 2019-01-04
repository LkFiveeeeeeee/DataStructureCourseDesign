#ifndef _NODE_LIST
#define _NODE_LIST
#include <iostream>
using namespace std;


class Node {
public:
	Node(int n,Node* ne = NULL): num(n), next(ne){}
	Node* getNext() {
		return next;
	}
	void setNext(Node* node) {
		next = node;
	}
	int getNum() {
		return num;
	}

private:
	int num;
	Node* next;
};


class NodeList {
public:
	NodeList() {
		first = new Node(0);
		if (first == NULL) {
			cerr << "������ָ�붯̬�ڴ����ʧ��,������" << endl;
			return ;
		}
		tail = new Node(0);
		if (tail == NULL) {
			cerr << "����βָ�붯̬�ڴ����ʧ��,������" << endl;
			return ;
		}
	}
	void Insert(Node * node);
	Node* getFirst();
	Node* getTail();
	void setTail(Node* node);
	void setFirst(Node * node);
	void deleteNode();
	~NodeList();
private:
	//����ͷ�ڵ�
	Node* first;
	//����β�ڵ�
	Node* tail;
};

Node* NodeList::getFirst() {
	return first;
}

Node* NodeList::getTail() {
	return tail;
}

void NodeList::setTail(Node* node) {
	tail->setNext(node);
}

void NodeList::setFirst(Node * node) {
	first->setNext(node);
}

void NodeList::deleteNode() {
	Node* itr = getFirst()->getNext();
	while (itr != getTail()->getNext()) {
		Node* temp = itr;
		itr = temp->getNext();
		delete temp;
	}
	getFirst()->setNext(NULL);
	delete itr;
}


	void NodeList::Insert(Node * node) {
		//���������Ԫ��,��ͷָ����ӽڵ�ΪNULL
		if (getFirst()->getNext() == NULL) {
			//���ͷ����β�ڵ���г�ʼ��
			setFirst(node);
			setTail(node);
		}
		else
		{
			//���������Ԫ��,�����β�ڵ���ָ��ǿ�
			Node* tempNode = getTail()->getNext();
			tempNode->setNext(node);
			getTail()->setNext(node);
		}

	}


NodeList::~NodeList() {
	deleteNode();
	delete getTail();
	delete getFirst();
}







#endif // !_NODE_LIST

