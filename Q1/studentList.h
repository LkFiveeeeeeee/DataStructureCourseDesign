#ifndef _LIST_
#define _LIST_
#include <iostream>
#include <string>
using namespace std;

class studentNode
{
public:
	studentNode(int num,string name,string sex,int age,string type,studentNode* next=NULL) 
		:testNumer(num),stuName(name),stuSex(sex),stuAge(age),stuApplyType(type),stuNext(next)
	{

	}
	
	studentNode* getNext();
	void setName(string name) {
		stuName = name;
	}

	string getName() {
		return stuName;
	}

	void setNum(int num) {
		testNumer = num;
	}

	int getNum() {
		return testNumer;
	}

	void setSex(string sex) {
		stuSex = sex;
	}

	string getSex() {
		return stuSex;
	}

	void setAge(int age) {
		stuAge = age;
	}

	int getAge() {
		return stuAge;
	}

	void setType(string type) {
		stuApplyType = type;
	}

	string getType() {
		return stuApplyType;
	}

	void setNext(studentNode * node) {
		stuNext = node;
	}

private:
	int testNumer;		//ѧ��
	string stuName;     //����
	string stuSex;      //�Ա�
	int stuAge;         //����
	string stuApplyType; //�������
	studentNode * stuNext;  //ָ����һ��ѧ���ڵ��ָ��
};


studentNode* studentNode::getNext() {
	return stuNext;
}

class studentList {
public:
	studentList() {
		first = new studentNode(0, "", "", 0, "");
		if (first == NULL) {
			cerr << "��̬�����׽ڵ�ʧ��" << endl;
		}
	}


	//����̬���ɵ��ڴ����,��ֹ�ڴ�й©
	~studentList() {
		if (first != NULL) {
			studentNode *temp = first->getNext();
			delete first;
			while (temp != NULL) {
				studentNode* tempNode = temp->getNext();
				delete temp;
				temp = tempNode;
			}
		}
	}
	//����ѧ����Ϣ
	bool insertStu(studentNode* node, int pos);

	//���ڱ��е�λ��Ϊ�����������ض�λ�õĽڵ�
	studentNode* findPosByPos(int pos);

	//�Կ���Ϊ�����������ض�λ�õĽڵ�
	//����ֵΪ ����Ϊnum�Ľڵ�� ǰ�ýڵ�
	studentNode* findPosByNum(int num);

	//�޸�ѧ����Ϣ
	//@@param1 int���� ����
	bool fixStuInfo(int num,studentNode* node);

	//ɾ��һ��ѧ����Ϣ
	//@@param1 int���� ����
	bool deleteStu(int num);


	//������е�ѧ����Ϣ
	void outPutStuInfo();

	//������е�һ��ѧ����Ϣ
	void outPutStuInfoOneLine(studentNode* node);




private:
	studentNode *first; //ͷָ��
};


//����ѧ����Ϣ
bool studentList::insertStu(studentNode* node, int pos) {
	if (first->getNext() == NULL) {
		first->setNext(node);
	}
	else {
		//���Ҫ�����λ����first�ڵ�֮��
		if (pos == 1) {
			//�ݴ�first��Ľڵ�,���нڵ�֮��ĸ���
			auto tempNode = first->getNext();
			first->setNext(node);
			node->setNext(tempNode);
		}//������Ǵ����׽ڵ�֮���λ��,��ʹ��findPos���в���λ��ǰ�ýڵ�Ļ�ȡ
		else {
			auto beforeNode = findPosByPos(pos - 1);
			//����ҵ���,����в���,�������ɵĽڵ�ɾ��,��ֹ�ڴ�й©
			if (beforeNode != NULL) {
				auto tempNode = beforeNode->getNext();
				beforeNode->setNext(node);
				node->setNext(tempNode);
			}
			else {
				delete node;
				return false;
			}
		}
	}
	return true;
}

