#include <iostream>
#include <time.h>
#include <string>
#include "myHeap.h"
using namespace std;
const int radix = 10; // �������

void drawScreen() {
	cout << "**\t\t�����㷨�Ƚ�\t\t**\n"
		<< "==========================================\n"
		<< "**\t\t1 --- ð������\t\t**\n"
		<< "**\t\t2 --- ѡ������\t\t**\n"
		<< "**\t\t3 --- ֱ�Ӳ�������\t**\n"
		<< "**\t\t4 --- ϣ������\t\t**\n"
		<< "**\t\t5 --- ��������\t\t**\n"
		<< "**\t\t6 --- ������\t\t**\n"
		<< "**\t\t7 --- �鲢����\t\t**\n"
		<< "**\t\t8 --- ��������\t\t**\n"
		<< "**\t\t9 --- �˳�����\t\t**\n"
		<< "==========================================\n\n";
}


void coutResult(string sortName, int sortTimes, double sortCost);

void bubbleSort(int num);

void chooseSort(int num);

void insertSort(int num);

void shellSort(int num);

void useQuickSort(int num);

void heapSort(int num);

void useMergeSort(int num);

void useMSDsort(int num);
int main() {
	drawScreen();
	cout << "\n������Ҫ������������ĸ���:\t";
	int number;
	cin >> number;
	cout << "\n\n";
	int order;
	while (1) {
		cout << "��ѡ�������㷨:\t";
		cin >> order;
		bool out = false;
		switch (order)
		{
		case 1:
			bubbleSort(number);
			break;
		case 2:
			chooseSort(number);
			break;
		case 3:
			insertSort(number);
			break;
		case 4:
			shellSort(number);
			break;
		case 5:
			useQuickSort(number);
			break;
		case 6:
			heapSort(number);
			break;
		case 7:
			useMergeSort(number);
			break;
		case 8:
			useMSDsort(number);
			break;
		case 9:
			out = true;
			break;
		default:
			cout << "�����ָ��,��ȷ�Ϻ���������\n";
			break;
		}
		if (out) {
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}

bool judgeSort(int *numArray, int size) {
	for(int i = 0; i < size-1; i++) {
		if (numArray[i] > numArray[i + 1]) {
			return false;
		}
	}
	return true;
}

//����������,���ٴ��������
void coutResult(string sortName, long long sortTimes, double sortCost) {
	cout << sortName << "����ʱ��:\t" << sortCost << "ms\n";
	cout << sortName << "��������:\t" << sortTimes << "��\n\n";
}

//ð������
void bubbleSort(int num) {
	int* numArray = new int[num + 1];
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}
	clock_t start = clock();
	long long swapTime = 0;
	for (int i = 0; i < num; i++) {
		//�����ж��Ƿ��ڱ���ð�ݹ����д����޽��������(������δ����ð�ݵ�����ǡ�������������,����������)
		int swapPerTime = 0;
		for (int j = num - 1; j > i; j--) {
			if (numArray[j - 1] > numArray[j]) {
				int temp = numArray[j - 1];
				numArray[j - 1] = numArray[j];
				numArray[j] = temp;
				swapTime++;
				swapPerTime++;
			}
		}
		if (swapPerTime == 0) {
			break;
		}
	}
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("ð������", swapTime, costTime);

	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}


//ѡ������
void chooseSort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}

	clock_t start = clock();
	long long swapTime = 0;
	for (int i = 0; i < num - 1; i++) {
		//����Сֵ��ʼ��ΪINT�����͵����ֵ
		int min = INT_MAX;
		int minIndex = -1;
		for (int j = i; j < num; j++) {
			if (numArray[j] < min) {
				min = numArray[j];
				minIndex = j;
				swapTime++;
			}
		}
		int temp = numArray[i];
		numArray[i] = min;
		numArray[minIndex] = temp;
		swapTime++;
	}
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("ѡ������", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;

}

//ֱ�Ӳ�������
void insertSort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}

	clock_t start = clock();
	long long swapTime = 0;
	for (int i = 1; i < num; i++) {
		int j = i - 1;
		int temp = numArray[i];
		for (; j >= 0; j -= 1) {
			if (numArray[j] > temp) {
				numArray[j + 1] = numArray[j];
				swapTime++;
			}
			else {
				break;
			}
		}
		numArray[j + 1] = temp;
		swapTime++;
	}
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;

	coutResult("ֱ�Ӳ�������", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	
	delete[] numArray;
}

