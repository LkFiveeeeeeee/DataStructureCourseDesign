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
		//如果link为NULL,则将link设置为tempLink的值
		if (link == NULL) {
			tempPara = tempLink;
		}
		else {
			//反之则从link向下搜索,找到一个没有后继节点的节点,然后将其的后继节点设置为tempLink
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
		//初始化
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