//���ڱ��е�λ��Ϊ�����������ض�λ�õĽڵ�
studentNode* studentList::findPosByPos(int pos) {
	//��������λ����������
	if (pos <= 0) {
		cerr << "��Ч��λ������,λ������ӦΪ����0����Ȼ��" << endl;
		return NULL;
	}
	//��������λ��ǡ��Ϊfirst��ֱ�Ӻ����ڵ�;
	else if (pos == 1) {
		return first->getNext();
	}
	else {
		int count = 1;
		studentNode* temp = first->getNext();
		//�����Ϊ�׽ڵ�,��ѭ����ȡ
		while (count != pos) {
			//��������λ�ó����˱�ķ�Χ
			if (temp == NULL) {
				cerr << "��Ч��λ������,������ָʾ��λ�ó�������Ϣϵͳ�ķ�Χ" << endl;
				return NULL;
			}
			else {
				temp = temp->getNext();
				count++;
			}
		}
		return temp;
	}
}



//�Կ���Ϊ�����������ض�λ�õĽڵ�
studentNode* studentList::findPosByNum(int num) {
	if (num <= 0) {
		cerr << "��Ч�Ŀ���,����ӦΪ����0����Ȼ��" << endl;
		return NULL;
	}
	auto node = first->getNext();
	//�����洢�ڵ�
	auto temp = node;
	if (node == NULL) {
		cerr << "�˿��Ų�����!" << endl;
		return NULL;
	}
	//�����һ��ѧ���ڵ�Ŀ��ŷ���Ҫ��,�򷵻�ͷָ��
	if (node->getNum() == num) {
		return first;
	}

	while (node->getNum() != num) {
		//temp�����洢node��ǰһ���ڵ�
		temp = node;		
		node = node->getNext();
		if (node == NULL) {
			cerr << "�˿��Ų�����!" << endl;
			return NULL;
		}
	}
	return temp;
}


//�޸�ѧ����Ϣ
//@@returnType bool �ж�ѧ���ڵ��Ƿ����
bool studentList::fixStuInfo(int num, studentNode* node) {
	//Ѱ�ҵ�ǰ���ŵ�ǰ�ýڵ�
	auto fNode = findPosByNum(num);
	//����ҵ�,��node�ڵ��뿼�Žڵ�����滻,����delete�����Žڵ��ֹ�ڴ�й©
	if (fNode != NULL) {
		auto tempNode = fNode->getNext()->getNext();
		auto deleteNode = fNode->getNext();
		fNode->setNext(node);
		node->setNext(tempNode);
		delete deleteNode;
		cout << "�޸ĺ�Ŀ�����Ϣ��: ";
		outPutStuInfoOneLine(node);
		return true;
	}
	return false;
}

//ɾ��һ��ѧ����Ϣ
//@@returnType bool �ж�ɾ���ڵ��Ƿ����
bool studentList::deleteStu(int num) {
	auto beforeNode = findPosByNum(num);
	if (beforeNode != NULL) {
		auto node = beforeNode->getNext()->getNext();
		auto deleteNode = beforeNode->getNext();
		beforeNode->setNext(node);
		cout << "����ɾ���Ŀ�����Ϣ��: ";
		outPutStuInfoOneLine(deleteNode);
		delete deleteNode;
		return true;
	}
	return false;
}

//������е�ѧ����Ϣ
void studentList::outPutStuInfo() {
	cout << "\n";
	cout<<"����\t"<<"����\t"<<"�Ա�\t"<<"����\t"<<"�������\n";
	auto node = first->getNext();
	while (node != NULL) {
		outPutStuInfoOneLine(node);
		node = node->getNext();
	}
}

//������е�һ��ѧ����Ϣ
void studentList::outPutStuInfoOneLine(studentNode* node) {
	cout << node->getNum() << '\t'
		<< node->getName() << '\t'
		<< node->getSex() << '\t'
		<< node->getAge() << '\t'
		<< node->getType() << endl;
}

#endif // _LIST_