//ϣ������
void shellSort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}


	clock_t start = clock();
	long long swapTime = 0;
	int gap = num / 3 + 1;
	int count = 0;
	while (count == 0) {
		if (gap == 1) {
			count++;
		}
		for (int i = gap; i < num; i++) {
			int j = i - gap;
			int temp = numArray[i];
			for (; j >= 0; j -= gap) {
				if (numArray[j] > temp) {
					numArray[j + gap] = numArray[j];
					swapTime++;
				}
				else {
					break;
				}
			}
			numArray[j + gap] = temp;
			swapTime++;
		}
		gap = gap / 3 + 1;
	}
	
	clock_t end = clock();

	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("ϣ������", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}

//���ŷָ��㷨
int partition(int low, int high,int * numArray,long long& swapTime) {
	int pivotopos = low;
	int pivot = numArray[low];
	for (int i = low + 1; i <= high; i++) {
		if (numArray[i] < pivot) {
			pivotopos++;
			if (pivotopos != i) {
				int temp = numArray[i];
				numArray[i] = numArray[pivotopos];
				numArray[pivotopos] = temp;
				swapTime++;
			}
		}
	}
	numArray[low] = numArray[pivotopos];
	numArray[pivotopos] = pivot;
	swapTime++;
	return pivotopos;
}
//�ݹ�,ʹ��swapTime�����ý��н�����������
void quickSort(int *numArray, int low, int high,long long& swapTime) {
	if (low < high) {
		int pivotpos = partition(low, high, numArray, swapTime);
		quickSort(numArray, low, pivotpos - 1, swapTime);
		quickSort(numArray, pivotpos + 1, high, swapTime);
	}
}

void useQuickSort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}
	long long swapTime = 0;
	clock_t start = clock();
	quickSort(numArray, 0, num - 1,swapTime);
	clock_t end = clock();

	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("��������", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}

void heapSort(int num) {
	MaxHeap myHeap(num);
	clock_t start = clock();
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		myHeap.insert(rand());
	}
	for (int i = num - 1; i >= 1; i--) {
		myHeap.swap(0, i);
		myHeap.shiftDown(i - 1);
	}
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("������", myHeap.swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(myHeap.numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT

}

void merge(int *arrayOne, int first, int mid, int last, int * temp, long long& swapTime) {
	int left = first;
	int right = mid + 1;
	for (int i = first; i < last; i++) {
		temp[i] = arrayOne[i];
	}
	int count = first;
	//��������������ж�δִ�����
	while (left <= mid && right <= last) {
		if (temp[left] < temp[right]) {
			arrayOne[count++] = temp[left++];
			swapTime++;
		}
		else if (temp[right] < temp[left]) {
			arrayOne[count++] = temp[right++];
			swapTime++;
		}
		else
		{
			//��������ͬ���
			arrayOne[count++] = temp[left++];
			swapTime++;
			arrayOne[count++] = temp[right++];
			swapTime++;
		}
	}
	//���������δ��ͷ�����������Ѿ�����
	while (left <= mid) {
		arrayOne[count++] = temp[left++];
		swapTime++;
	}
	//���������δ��ͷ,���������Ѿ�����
	while (right <= last) {
		arrayOne[count++] = temp[right++];
		swapTime++;
	}
}

void mergeSort(int* numArray, int first, int last, int* temp, long long& swapTime) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(numArray, first, mid, temp,swapTime);
		mergeSort(numArray, mid + 1, last, temp,swapTime);
		merge(numArray, first, mid, last, temp,swapTime);
	}
}


void useMergeSort(int num) {
	int * numArray = new int[num + 1];
	int *temp = new int[num];
	srand((int)time(NULL));
	long long swapTime = 0;
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}
	clock_t start = clock();
	mergeSort(numArray, 0, num - 1, temp,swapTime);
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("�鲢����", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] temp;
	delete[] numArray;
}

//��õ�ǰ���ֵ����λ��
int getMaxDigit(int num) {
	int n = 1;
	while (static_cast<int> (num / pow(10,n))) {
		n++;
	}
	return n;
}
//��õ�ǰ���ֵĵ�nλ
int getDigit(int num,int n) {
	//������ 10^n �õ�����,�ٽ��������� 10^(n-1) �õ���λ������
	return static_cast<int>((num % static_cast<int>(pow(10, n))) / pow(10, n - 1));
}

