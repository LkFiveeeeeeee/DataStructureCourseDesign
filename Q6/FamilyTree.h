#ifndef _FAMILY_TREE
#define _FAMILY_TREE
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class FamilyNode {
public:
	FamilyNode(){}
	FamilyNode(string tempName,int num = 0):name(tempName),childrenNum(num){ }
	string getName() { return name; }
	void setName(string tempName) { name = tempName; }
	int getNum() { return childrenNum; }
	void setNum(int num) { childrenNum = num; }
	void setNode(FamilyNode* node){ childrenNode.push_back(node);}
	vector<FamilyNode*> * getNodeVector() { return &childrenNode; }
	FamilyNode* getNode(int i) { return childrenNode.at(i); }
private:
	string name;
	int childrenNum;
	vector<FamilyNode*> childrenNode;
};

class FamilyTree {
public:
	FamilyTree(FamilyNode * node);
	//创建一个家庭
	void createFamily(string name);
	//添加家庭成员
	void addFamilyMember(string name);
	//解散局部家庭
	void dissovePartFamily(string name);
	//为某一家庭成员更改名字
	void changeNameForOneFameliyMember(string name);
private:
	FamilyNode* root;
	FamilyNode* findNode(FamilyNode* node, string name);
	void coutFirstChildren(FamilyNode* node,string name);
};


FamilyTree::FamilyTree(FamilyNode * node) {
	root = node;
}

FamilyNode* FamilyTree::findNode(FamilyNode* node,string name) {
	if (node != NULL) {
		if (node->getName() == name) {
			return node;
		}
		else {
			FamilyNode* tempNode;
			for (auto i = 0; i < node->getNum(); i++) {
				tempNode = findNode(node->getNode(i), name);
				if (tempNode != NULL) {
					return tempNode;
				}
			}
			return NULL;
		}
	}
	return NULL;
}

void FamilyTree::createFamily(string name) {
	FamilyNode* tempNode = findNode(root, name);
	if (tempNode == NULL) {
		cout << "查无此人,请确认是否输入姓名正确!!!\n";
		return;
	}
	else if (tempNode->getNum() != 0) {
		cout << "此人已拥有家庭,请确认是否输入姓名正确!!!\n";
		return;
	}
	int num;
	cout << "请输入" << name << "的儿女人数: ";
	cin >> num;
	tempNode->setNum(num);
	if (num <= 0) {
		cout << "错误的数字,请确认后再输入,指令已重置!!!\n";
		return;
	}
	cout << "请依次输入" << name << "的儿女的姓名: ";
	for (auto i = 0; i < num; i++) {
		string tempName;
		cin >> tempName;
		FamilyNode* node = new FamilyNode(tempName);
		tempNode->setNode(node);
	}
	coutFirstChildren(tempNode, name);
}


void FamilyTree::addFamilyMember(string name) {
	FamilyNode* node = findNode(root,name);
	if (node == NULL) {
		cout << "查无此人,请确认是否输入姓名正确!!!\n";
		return;
	}
	int num = node->getNum();
	num++;
	node->setNum(num);
	cout << "请输入"<<name<<"新添加儿子(或女儿)的姓名: ";
	string tempName;
	cin >> tempName;
	FamilyNode* tempNode = new FamilyNode(tempName);
	node->setNode(tempNode);
	coutFirstChildren(node, name);
}

void FamilyTree::dissovePartFamily(string name) {
	FamilyNode* node = findNode(root,name);
	if (node == NULL) {
		cout << "查无此人,请确认是否输入姓名正确!!!\n";
		return;
	}
	cout << "要解散家庭的人是:" << node->getName() << endl;
	cout << node->getName() << "的第一代子孙是：";
	for (auto i = 0; i < node->getNum(); i++) {
		cout << node->getNode(i)->getName() << "\t";
		delete node->getNode(i);
	}
	node->setNum(0);
	//清空存储子节点的vector
	node->getNodeVector()->clear();
	cout << "\n\n";
}

void FamilyTree::changeNameForOneFameliyMember(string name) {
	FamilyNode* node = findNode(root, name);
	if (node == NULL) {
		cout << "查无此人,请确认是否输入姓名正确!!!\n";
		return;
	}
	string newName;
	cout << "请输入更改后的姓名：";
	cin >> newName;
	cout << name << "已更名为";
	node->setName(newName);
	cout << node->getName()<<endl<<endl;
}


void FamilyTree::coutFirstChildren(FamilyNode *node, string name) {
	cout << name << "的第一代子孙是: ";
	for (auto i = 0; i < node->getNum(); i++) {
		cout << node->getNode(i)->getName() << "\t";
	}
	cout << endl<<endl;
}

#endif // !_FAMILY_TREE

