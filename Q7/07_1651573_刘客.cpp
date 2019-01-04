#include "HuffmanTree.h"
#include <ctype.h>

int main() {
	int num;
	int totalLength = 0;
	int cost = 0;
	cout << "输入要收集的木头的个数: ";
	cin >> num;
	
	cout << "输入每个木头的长度:\n";

	if (num == 1) {
		cin >> num;
		cout << "0";
	}
	else {
		HuffmanTree* huffTree = new HuffmanTree(num);
		for (int i = 0; i < num; i++) {
			int length;
			cin >> length;

			huffTree->insertNode(new HuffmanNode(length));
		}
		HuffmanNode *left;
		HuffmanNode *right;
		//使用循环,当堆不为空时,持续进行循环
		//每次推出两个节点, 进行merge操作, 再将生成的节点推入堆中
		while (!huffTree->isEmptey()) {
			bool empty = false;
			left = huffTree->remove();
			right = huffTree->remove();
			if (huffTree->isEmptey()) {
				empty = true;
			}
			huffTree->mergeTree(left, right);
			if (empty) {
				break;
			}
		}
		cost = huffTree->countWeight(huffTree->getRoot());
		cout << cost;
	}
	
	getchar();
	getchar();

	return 0;
}