#ifndef _MY_GRAPH_
#define _MY_GRAPH_
#include <iostream>
using namespace std;

struct Edge {
	int vertexIndex;
	int duration;
	Edge* nextEdge;
	Edge(int ve, int du, Edge* next = NULL):vertexIndex(ve),duration(du),nextEdge(next) {};
	int getIndex() { return vertexIndex; }
	int getDuration() { return duration; }
	Edge* getNextEdge() { return nextEdge; }
};

class LinkNode {
public:
	LinkNode(){}
	LinkNode(int index,Edge* tempLink = NULL):vertexIndex(index),link(tempLink){};
	void setLink(Edge* tempLink) {
		Edge* tempPara;
		tempPara = link;
		//���linkΪNULL,��link����ΪtempLink��ֵ
		if (link == NULL) {
			tempPara = tempLink;
		}
		else {
			//��֮���link��������,�ҵ�һ��û�к�̽ڵ�Ľڵ�,Ȼ����ĺ�̽ڵ�����ΪtempLink
			while (tempPara->nextEdge != NULL) {
				tempPara = tempPara->nextEdge;
			}
			tempPara->nextEdge = tempLink;
		}
	}
	Edge* getFirstEdge() { return link; }

	void deleteNode() {
		Edge* temp = link;
		if (link != NULL) {
			link = link->getNextEdge();
			delete temp;
		}
	}

private:
	Edge* link;
	int vertexIndex;
	
};


class Graph {
public:
	Graph(int n) {
		vertexNum = n;
		vertexV = new LinkNode*[n+1];
		//��ʼ��
		for (int i = 0; i <= n; i++) {
			vertexV[i] = NULL;
		}
	}
	~Graph() {
		deleteFun();
	}
	bool setLinkNode(int i, LinkNode* node) {
		if (vertexV[i] == NULL) {
			vertexV[i] = node;
			return true;
		}
		else {
			return false;
		}
	}
	LinkNode* getVertex(int index) {
		return vertexV[index];
	}
	

private:
	LinkNode ** vertexV;
	int vertexNum;
	void deleteFun() {
		for (int i = 0; i < vertexNum; i++) {
			if (vertexV[i] != NULL) {
				vertexV[i]->deleteNode();
				delete vertexV[i];
			}
		}
		delete[] vertexV;
	}
};

#endif // !_MY_GRAPH_

