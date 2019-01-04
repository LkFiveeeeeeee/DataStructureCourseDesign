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
	//为Huffman指针节点容器分配内存
	heapContainer = new HuffmanNode*[n+1];
	maxSize = n;
	currentSize = 0;
}

MyHeap::~MyHeap() {
	delete heapContainer;
}

//@@param start 开始点
//@@param m 终止点
void MyHeap::shiftDown(int start, int m) {
	int i = start;
	int j = 2 * start + 1;
	HuffmanNode* tempNode = heapContainer[i];
	//当j没有越界时,循环进行比较
	while (j <= m) {
		if (j < m && heapContainer[j]->getData() >= heapContainer[j + 1]->getData()) {
			j++;
		}
		//如果start的位置的值小于当前位置的值,说明排序正确,跳出循环
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

//@@param start 开始点
void MyHeap::shiftUp(int start) {
	int i = start;
	int j = (i - 1) / 2;
	HuffmanNode* tempNode = heapContainer[i];
	//当i == 0时循环结束
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
	//当已满时,给出错误信息并退出
	if (isFull()) {
		cerr << "最大堆已满,插入失败!!" << endl;
		exit(1);
	}
	else {
		//否则,在容器中加入节点,并使用向上转移函数重新排序
		heapContainer[currentSize] = node;
		shiftUp(currentSize);
		currentSize++;
		return true;
	}
}


HuffmanNode* MyHeap::RemoveMin() {
	//当堆中无元素时,给出错误信息
	if (currentSize == 0) {
		cerr << "堆中无元素,请确认您的操作是否正确\n";
		return NULL;
	}
	else {
		//将堆顶节点返回,并将堆尾的节点提到堆顶,使用向下转移算法重新排序
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
	//一开始还没有将树合并,所以祖宗节点为NULL
	root = NULL;
}

void HuffmanTree::mergeTree(HuffmanNode* left, HuffmanNode* right) {
	HuffmanNode* parent = new HuffmanNode(left->getData() + right->getData(), left, right);
	//如果堆为空的话,说明所有节点已经处理完毕,此时就把根节点设为当前合并所得到的节点
	if (huffmanheap->isEmptey()) {
		setRoot(parent);
	}
	huffmanheap->Insert(parent);
}

//递归计算
int HuffmanTree::countWeight(HuffmanNode* node) {
	//不计算root节点的data,其他节点的data全部计入
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



