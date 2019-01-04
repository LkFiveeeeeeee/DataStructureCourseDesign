#include "FamilyTree.h"

void welcomeImage() {
	cout << "**\t\t" << "家谱管理系统" << "\t\t\t**\n";
	cout << "==================================================\n";
	cout << "**\t      请选择要执行的操作 ：       \t**\n";
	cout << "**\t\tA --- 完善家谱 \t\t\t**\n";
	cout << "**\t\tB --- 添加家庭成员\t\t**\n";
	cout << "**\t\tC --- 解散局部家庭\t\t**\n";
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**\n";
	cout << "**\t\tE --- 退出程序\t\t\t**\n";
	cout << "==================================================\n";
	cout << "首先建立一个家谱!\n";
}

bool processMethod(char method,FamilyTree * tree) {
	string name;
	switch (method)
	{
	case 'A':
		cout << "请输入要建立家庭的人的姓名：";
		cin >> name;
		tree->createFamily(name);
		return false;
		break;
	case 'B':
		cout << "请输入要添加儿子(或女儿)的人的姓名：";
		cin >> name;
		tree->addFamilyMember(name);
		return false;
		break;
	case 'C':
		cout << "请输入要解散家庭的人的姓名：";
		cin >> name;
		tree->dissovePartFamily(name);
		return false;
		break;
	case 'D':
		cout << "请输入要更改姓名的人的目前姓名：";
		cin >> name;
		tree->changeNameForOneFameliyMember(name);
		return false;
		break;
	case 'E':
		return true;
	default:
		cout << "你输入的命令有误,请确认后再输入!!!!!\n";
		return false;
		break;
	}
}

int main() {
	welcomeImage();
	
	cout << "请输入祖先的姓名: ";
	string ancestor;
	cin >> ancestor;
	FamilyNode* indi = new FamilyNode(ancestor);
	if (indi == NULL) {
		cerr << "动态内存分配失败!!!!";
		exit(1);
	}
	cout << "此家谱的祖先是：" << ancestor<<endl<<endl;
	FamilyTree* tree = new FamilyTree(indi);
	while (1) {
		char Method;
		cout << "请选择要执行的操作：";
		cin >> Method;
		if (processMethod(Method,tree)) {
			break;
		}
	}
	getchar();
	getchar();
	return 0;
	
}