void insertSortForMSD(int *numArray, int left, int right, long long &swapTime) {
	for (int i = left + 1; i <= right; i++) {
		int j = i - 1;
		int temp = numArray[i];
		for (; j >= 0; j -= 1) {
			if (numArray[j] > temp) {
				numArray[j + 1] = numArray[j];
				swapTime++;
			}
			else {
				break;
			}
		}
		numArray[j + 1] = temp;
		swapTime++;
	}
}

//��������Ϊ[left,right],�ұ�Ϊ������
void MSDsort(int *numArray, int left, int right, int index,long long &swapTime) {
	if (index <= 0) {
		//�ݹ���ֹ����,�������,����
		return;
	}
	if (right - left < 200) {
		insertSortForMSD(numArray, left, right, swapTime);
		return;
	}
	int i, j,tempLeft,tempRight;
	int count[radix];
	int* tempArray = new int[right - left + 1];
	
	//��ʼ����¼��λ������
	for (i = 0; i < radix; i++) {
		count[i] = 0;
	}
	//д��count��������ڵ�ǰλ����,ÿ�������е�Ԫ�صĸ���
	for (i = left; i <= right; i++) {
		count[getDigit(numArray[i], index)]++;
	}
	//�ض�����������λ��
	for (j = 1; j < radix; j++) {
		count[j] += count[j - 1];
	}
	//��ÿ���������д����ʱ����
	for (i = left; i <= right; i++) {
		j = getDigit(numArray[i], index);
		tempArray[count[j] - 1] = numArray[i];
		swapTime++;
		count[j]--;
	}
	//����ʱ�����е������浽���Ӧ�������洢������������
	for (i = left, j = 0; i <= right; i++, j++) {
		numArray[i] = tempArray[j];
		swapTime++;
	}
	for (j = 0; j < radix; j++) {
		tempLeft = left + count[j];
		if (j != radix - 1) {
			tempRight = left + count[j + 1] - 1;
		}
		else {
			tempRight = right;
		}
		
		MSDsort(numArray, tempLeft, tempRight, index - 1,swapTime);
	}
/*	for (int i = tempLeft; i < tempRight; i++) {
		cout << numArray[i] << "\t";
		if ((i + 1) % 5 == 0) {
			cout << endl << endl;
		}
	}*/
	delete[] tempArray;
}
/*
//��һ������MSDsortʱ���Ǹ������
void MSDsortFirst(int *numArray, int left, int right, int index, int &swapTime) {
	if (index <= 0) {
		//�ݹ���ֹ����,�������,����
		return;
	}
	int i, j;
	int count[2 * radix];
	int* tempArray = new int[right - left + 1];

	//��ʼ����¼��λ������
	for (i = 0; i < 2 * radix; i++) {
		count[i] = 0;
	}
	//д��count��������ڵ�ǰλ����,ÿ�������е�Ԫ�صĸ���
	for (i = left; i <= right; i++) {
		if (numArray[i] < 0) {
			count[-getDigit(numArray[i], index) + 9]++;
		}
		else {
			count[getDigit(numArray[i], index) + 9]++;
		}
		
	}
	//�ض�����������λ��
	for (j = 1; j < 2 * radix; j++) {
		count[j] += count[j - 1];
	}
	//��ÿ���������д����ʱ����
	for (i = left; i <= right; i++) {
		if (numArray[i] < 0) {
			j = 9 - getDigit(numArray[i], index);
		}
		else {
			j = 9 + getDigit(numArray[i], index);
		}
		
		tempArray[count[j] - 1] = numArray[i];
		swapTime++;
		count[j]--;
	}
	//����ʱ�����е������浽���Ӧ�������洢������������
	for (i = left, j = 0; i <= right; i++, j++) {
		numArray[i] = tempArray[j];
		swapTime++;
	}
	for (j = 0; j < 2 * radix - 1; j++) {
		left = count[j];
		right = count[j + 1] - 1;
		MSDsort(numArray, left, right, index - 1, swapTime);
	}

	delete[] tempArray;
}*/




void useMSDsort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}
	long long swapTime = 0;
	clock_t start = clock();
	int maxDigit = 0;
	//��ȡ������ɵ����е����λ��
	for (int i = 0; i < num; i++) {
		int index = getMaxDigit(numArray[i]);
		if ( index > maxDigit) {
			maxDigit = index;
		}
	}
	MSDsort(numArray, 0, num - 1, maxDigit, swapTime);
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("��������", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n�ж����:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}




