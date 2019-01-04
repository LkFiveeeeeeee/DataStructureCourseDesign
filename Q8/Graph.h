#ifndef _GRAPH_
#define _GRAPH_
#include <iostream>
#define MAX_INT 99999
using namespace std;
class GraphMatrx {
public:
	//初始化
	//param1 顶点个数
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
	//设置顶点数组
	void setNodeVector(char* vector) { nodeVector = vector; }

	//return value
	//-1 -》未找到
	//else 则为顶点vector索引
	int getNode(char ch) {
		for (int i = 0; i < getNodeNum(); i++) {
			if (ch == nodeVector[i]) {
				return i;
			}
		}
		return -1;
	}

	//直接从邻接矩阵中查找
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
	//true -》 终止插入操作
	//false -》持续插入,错误信息在函数内部已经提示
	bool insertEdge(char fNode, char sNode, int weight) {
		if (fNode == '?' && sNode == '?' && weight == 0) {
			if (isFullConnect()) {
				return true;
			}
			else {
				cout << "您的各个电网之间并未全部连同,请确认您的节点是否正确\n";
				return false;
			}
		}
		if (fNode == sNode) {
			cout << "错误的电网站点信息,请确认后在输入\n";
			return false;
		}
		int fIndex = getNode(fNode);
		int sIndex = getNode(sNode);
		//未知节点错误
		if (fIndex == -1 || sIndex == -1) {
			cerr << "错误的节点信息,请重新输入\n";
			return false;
		}
		//已有错误
		if (matrx[fIndex][sIndex] != MAX_INT || matrx[sIndex][fIndex] != MAX_INT) {
			cerr << "这两个节点之间已经有了权重,请检查您的节点是否输入正确\n ";
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
	//在一定程度上判断当前输入的图是否连通
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

