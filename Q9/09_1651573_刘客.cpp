#include "Graph.h"
struct Stack
{
	int *container;
	int currentIndex;
	Stack(int n) {
		container = new int[n + 1];
		currentIndex = -1;
	}
	
	void push(int num){
		container[++currentIndex] = num;
	}
	int getTop() {
		return container[currentIndex];
	}
	int pop() {
		return container[currentIndex--];
	}
	bool isEmpty() {
		return currentIndex == -1 ? true : false;
	}

	~Stack() {
		if (container != NULL) {
			delete container;
		}
	}

};
bool topiSort(Graph& graph, int *inPoint, int* sortVector, Stack& myStack,int size) {
	int count = 1;
	//�����Ϊ0�ĵ�������ջ��
	for (int i = 1; i < size; i++) {
		if (inPoint[i] == 0) {
			myStack.push(i);
			//sortVector �洢������������,���Ϊ0,�������sortVector��
			sortVector[count++] = i;
		}
	}

	//��ջ��Ϊ��ʱ,ȡ��ջ����Ԫ��,Ȼ����graph��Ѱ����ջ��Ԫ��Ϊ���ı�,����Щ�����ӵ��յ����ȼ�һ
	//����е��յ��һ�����Ϊ0�������ٶ�����ջ��
	while (!myStack.isEmpty()) {
		int index = myStack.pop();
		LinkNode* node = graph.getVertex(index);
		if (node == NULL) {
			//˵���ýڵ����յ�
			break;
		}
		Edge* tempEdge = node->getFirstEdge();
		while (tempEdge != NULL) {
			inPoint[tempEdge->getIndex()]--;
			if (inPoint[tempEdge->getIndex()] == 0) {
				myStack.push(tempEdge->getIndex());
				sortVector[count++] = tempEdge->getIndex();
			}
			tempEdge = tempEdge->getNextEdge();
		}
	}
	//��whileѭ������ʱ,�ж�����������Ƿ�����Ԫ�����ȫ��Ϊ0,����в�Ϊ0��Ԫ��,˵����������ʧ�ܷ���false
	for (int i = 1; i < size; i++) {
		if (inPoint[i] != 0) {
			return false;
		}
	}
	return true;
}

void findKeyActivity(Graph& graph, int* sortVector, int size) {
	int *Ve = new int[size];//���翪ʼʱ��Vector
	int *Vl = new int[size];//��ٿ�ʼʱ��Vector
	//��ʼ��
	for (int i = 0; i < size; i++) {
		Ve[i] = 0;
		//��ٿ�ʼʱ���ʼ��Ϊ���ֵ
		Vl[i] = INT_MAX;
	}
	//��ͨ��ѭ��������翪ʼʱ��Vector
	for (int i = 1; i < size - 1; i++) {
		int curIndex = sortVector[i];
		LinkNode* tempNode = graph.getVertex(curIndex);
		Edge* edge = tempNode->getFirstEdge();
		while (edge != NULL) {
			//index�Ǳߵ��յ�
			int index = edge->getIndex();
			//���Ve[ĳһ���] + edge[����㵽ĳһ�յ�] > Ve[ĳһ�յ�],��Ve[ĳһ�յ�]����
			if (Ve[curIndex] + edge->getDuration() > Ve[index]) {
				Ve[index] = Ve[curIndex] + edge->getDuration();
			}
			edge = edge->getNextEdge();
		}
	}
	//��ͨ��ѭ�������ٿ�ʼʱ��
	//�յ�����翪ʼʱ�����ٿ�ʼʱ����ͬ
	Vl[sortVector[size - 1]] = Ve[sortVector[size - 1]];
	cout <<"\n���ʱ��Ϊ: " <<Ve[sortVector[size - 1]] << endl<<endl;
	for (int i = size - 2; i >= 1; i--) {
		int curIndex = sortVector[i];
		LinkNode* tempNode = graph.getVertex(curIndex);
		Edge* edge = tempNode->getFirstEdge();
		while (edge != NULL) {
			int index = edge->getIndex();
			//���Vl[ĳһ���] + edge[����㵽ĳһ�յ�] > Vl[ĳһ�յ�],��Vl[ĳһ�յ�]����
			if (Vl[curIndex] > Vl[index] - edge->getDuration()) {
				Vl[curIndex] = Vl[index] - edge->getDuration();
			}
			edge = edge->getNextEdge();
		}
	}
	cout << "�ؼ��Ϊ:\n";
	//�����������Ve��Vl��������ؼ��
	for (int i = 1; i < size - 1; i++) {
		int curIndex = sortVector[i];
		int Ae = Ve[curIndex];
		LinkNode* tempNode = graph.getVertex(curIndex);
		Edge* edge = tempNode->getFirstEdge();
		int count = 0;
		while (edge != NULL) {
			count++;
			edge = edge->getNextEdge();
		}
		while (count != 0) {
			Edge* tempEdge = tempNode->getFirstEdge();
			for (int i = 1; i < count; i++) {
				tempEdge = tempEdge->getNextEdge();
			}
			int Al = Vl[tempEdge->getIndex()] - tempEdge->getDuration();
			//���Al == Ae,��˵��Ϊ�ؼ��
			if (Al == Ae) {
				cout << curIndex << " -> " << tempEdge->getIndex()<<endl;
			}
			count--;
		}
	}
}


int main() {
	int n, m;
	LinkNode* linkPara = NULL;
	Edge* edgePara = NULL;
	cout << "������N(���ӵ�����)��M(��������)\n===��ʽ(N M)===\n������: ";
	cin >> n >> m;
	Graph myGraph(n);
	//�������
	int *inPoint = new int[n + 1];
	//�洢������������
	int *sortVector = new int[n+1];
	//����ջ
	Stack myStack(n);
	//��ʼ�����
	for (int i = 0; i <= n; i++) {
		inPoint[i] = 0;
	}
	cout << "����������M��,ÿ�и���3��������(����ʼ���ӵ�A,������ɽ��ӵ�B,�Լ�����ʱ��C)\n===��ʽ(A B C)===\n"
		<< "������:\n";
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edgePara = new Edge(b, c);
		linkPara = new LinkNode(a,edgePara);
		inPoint[b]++;
		//�������ɹ�,�����ѭ��
		//����ɹ�,��������֮ǰGraph�еĶ��������в�û�иýڵ�
		//����ʧ��,��������֮ǰGraph�Ķ��������Ѿ�ӵ���˸ýڵ�
		if (myGraph.setLinkNode(a, linkPara)) {
			continue;
		}
		else {
			//����ķ����ڴ�,�����
			delete linkPara;
			myGraph.getVertex(a)->setLink(edgePara);
		}
	}
	//��������
	if (!topiSort(myGraph, inPoint, sortVector, myStack, n + 1)) {
		cout << 0;
	}
	else {
			findKeyActivity(myGraph, sortVector, n + 1);
	}



	getchar();
	getchar();
	return 0;


}