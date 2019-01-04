#include "Graph.h"
void cout_screen() {
	cout << "**\t\t�������ģ��ϵͳ\t\t**\n"
		<< "==================================================\n"
		<< "**\t\tA --- ������������\t\t**\n"
		<< "**\t\tB --- ��ӵ����ı�\t\t**\n"
		<< "**\t\tC --- ������С������\t\t**\n"
		<< "**\t\tD --- ��ʾ��С������\t\t**\n"
		<< "**\t\tE --- �˳�    ����\t\t**\n"
		<< "==================================================\n\n";
}
void primTree(EdgeNode* NodeVector, GraphMatrx* graph, char ch,int size) {
	int nodeNum = graph->getNodeNum();
	int edgeNum = graph->getEdgeNum();
	int count = 0;//�Ѿ�����һ������(�׶���)
	int firstIndex = graph->getNode(ch);
	//��ʼ��lowCost��nearVex����
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
		//�Ȼ�ȡ��ǰ������׸��ڽӵ�
		int tempIndex = graph->getFirstNeighbor(firstIndex);
		//������ڽӵ����,�����ѭ��
		while (tempIndex != -1) {
			//��ȡ������Ȩֵ
			int weight = graph->getWeight(firstIndex, tempIndex);
			//�����lowCost�д��С,�����lowCost��nearVex�е�ǰ���ڵ�
			if (weight < lowCost[tempIndex]) {
				lowCost[tempIndex] = weight;
				nearVex[tempIndex] = firstIndex;
			}
			tempIndex = graph->getNextNeighbor(firstIndex, tempIndex);
		}
		int min = MAX_INT;
		//��lowCost��ѡȡ����ѭ�������е���Сֵ
		for (int i = 0; i < size; i++) {
			if (nearVex[i] != -1 && lowCost[i] < min) {
				firstIndex = i;
				min = lowCost[i];
			}
		}
		//��Edge��ӽ�����,���������ⶥ���������,�����´�ѭ���Ըö��㿪ʼ
		EdgeNode tempNode;
		tempNode.head = nearVex[firstIndex];
		tempNode.tail = firstIndex;
		tempNode.weight = lowCost[firstIndex];
		nearVex[firstIndex] = -1;
		NodeVector[count++] = tempNode;
	}
	cout << "����Prim��С������!\n\n";
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
	//���ڽӾ������ʽ�洢��վ֮��ĳ���
	GraphMatrx* powerGraph = NULL;
	char * nodeVector = NULL;
	int num;
	bool isA = false;
	bool isB = false;
	bool isC = false;
	bool isContinue = true;
	EdgeNode* edgeVector = NULL;
	while (isContinue) {
		cout << "���������: ";
		char ch;
		cin >> ch;
		switch (ch)
		{
		case 'A':
			//����Ѿ�����A����,������ʾ
			if (isA) {
				cout << "���Ѿ���������,�������������\n";
			}
			else {
				//�������
				cout << "�����붥��ĸ���:";
			
				cin >> num;
				cout << "��������������������:\n";
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
				cout << "���Ƚ���A����\n";
				break;
			}
			int num = powerGraph->getNodeNum();
			char Lch;
			char Rch;
			int weight;
			do {
				cout << "�������������㼰��(ch,ch,int): ";
				cin >> Lch >> Rch >> weight;
			} while (!powerGraph->insertEdge(Lch, Rch, weight));
			cout << "\n";
			isB = true;
			break;
			}
		case 'C':
			if (!isA) {
				cout << "���Ƚ���A����\n";
				break;
			}
			else if (!isB) {
				cout << "���Ƚ���B����\n";
				break;
			}
			//TODO prime����
			cout << "��������ʼ����: ";
			char ch;
			cin >> ch;
			primTree(edgeVector, powerGraph,ch,num);
			isC = true;
			break;
		case 'D':
			if (!isA) {
				cout << "���Ƚ���A����\n";
				break;
			}
			else if (!isB) {
				cout << "���Ƚ���B����\n";
				break;
			}
			else if (!isC) {
				cout << "���Ƚ���C����\n";
				break;
			}
			cout << "��С�������Ķ��㼰��Ϊ: \n\n";
			//TODO;
			cout_primTree(edgeVector, powerGraph->getNodeNum() - 1, nodeVector);
			break;
		case 'E':
			isContinue = false;
			break;
		default:
			cout << "����Ĳ�����,��ȷ�Ϻ�������\n";
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