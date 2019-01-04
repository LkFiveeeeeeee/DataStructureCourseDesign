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
	//将入度为0的点先推入栈中
	for (int i = 1; i < size; i++) {
		if (inPoint[i] == 0) {
			myStack.push(i);
			//sortVector 存储拓扑排序序列,入度为0,则将其放入sortVector中
			sortVector[count++] = i;
		}
	}

	//当栈不为空时,取出栈顶的元素,然后在graph中寻找以栈顶元素为起点的边,将这些边连接的终点的入度减一
	//如果有的终点减一后入度为0，则将其再度推入栈中
	while (!myStack.isEmpty()) {
		int index = myStack.pop();
		LinkNode* node = graph.getVertex(index);
		if (node == NULL) {
			//说明该节点是终点
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
	//当while循环结束时,判断入度数组中是否所有元素入度全部为0,如果有不为0的元素,说明拓扑排序失败返回false
	for (int i = 1; i < size; i++) {
		if (inPoint[i] != 0) {
			return false;
		}
	}
	return true;
}

void findKeyActivity(Graph& graph, int* sortVector, int size) {
	int *Ve = new int[size];//最早开始时间Vector
	int *Vl = new int[size];//最迟开始时间Vector
	//初始化
	for (int i = 0; i < size; i++) {
		Ve[i] = 0;
		//最迟开始时间初始化为最大值
		Vl[i] = INT_MAX;
	}
	//先通过循环填充最早开始时间Vector
	for (int i = 1; i < size - 1; i++) {
		int curIndex = sortVector[i];
		LinkNode* tempNode = graph.getVertex(curIndex);
		Edge* edge = tempNode->getFirstEdge();
		while (edge != NULL) {
			//index是边的终点
			int index = edge->getIndex();
			//如果Ve[某一起点] + edge[该起点到某一终点] > Ve[某一终点],则将Ve[某一终点]更新
			if (Ve[curIndex] + edge->getDuration() > Ve[index]) {
				Ve[index] = Ve[curIndex] + edge->getDuration();
			}
			edge = edge->getNextEdge();
		}
	}
	//再通过循环算出最迟开始时间
	//终点的最早开始时间和最迟开始时间相同
	Vl[sortVector[size - 1]] = Ve[sortVector[size - 1]];
	cout <<"\n最短时间为: " <<Ve[sortVector[size - 1]] << endl<<endl;
	for (int i = size - 2; i >= 1; i--) {
		int curIndex = sortVector[i];
		LinkNode* tempNode = graph.getVertex(curIndex);
		Edge* edge = tempNode->getFirstEdge();
		while (edge != NULL) {
			int index = edge->getIndex();
			//如果Vl[某一起点] + edge[该起点到某一终点] > Vl[某一终点],则将Vl[某一终点]更新
			if (Vl[curIndex] > Vl[index] - edge->getDuration()) {
				Vl[curIndex] = Vl[index] - edge->getDuration();
			}
			edge = edge->getNextEdge();
		}
	}
	cout << "关键活动为:\n";
	//最后根据算出的Ve和Vl数据来求关键活动
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
			//如果Al == Ae,则说明为关键活动
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
	cout << "请输入N(交接点数量)和M(任务数量)\n===格式(N M)===\n请输入: ";
	cin >> n >> m;
	Graph myGraph(n);
	//入度数组
	int *inPoint = new int[n + 1];
	//存储拓扑排序序列
	int *sortVector = new int[n+1];
	//辅助栈
	Stack myStack(n);
	//初始化入度
	for (int i = 0; i <= n; i++) {
		inPoint[i] = 0;
	}
	cout << "请依次输入M行,每行给出3个正整数(任务开始交接点A,任务完成交接点B,以及任务时间C)\n===格式(A B C)===\n"
		<< "请输入:\n";
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edgePara = new Edge(b, c);
		linkPara = new LinkNode(a,edgePara);
		inPoint[b]++;
		//如果插入成功,则继续循环
		//插入成功,代表在这之前Graph中的顶点数组中并没有该节点
		//插入失败,代表在这之前Graph的顶点数组已经拥有了该节点
		if (myGraph.setLinkNode(a, linkPara)) {
			continue;
		}
		else {
			//多余的分配内存,清理掉
			delete linkPara;
			myGraph.getVertex(a)->setLink(edgePara);
		}
	}
	//拓扑排序
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