#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_
#include <iostream>
using namespace std;
class HuffmanNode {
public:
	HuffmanNode(int num, HuffmanNode* left = NULL, HuffmanNode* right = NULL)
		:data(num), leftChild(left), rightChild(right) {};
	int getData() { return data; }
	void setData(int num) { data = num; }
	void setLeft(HuffmanNode* left) { leftChild = left; }
	void setRight(HuffmanNode* right) { rightChild = right; }
	HuffmanNode* getLeft() { return leftChild; }
	HuffmanNode* getRight() { return rightChild; }
private:
	int data;
	HuffmanNode* leftChild;
	HuffmanNode* rightChild;
};
class MyHeap {
public:
	MyHeap(int n);
	~MyHeap();
	bool Insert(HuffmanNode* node);
	HuffmanNode* RemoveMin();
	bool isFull()const;
	bool isEmptey()const;
private:
	HuffmanNode** heapContainer;
	int currentSize;
	int maxSize;
	void shiftUp(int start);
	void shiftDown(int start, int m);
};


MyHeap::MyHeap(int n) {
	//ΪHuffmanָ��ڵ����������ڴ�
	heapContainer = new HuffmanNode*[n+1];
	maxSize = n;
	currentSize = 0;
}

MyHeap::~MyHeap() {
	delete heapContainer;
}

//@@param start ��ʼ��
//@@param m ��ֹ��
void MyHeap::shiftDown(int start, int m) {
	int i = start;
	int j = 2 * start + 1;
	HuffmanNode* tempNode = heapContainer[i];
	//��jû��Խ��ʱ,ѭ�����бȽ�
	while (j <= m) {
		if (j < m && heapContainer[j]->getData() >= heapContainer[j + 1]->getData()) {
			j++;
		}
		//���start��λ�õ�ֵС�ڵ�ǰλ�õ�ֵ,˵��������ȷ,����ѭ��
		if (tempNode->getData() <= heapContainer[j]->getData()) {
			break;
		}
		else {
			heapContainer[i] = heapContainer[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heapContainer[i] = tempNode;
}

//@@param start ��ʼ��
void MyHeap::shiftUp(int start) {
	int i = start;
	int j = (i - 1) / 2;
	HuffmanNode* tempNode = heapContainer[i];
	//��i == 0ʱѭ������
	while (i > 0) {
		if (heapContainer[j]->getData() <= tempNode->getData()) {
			break;
		}
		else {
			heapContainer[i] = heapContainer[j];
			i = j;
			j = (j - 1) / 2;
		}
	}
	heapContainer[i] = tempNode;
}

bool MyHeap::isFull()const {
	return currentSize == maxSize;
}

bool MyHeap::isEmptey()const {
	return currentSize == 0;
}

bool MyHeap::Insert(HuffmanNode* node) {
	//������ʱ,����������Ϣ���˳�
	if (isFull()) {
		cerr << "��������,����ʧ��!!" << endl;
		exit(1);
	}
	else {
		//����,�������м���ڵ�,��ʹ������ת�ƺ�����������
		heapContainer[currentSize] = node;
		shiftUp(currentSize);
		currentSize++;
		return true;
	}
}


HuffmanNode* MyHeap::RemoveMin() {
	//��������Ԫ��ʱ,����������Ϣ
	if (currentSize == 0) {
		cerr << "������Ԫ��,��ȷ�����Ĳ����Ƿ���ȷ\n";
		return NULL;
	}
	else {
		//���Ѷ��ڵ㷵��,������β�Ľڵ��ᵽ�Ѷ�,ʹ������ת���㷨��������
		HuffmanNode* tempNode = heapContainer[0];
		heapContainer[0] = heapContainer[currentSize - 1];
		currentSize--;
		shiftDown(0, currentSize - 1);
		return tempNode;
	}
}

class HuffmanTree {
public:
	HuffmanTree(int num);
	~HuffmanTree() {
		if (root != NULL) {
			deleteTree(root);
		}
	}
	void mergeTree(HuffmanNode* left, HuffmanNode* right);
	void setRoot(HuffmanNode* node) {
		root = node;
	}
	HuffmanNode* getRoot() {
		return root;
	}
	void insertNode(HuffmanNode* node) {
		huffmanheap->Insert(node);
	}
	bool isEmptey() {
		return huffmanheap->isEmptey();
	}
	HuffmanNode* remove() {
		return huffmanheap->RemoveMin();
	}
	int countWeight(HuffmanNode* node);
private:
	HuffmanNode* root;
	MyHeap* huffmanheap;
	void deleteTree(HuffmanNode* node);
};

HuffmanTree::HuffmanTree(int num) {
	huffmanheap = new MyHeap(num);
	//һ��ʼ��û�н����ϲ�,�������ڽڵ�ΪNULL
	root = NULL;
}

void HuffmanTree::mergeTree(HuffmanNode* left, HuffmanNode* right) {
	HuffmanNode* parent = new HuffmanNode(left->getData() + right->getData(), left, right);
	//�����Ϊ�յĻ�,˵�����нڵ��Ѿ��������,��ʱ�ͰѸ��ڵ���Ϊ��ǰ�ϲ����õ��Ľڵ�
	if (huffmanheap->isEmptey()) {
		setRoot(parent);
	}
	huffmanheap->Insert(parent);
}

//�ݹ����
int HuffmanTree::countWeight(HuffmanNode* node) {
	//������root�ڵ��data,�����ڵ��dataȫ������
	if (node == root) {
		return countWeight(node->getLeft()) + countWeight(node->getRight());
	}
	else if (node->getLeft() != NULL && node->getRight() != NULL) {
		return countWeight(node->getLeft()) + countWeight(node->getRight()) + node->getData();
	}
	else {
		return node->getData();
	}
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
	if (node->getLeft() != NULL && node->getRight() != NULL) {
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
	}
	delete node;
}

#endif // !_HUFFMAN_TREE_



