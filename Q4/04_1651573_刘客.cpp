#include <iostream>
#include <stack>
#include <string>
using namespace std;

void processCin(string* stringV,int& count) {
	count = 0;
	while (1) {
		char c;
		string tempStr = "";
		bool isEndl = false;//��־�Ƿ��������
		while ((c = getchar()) != ' ') {
			if (c == '\n') {
				isEndl = true;
				break;
			}
			else {
				tempStr = tempStr + c;
			}
		}
		if (tempStr.size() > 1 && tempStr[0] == '+') {
			tempStr = tempStr.substr(1, tempStr.size());
		}
		stringV[count++] = tempStr;
		if (isEndl) {
			break;
		}
	}
}

int inStackOp(char op) {
	switch (op)
	{
	case '#':
		return 0;
	case '(':
		return 1;
		break;
	case '+':
	case '-':
		return 3;
		break;
	case '*':
	case '/':
		return 5;
		break;
	default:
		return -1;
		break;
	}
}

int outStackOp(char op) {
	switch (op)
	{
	case ')':
		return 1;
		break;
	case '+':
	case '-':
		return 2;
		break;
	case '*':
	case '/':
		return 4;
		break;
	case '(':
		return 6;
		break;
	default:
		return -1;
		break;
	}
}



//@@returnValue  Type==>int
// 1 ==> OUT > IN
// 0 ==> OUT == IN
//-1 ==> OUT < IN
int outCompareIn(string outStr,stack<string>& strStack) {
	//������ַ��������
	if (outStr.compare("") == 0) {
		return -1;
	}
	string inStr = strStack.top();
	int inNum = inStackOp(inStr[0]);
	int outNum = outStackOp(outStr[0]);
	if (outNum > inNum) {
		return 1;
	}
	else if (outNum == inNum) {
		return 0;
	}
	else {
		return -1;
	}
}

int main() {
	stack<string> strStack;
	strStack.push("#");

	string stringV[20];
	int count = 0;//����size

	

	processCin(stringV, count);
	

	int index = 0;

	bool isEndl = false;//��־�Ƿ��������
	while (!strStack.empty()) {

		string tempStr;
		if (index != count) {
			tempStr = stringV[index++];
		}
		else {
			tempStr = "";
			isEndl = true;
		}
	

		//���������ֱ�����
		if (tempStr.compare("") != 0 && (isdigit(tempStr[0]) || tempStr.size() > 1)) {
			
			if (count == 1) {
				cout << tempStr;
				break;


			}
			else {
				cout << tempStr<< " ";
			}

		}
		else {
			//whileѭ��Ϊ�˴��� �ⲿ���ȼ������ڲ������,��Ϊ�����������ջ�������
			while (1) {
				if (outCompareIn(tempStr, strStack) > 0) {
						//������������ȼ�����,����push����
					strStack.push(tempStr);
					break;
				}
				else if (outCompareIn(tempStr, strStack) == 0) {
					//��ʱֻ�ᷢ��һ�����,��������������,��ʱֱ��pop;
					strStack.pop();
					break;
				}
				else {
					//��ʱ�ڲ���������ȼ�����,��������ڲ������
					//ֻ��һ�����ֵ����
					if (strStack.size() == 1) {
						break;
					}
					string coutStr = strStack.top();
					strStack.pop();
					if (strStack.size() != 1 || !isEndl) {
						cout << coutStr << " ";
					}
					else {
						//����β���ո�
						cout << coutStr;
						strStack.pop();
						break;
					}
				
				}
			}
		}

	}

	getchar();
	getchar();
	getchar();
	return 0;
}