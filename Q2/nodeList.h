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
			cerr << "链表首指针动态内存分配失败,请重试" << endl;
			return ;
		}
		tail = new Node(0);
		if (tail == NULL) {
			cerr << "链表尾指针动态内存分配失败,请重试" << endl;
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
	//定义头节点
	Node* first;
	//定义尾节点
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
		//如果表中无元素,即头指针的子节点为NULL
		if (getFirst()->getNext() == NULL) {
			//则对头结点和尾节点进行初始化
			setFirst(node);
			setTail(node);
		}
		else
		{
			//如果表中有元素,则表明尾节点所指向非空
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

