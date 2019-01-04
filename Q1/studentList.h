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
	int testNumer;		//学号
	string stuName;     //姓名
	string stuSex;      //性别
	int stuAge;         //年龄
	string stuApplyType; //报考类别
	studentNode * stuNext;  //指向下一个学生节点的指针
};


studentNode* studentNode::getNext() {
	return stuNext;
}

class studentList {
public:
	studentList() {
		first = new studentNode(0, "", "", 0, "");
		if (first == NULL) {
			cerr << "动态分配首节点失败" << endl;
		}
	}


	//将动态生成的内存清除,防止内存泄漏
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
	//插入学生信息
	bool insertStu(studentNode* node, int pos);

	//以在表中的位置为依据来搜索特定位置的节点
	studentNode* findPosByPos(int pos);

	//以考号为依据来搜索特定位置的节点
	//返回值为 考号为num的节点的 前置节点
	studentNode* findPosByNum(int num);

	//修改学生信息
	//@@param1 int类型 考号
	bool fixStuInfo(int num,studentNode* node);

	//删除一条学生信息
	//@@param1 int类型 考号
	bool deleteStu(int num);


	//输出表中的学生信息
	void outPutStuInfo();

	//输出表中的一条学生信息
	void outPutStuInfoOneLine(studentNode* node);




private:
	studentNode *first; //头指针
};


//插入学生信息
bool studentList::insertStu(studentNode* node, int pos) {
	if (first->getNext() == NULL) {
		first->setNext(node);
	}
	else {
		//如果要插入的位置在first节点之后
		if (pos == 1) {
			//暂存first后的节点,进行节点之间的更换
			auto tempNode = first->getNext();
			first->setNext(node);
			node->setNext(tempNode);
		}//如果不是处在首节点之后的位置,则使用findPos进行插入位置前置节点的获取
		else {
			auto beforeNode = findPosByPos(pos - 1);
			//如果找到了,则进行插入,否则将生成的节点删除,防止内存泄漏
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

//以在表中的位置为依据来搜索特定位置的节点
studentNode* studentList::findPosByPos(int pos) {
	//如果请求的位置索引错误
	if (pos <= 0) {
		cerr << "无效的位置索引,位置索引应为大于0的自然数" << endl;
		return NULL;
	}
	//如果请求的位置恰好为first的直接后驱节点;
	else if (pos == 1) {
		return first->getNext();
	}
	else {
		int count = 1;
		studentNode* temp = first->getNext();
		//如果不为首节点,则循环获取
		while (count != pos) {
			//如果请求的位置超出了表的范围
			if (temp == NULL) {
				cerr << "无效的位置索引,该索引指示的位置超出了信息系统的范围" << endl;
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



//以考号为依据来搜索特定位置的节点
studentNode* studentList::findPosByNum(int num) {
	if (num <= 0) {
		cerr << "无效的考号,考号应为大于0的自然数" << endl;
		return NULL;
	}
	auto node = first->getNext();
	//用来存储节点
	auto temp = node;
	if (node == NULL) {
		cerr << "此考号不存在!" << endl;
		return NULL;
	}
	//如果第一个学生节点的考号符合要求,则返回头指针
	if (node->getNum() == num) {
		return first;
	}

	while (node->getNum() != num) {
		//temp用来存储node的前一个节点
		temp = node;		
		node = node->getNext();
		if (node == NULL) {
			cerr << "此考号不存在!" << endl;
			return NULL;
		}
	}
	return temp;
}


//修改学生信息
//@@returnType bool 判断学生节点是否存在
bool studentList::fixStuInfo(int num, studentNode* node) {
	//寻找当前考号的前置节点
	auto fNode = findPosByNum(num);
	//如果找到,则将node节点与考号节点进行替换,并将delete掉考号节点防止内存泄漏
	if (fNode != NULL) {
		auto tempNode = fNode->getNext()->getNext();
		auto deleteNode = fNode->getNext();
		fNode->setNext(node);
		node->setNext(tempNode);
		delete deleteNode;
		cout << "修改后的考生信息是: ";
		outPutStuInfoOneLine(node);
		return true;
	}
	return false;
}

//删除一条学生信息
//@@returnType bool 判断删除节点是否存在
bool studentList::deleteStu(int num) {
	auto beforeNode = findPosByNum(num);
	if (beforeNode != NULL) {
		auto node = beforeNode->getNext()->getNext();
		auto deleteNode = beforeNode->getNext();
		beforeNode->setNext(node);
		cout << "你所删除的考生信息是: ";
		outPutStuInfoOneLine(deleteNode);
		delete deleteNode;
		return true;
	}
	return false;
}

//输出表中的学生信息
void studentList::outPutStuInfo() {
	cout << "\n";
	cout<<"考号\t"<<"姓名\t"<<"性别\t"<<"年龄\t"<<"报考类别\n";
	auto node = first->getNext();
	while (node != NULL) {
		outPutStuInfoOneLine(node);
		node = node->getNext();
	}
}

//输出表中的一条学生信息
void studentList::outPutStuInfoOneLine(studentNode* node) {
	cout << node->getNum() << '\t'
		<< node->getName() << '\t'
		<< node->getSex() << '\t'
		<< node->getAge() << '\t'
		<< node->getType() << endl;
}

#endif // _LIST_

