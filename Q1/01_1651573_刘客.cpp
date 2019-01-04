#include "studentList.h"
void initStuInfo(int num, studentList* studentSystem);
studentNode* createStuInfo();
int outOperation(studentList* studentSystem);
void insertStuInfo(studentList* studentSystem);
void deleteStuInfo(studentList* studentSystem);
void findStuInfo(studentList* studentSystem);
void fixStuInfo(studentList* studentSystem);
void outAllInfo(studentList* studentSystem);

int main() {
	studentList * studentSystem = new studentList();

	int studentNum;
	cout << "首先请建立考生系统!\n";
	do {
		cout << "请输入考生人数:";
		cin >> studentNum;
		if (studentNum < 0) {
			cout << "考生人数不可为负!! ";
		}
	} while (studentNum < 0);
	initStuInfo(studentNum, studentSystem);
	cout << "请选择您要进行的操作(1为插入,2为删除,3为查找,4为修改,5为统计,0为取消操作)" << endl;

	while (outOperation(studentSystem) != 0);

	return 0;

}


//初始化信息
void initStuInfo(int num,studentList* studentSystem) {
	cout << "请以此输入考生的考号、姓名、性别、年龄以及报考类别!" << endl;
		
	for (auto i = 0; i < num; i++) {
		auto tempNode = createStuInfo();
		if (tempNode == NULL) {
			cout << "插入学生信息失败,没有足够的资源动态生成学生节点" << endl;
			return;
		}
		studentSystem->insertStu(tempNode,i + 1);
	}

	studentSystem->outPutStuInfo();
}

//操作序列
int outOperation(studentList* studentSystem) {
	int num;
	do {
		cout << "请选择您要进行的操作:";
		cin >> num;
		switch (num)
		{
		case 1:
			insertStuInfo(studentSystem);
			break;
		case 2:
			deleteStuInfo(studentSystem);
			break;
		case 3:
			findStuInfo(studentSystem);
			break;
		case 4:
			fixStuInfo(studentSystem);
			break;
		case 5:
			outAllInfo(studentSystem);
			break;
		case 0:
			return 0;
		default:
			cout << "您的操作码错误,请重新输入 ";
			break;
		}
	} while (num < 0 || num > 5);
	return 1;
}

//插入一条学生信息节点
void insertStuInfo(studentList* studentSystem) {
	int pos;
	cout << "请输入您要插入的考生的位置:";
	cin >> pos;
	cout << "请以此输入要插入的考生的考号,姓名,性别,年龄以及报考类别\n";
	auto tempNode = createStuInfo();
	if (tempNode == NULL) {
		cout << "插入学生信息失败,没有足够的资源动态生成学生节点" << endl;
		return;
	}
	if (studentSystem->insertStu(tempNode, pos)) {
		outAllInfo(studentSystem);
	}
	else {
		delete tempNode;//释放内
		cerr << "插入失败\n";
	}
}

//删除一条学生信息节点
void deleteStuInfo(studentList* studentSystem) {
	int num;
	cout << "请输入要删除的考生的考号:";
	cin >> num;
	if (studentSystem->deleteStu(num)) {
		outAllInfo(studentSystem);
	}
}

//寻找一条学生信息节点
void findStuInfo(studentList* studentSystem) {
	int num;
	cout << "请输入要查询的考生的考号";
	cin >> num;
	auto node = studentSystem->findPosByNum(num);
	if (node == NULL) {
		return;
	}
	cout << "考号\t" << "姓名\t" << "性别\t" << "年龄\t" << "报考类别\n";
	studentSystem->outPutStuInfoOneLine(node->getNext());
	cout << "\n";
}


//修改一条学生信息节点
void fixStuInfo(studentList* studentSystem) {
	int num;
	cout << "请输入要修改的学生的考号:";
	cin >> num;
	cout << "请依次输入修改后的考生的考号,姓名,性别,年龄以及报考类型\n";
	auto tempNode = createStuInfo();
	if (tempNode == NULL) {
		cout << "新建学生信息失败,没有足够的资源动态生成学生节点" << endl;
		return;
	}
	if (studentSystem->fixStuInfo(num, tempNode)) {
		outAllInfo(studentSystem);
	}
	else {
		//释放内存
		delete tempNode; 
	}
}

//输出学生信息表
void outAllInfo(studentList* studentSystem) {
	studentSystem->outPutStuInfo();
	cout << "\n";
}

//创建一条学生信息节点
studentNode* createStuInfo() {
	int testNum;
	string name;
	string sex;
	int age;
	string type;
	cin >> testNum >> name >> sex >> age >> type;
	auto tempNode = new studentNode(testNum, name, sex, age, type);
	return tempNode;
}