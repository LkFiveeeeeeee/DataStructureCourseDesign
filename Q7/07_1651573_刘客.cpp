#include "HuffmanTree.h"
#include <ctype.h>

int main() {
	int num;
	int totalLength = 0;
	int cost = 0;
	cout << "����Ҫ�ռ���ľͷ�ĸ���: ";
	cin >> num;
	
	cout << "����ÿ��ľͷ�ĳ���:\n";

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
		//ʹ��ѭ��,���Ѳ�Ϊ��ʱ,��������ѭ��
		//ÿ���Ƴ������ڵ�, ����merge����, �ٽ����ɵĽڵ��������
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