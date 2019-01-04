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
	//����һ����ͥ
	void createFamily(string name);
	//��Ӽ�ͥ��Ա
	void addFamilyMember(string name);
	//��ɢ�ֲ���ͥ
	void dissovePartFamily(string name);
	//Ϊĳһ��ͥ��Ա��������
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
		cout << "���޴���,��ȷ���Ƿ�����������ȷ!!!\n";
		return;
	}
	else if (tempNode->getNum() != 0) {
		cout << "������ӵ�м�ͥ,��ȷ���Ƿ�����������ȷ!!!\n";
		return;
	}
	int num;
	cout << "������" << name << "�Ķ�Ů����: ";
	cin >> num;
	tempNode->setNum(num);
	if (num <= 0) {
		cout << "���������,��ȷ�Ϻ�������,ָ��������!!!\n";
		return;
	}
	cout << "����������" << name << "�Ķ�Ů������: ";
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
		cout << "���޴���,��ȷ���Ƿ�����������ȷ!!!\n";
		return;
	}
	int num = node->getNum();
	num++;
	node->setNum(num);
	cout << "������"<<name<<"����Ӷ���(��Ů��)������: ";
	string tempName;
	cin >> tempName;
	FamilyNode* tempNode = new FamilyNode(tempName);
	node->setNode(tempNode);
	coutFirstChildren(node, name);
}

void FamilyTree::dissovePartFamily(string name) {
	FamilyNode* node = findNode(root,name);
	if (node == NULL) {
		cout << "���޴���,��ȷ���Ƿ�����������ȷ!!!\n";
		return;
	}
	cout << "Ҫ��ɢ��ͥ������:" << node->getName() << endl;
	cout << node->getName() << "�ĵ�һ�������ǣ�";
	for (auto i = 0; i < node->getNum(); i++) {
		cout << node->getNode(i)->getName() << "\t";
		delete node->getNode(i);
	}
	node->setNum(0);
	//��մ洢�ӽڵ��vector
	node->getNodeVector()->clear();
	cout << "\n\n";
}

void FamilyTree::changeNameForOneFameliyMember(string name) {
	FamilyNode* node = findNode(root, name);
	if (node == NULL) {
		cout << "���޴���,��ȷ���Ƿ�����������ȷ!!!\n";
		return;
	}
	string newName;
	cout << "��������ĺ��������";
	cin >> newName;
	cout << name << "�Ѹ���Ϊ";
	node->setName(newName);
	cout << node->getName()<<endl<<endl;
}


void FamilyTree::coutFirstChildren(FamilyNode *node, string name) {
	cout << name << "�ĵ�һ��������: ";
	for (auto i = 0; i < node->getNum(); i++) {
		cout << node->getNode(i)->getName() << "\t";
	}
	cout << endl<<endl;
}

#endif // !_FAMILY_TREE

