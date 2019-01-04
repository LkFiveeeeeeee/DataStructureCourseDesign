#ifndef _GRAPH_
#define _GRAPH_
#include <iostream>
#define MAX_INT 99999
using namespace std;
class GraphMatrx {
public:
	//��ʼ��
	//param1 �������
	GraphMatrx(int num) :nodeNum(num), edgeNum(0) {
		matrx = new int*[num + 1];
		for (int i = 0; i < num; i++) {
			*(matrx + i) = new int[num + 1];
		}
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				matrx[i][j] = MAX_INT;
			}
		}
	}

	~GraphMatrx() {
		for (int i = 0; i < nodeNum; i++) {
			delete []matrx[i];
		}
		delete[] matrx;
	}
	//���ö�������
	void setNodeVector(char* vector) { nodeVector = vector; }

	//return value
	//-1 -��δ�ҵ�
	//else ��Ϊ����vector����
	int getNode(char ch) {
		for (int i = 0; i < getNodeNum(); i++) {
			if (ch == nodeVector[i]) {
				return i;
			}
		}
		return -1;
	}

	//ֱ�Ӵ��ڽӾ����в���
	int getFirstNeighbor(int m) {
		for (int i = 0; i < nodeNum; i++) {
			if (matrx[m][i] != MAX_INT) {
				return i;
			}
		}
		return -1;
	}

	int getNextNeighbor(int m, int w) {
		bool isPass = false;
		for (int i = 0; i < nodeNum; i++) {
			if (isPass) {
				if (matrx[m][i] != MAX_INT) {
					return i;
				}
			}
			if (i == w) {
				isPass = true;
			}

		}
		return -1;
	}

	//return value
	//true -�� ��ֹ�������
	//false -����������,������Ϣ�ں����ڲ��Ѿ���ʾ
	bool insertEdge(char fNode, char sNode, int weight) {
		if (fNode == '?' && sNode == '?' && weight == 0) {
			if (isFullConnect()) {
				return true;
			}
			else {
				cout << "���ĸ�������֮�䲢δȫ����ͬ,��ȷ�����Ľڵ��Ƿ���ȷ\n";
				return false;
			}
		}
		if (fNode == sNode) {
			cout << "����ĵ���վ����Ϣ,��ȷ�Ϻ�������\n";
			return false;
		}
		int fIndex = getNode(fNode);
		int sIndex = getNode(sNode);
		//δ֪�ڵ����
		if (fIndex == -1 || sIndex == -1) {
			cerr << "����Ľڵ���Ϣ,����������\n";
			return false;
		}
		//���д���
		if (matrx[fIndex][sIndex] != MAX_INT || matrx[sIndex][fIndex] != MAX_INT) {
			cerr << "�������ڵ�֮���Ѿ�����Ȩ��,�������Ľڵ��Ƿ�������ȷ\n ";
			return false;
		}
		matrx[fIndex][sIndex] = weight;
		matrx[sIndex][fIndex] = weight;
		edgeNum++;
		return false;
	}

	//return value
	int getWeight(int fIndex, int sIndex) {
		return matrx[fIndex][sIndex];
	}

	int getNodeNum() { return nodeNum; }
	int getEdgeNum() { return edgeNum; }

private:
	char* nodeVector;
	int** matrx;
	int nodeNum;
	int edgeNum;
	//��һ���̶����жϵ�ǰ�����ͼ�Ƿ���ͨ
	bool isFullConnect() {
		for (int i = 0; i < nodeNum; i++) {
			for (int j = 0; j < nodeNum; j++) {
				if (matrx[i][j] != MAX_INT) {
					break;
				}
				if (j == nodeNum - 1) {
					return false;
				}
			}
		}
		return true;
	}
};


struct EdgeNode {
	int head;
	int tail;
	int weight;
};



#endif // !_GRAPH_

