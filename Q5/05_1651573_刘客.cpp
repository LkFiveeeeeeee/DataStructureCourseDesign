#include<iostream>
using namespace std;
//自定义队列
struct myQuene
{
	int num[1001];
	int first;  //队列首指针
	int last;   //队列尾指针
};

int main() {
	myQuene queneA;
	myQuene queneB;
	//初始化A、B队列首尾指针
	queneA.first = 0; 
	queneB.first = 0;
	queneA.last = 0;
	queneB.last = 0;

	int peopleNum;
	int customerNum;
	//将处理计数时间设置为1,则每当countTime为偶数时,对B队列进行处理
	int countTime = 1;
	cout << "请输入顾客总数: ";
	cin >> peopleNum;
	if (peopleNum != 0) {
		cout << "请输入顾客编号: ";
	}
	//输入顾客编号
	for (auto i = 1; i <= peopleNum; i++) {
		cin >> customerNum;
		if (customerNum % 2 != 0) {
			//将尾指针递增,存储数据
			queneA.num[queneA.last++] = customerNum;
		}
		else {
			queneB.num[queneB.last++] = customerNum;
		}
	}

	//用来判断是否队列输出完毕,以此来判断是否需要输出" "(最后一位不应该输出空格)
	bool judgeAend = (queneA.first == queneA.last);
	bool judgeBend = (queneB.first == queneB.last);
	
	if (peopleNum != 0) {
		cout << "处理顺序为: ";
	}
	else {
		cout << "无顾客,不需要进行处理!";
	}

	while (!judgeAend || !judgeBend) {
		if (!judgeAend) {
			//当A队列未处理完毕时,进行处理
			cout << queneA.num[queneA.first++];
			//如果处理一个编号后,发现队列已经处理完毕
			if (queneA.first == queneA.last) {
				//将标志量设置为true
				judgeAend = true;
				if (judgeBend) {
					//如果B也已经处理完毕,则表明所有的顾客编号都已经处理完毕,此时不需要输出空格,直接break;
					break;
				}
			}
			//如果不然,则输出空格
			cout << " ";
		}
		//因为A队列的速度是B队列的两倍,所以只有计时为偶数时(countTime初始值为1),才对B进行处理,其他逻辑与A队列相同
		if (countTime % 2 == 0 && !judgeBend) {
			cout << queneB.num[queneB.first++];
			if (queneB.first == queneB.last) {
				judgeBend = true;
				if (judgeAend) {
					break;
				}
			}
			cout << " ";
		}
		countTime++;
	}

	getchar();
	getchar();
	return 0;


}