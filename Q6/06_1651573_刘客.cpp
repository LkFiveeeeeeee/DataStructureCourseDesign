#include "FamilyTree.h"

void welcomeImage() {
	cout << "**\t\t" << "���׹���ϵͳ" << "\t\t\t**\n";
	cout << "==================================================\n";
	cout << "**\t      ��ѡ��Ҫִ�еĲ��� ��       \t**\n";
	cout << "**\t\tA --- ���Ƽ��� \t\t\t**\n";
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**\n";
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**\n";
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**\n";
	cout << "**\t\tE --- �˳�����\t\t\t**\n";
	cout << "==================================================\n";
	cout << "���Ƚ���һ������!\n";
}

bool processMethod(char method,FamilyTree * tree) {
	string name;
	switch (method)
	{
	case 'A':
		cout << "������Ҫ������ͥ���˵�������";
		cin >> name;
		tree->createFamily(name);
		return false;
		break;
	case 'B':
		cout << "������Ҫ��Ӷ���(��Ů��)���˵�������";
		cin >> name;
		tree->addFamilyMember(name);
		return false;
		break;
	case 'C':
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> name;
		tree->dissovePartFamily(name);
		return false;
		break;
	case 'D':
		cout << "������Ҫ�����������˵�Ŀǰ������";
		cin >> name;
		tree->changeNameForOneFameliyMember(name);
		return false;
		break;
	case 'E':
		return true;
	default:
		cout << "���������������,��ȷ�Ϻ�������!!!!!\n";
		return false;
		break;
	}
}

int main() {
	welcomeImage();
	
	cout << "���������ȵ�����: ";
	string ancestor;
	cin >> ancestor;
	FamilyNode* indi = new FamilyNode(ancestor);
	if (indi == NULL) {
		cerr << "��̬�ڴ����ʧ��!!!!";
		exit(1);
	}
	cout << "�˼��׵������ǣ�" << ancestor<<endl<<endl;
	FamilyTree* tree = new FamilyTree(indi);
	while (1) {
		char Method;
		cout << "��ѡ��Ҫִ�еĲ�����";
		cin >> Method;
		if (processMethod(Method,tree)) {
			break;
		}
	}
	getchar();
	getchar();
	return 0;
	
}
