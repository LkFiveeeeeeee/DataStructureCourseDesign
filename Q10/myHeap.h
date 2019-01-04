#ifndef _MY_HEAP
#define _MY_HEAP
struct MaxHeap
{
	int *numArray;
	int count = -1;
	long long swapTime = 0;
	MaxHeap(int num) {
		numArray = new int[num];
	}
	void shiftDown(int size) {
		int i = 0;//start
		int j = 2 * i + 1; // 2 * start + 1;
		int temp = numArray[i];
		while(j <= size){
			if (j < size && numArray[j] < numArray[j + 1]){
				j++;
			}
			if (temp < numArray[j]) {
				numArray[i] = numArray[j];
				swapTime++;
				i = j;
				j = 2 * j + 1;
			}
			else {
				break;
			}
		}
		numArray[i] = temp;
		swapTime++;
	}
	void shiftUp(int start) {
		int i = start;
		int j = (start - 1) / 2;
		int temp = numArray[i];
		while (i > 0) {
			if (numArray[j] >= temp) {
				break;
			}
			else {
				numArray[i] = numArray[j];
				i = j;
				j = (j - 1) / 2;
				swapTime++;
			}
		}
		numArray[i] = temp;
		swapTime++;
	}
	void insert(int num) {
		numArray[++count] = num;
		shiftUp(count);
	}
	void swap(int pos1, int pos2) {
		int temp = numArray[pos1];
		numArray[pos1] = numArray[pos2];
		numArray[pos2] = temp;
		swapTime++;
	}
	~MaxHeap() {
		delete numArray;
	}
};

#endif // !#_MY_HEAP

