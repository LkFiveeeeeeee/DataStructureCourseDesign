#include "Graph.h"
void cout_screen() {
	cout << "**\t\t电网造价模拟系统\t\t**\n"
		<< "==================================================\n"
		<< "**\t\tA --- 创建电网顶点\t\t**\n"
		<< "**\t\tB --- 添加电网的边\t\t**\n"
		<< "**\t\tC --- 构造最小生成树\t\t**\n"
		<< "**\t\tD --- 显示最小生成树\t\t**\n"
		<< "**\t\tE --- 退出    程序\t\t**\n"
		<< "==================================================\n\n";
}
void primTree(EdgeNode* NodeVector, GraphMatrx* graph, char ch,int size) {
	int nodeNum = graph->getNodeNum();
	int edgeNum = graph->getEdgeNum();
	int count = 0;//已经分离一个顶点(首顶点)
	int firstIndex = graph->getNode(ch);
	//初始化lowCost与nearVex数组
	int *lowCost = new int[size];
	int *nearVex = new int[size];
	for (int i = 0; i < size; i++) {
		if (firstIndex == i) {
			lowCost[i] = 0;
			nearVex[i] = -1;
		}
		else {
			lowCost[i] = MAX_INT;
			nearVex[i] = 0;
		}
	}
	
	while (count != size) {
		//先获取当前顶点的首个邻接点
		int tempIndex = graph->getFirstNeighbor(firstIndex);
		//如果该邻接点存在,则进入循环
		while (tempIndex != -1) {
			//获取两点间的权值
			int weight = graph->getWeight(firstIndex, tempIndex);
			//如果比lowCost中存的小,则更新lowCost和nearVex中的前驱节点
			if (weight < lowCost[tempIndex]) {
				lowCost[tempIndex] = weight;
				nearVex[tempIndex] = firstIndex;
			}
			tempIndex = graph->getNextNeighbor(firstIndex, tempIndex);
		}
		int min = MAX_INT;
		//从lowCost中选取本次循环过程中的最小值
		for (int i = 0; i < size; i++) {
			if (nearVex[i] != -1 && lowCost[i] < min) {
				firstIndex = i;
				min = lowCost[i];
			}
		}
		//将Edge添加进数组,并将该树外顶点加入树内,并且下次循环以该顶点开始
		EdgeNode tempNode;
		tempNode.head = nearVex[firstIndex];
		tempNode.tail = firstIndex;
		tempNode.weight = lowCost[firstIndex];
		nearVex[firstIndex] = -1;
		NodeVector[count++] = tempNode;
	}
	cout << "生成Prim最小生成树!\n\n";
	delete[] lowCost;
	delete[] nearVex;
}

void cout_primTree(EdgeNode* vector, int num, char* chV) {
	for (int i = 0; i < num; i++) {
		cout << chV[vector[i].head] << "-<" << vector[i].weight << ">-" << chV[vector[i].tail] << "\t\t\t\t";
		if ((i+1) % 3 == 0) {
			cout << "\n";
		}
	}
	cout << "\n";
	cout << "\n";
}

void process() {
	//以邻接矩阵的形式存储电站之间的长度
	GraphMatrx* powerGraph = NULL;
	char * nodeVector = NULL;
	int num;
	bool isA = false;
	bool isB = false;
	bool isC = false;
	bool isContinue = true;
	EdgeNode* edgeVector = NULL;
	while (isContinue) {
		cout << "请输入操作: ";
		char ch;
		cin >> ch;
		switch (ch)
		{
		case 'A':
			//如果已经进行A操作,给出提示
			if (isA) {
				cout << "您已经建立电网,请进行其他操作\n";
			}
			else {
				//读入操作
				cout << "请输入顶点的个数:";
			
				cin >> num;
				cout << "请依次输入各顶点的名称:\n";
				char tempCh;
				powerGraph = new GraphMatrx(num);
				nodeVector = new char[num + 1];
				edgeVector = new EdgeNode[num + 1];
				for (int i = 0; i < num; i++) {
					cin >> tempCh;
					nodeVector[i] = tempCh;
				}
				powerGraph->setNodeVector(nodeVector);
				isA = true;
			}
			cout << "\n";
			break;
		case 'B': {
			if (!isA) {
				cout << "请先进行A操作\n";
				break;
			}
			int num = powerGraph->getNodeNum();
			char Lch;
			char Rch;
			int weight;
			do {
				cout << "请输入两个顶点及边(ch,ch,int): ";
				cin >> Lch >> Rch >> weight;
			} while (!powerGraph->insertEdge(Lch, Rch, weight));
			cout << "\n";
			isB = true;
			break;
			}
		case 'C':
			if (!isA) {
				cout << "请先进行A操作\n";
				break;
			}
			else if (!isB) {
				cout << "请先进行B操作\n";
				break;
			}
			//TODO prime操作
			cout << "请输入起始顶点: ";
			char ch;
			cin >> ch;
			primTree(edgeVector, powerGraph,ch,num);
			isC = true;
			break;
		case 'D':
			if (!isA) {
				cout << "请先进行A操作\n";
				break;
			}
			else if (!isB) {
				cout << "请先进行B操作\n";
				break;
			}
			else if (!isC) {
				cout << "请先进行C操作\n";
				break;
			}
			cout << "最小生成树的顶点及边为: \n\n";
			//TODO;
			cout_primTree(edgeVector, powerGraph->getNodeNum() - 1, nodeVector);
			break;
		case 'E':
			isContinue = false;
			break;
		default:
			cout << "错误的操作符,请确认后再输入\n";
			break;
		}
	}
	delete nodeVector;
	delete powerGraph;
	delete edgeVector;
}




int main() {
	cout_screen();


	process();

	getchar();
	getchar();
	return 0;
}