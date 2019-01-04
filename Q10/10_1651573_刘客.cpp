#include <iostream>
#include <time.h>
#include <string>
#include "myHeap.h"
using namespace std;
const int radix = 10; // 定义基数

void drawScreen() {
	cout << "**\t\t排序算法比较\t\t**\n"
		<< "==========================================\n"
		<< "**\t\t1 --- 冒泡排序\t\t**\n"
		<< "**\t\t2 --- 选择排序\t\t**\n"
		<< "**\t\t3 --- 直接插入排序\t**\n"
		<< "**\t\t4 --- 希尔排序\t\t**\n"
		<< "**\t\t5 --- 快速排序\t\t**\n"
		<< "**\t\t6 --- 堆排序\t\t**\n"
		<< "**\t\t7 --- 归并排序\t\t**\n"
		<< "**\t\t8 --- 基数排序\t\t**\n"
		<< "**\t\t9 --- 退出程序\t\t**\n"
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
	cout << "\n请输入要产生的随机数的个数:\t";
	int number;
	cin >> number;
	cout << "\n\n";
	int order;
	while (1) {
		cout << "请选择排序算法:\t";
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
			cout << "错误的指令,请确认后重新输入\n";
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

//输出结果函数,减少代码冗余度
void coutResult(string sortName, long long sortTimes, double sortCost) {
	cout << sortName << "所用时间:\t" << sortCost << "ms\n";
	cout << sortName << "交换次数:\t" << sortTimes << "次\n\n";
}

//冒泡排序
void bubbleSort(int num) {
	int* numArray = new int[num + 1];
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}
	clock_t start = clock();
	long long swapTime = 0;
	for (int i = 0; i < num; i++) {
		//用来判断是否在本次冒泡过程中存在无交换的情况(即后续未进行冒泡的序列恰好满足排序规律,则无需再排)
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
	coutResult("冒泡排序", swapTime, costTime);

	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}


//选择排序
void chooseSort(int num) {
	int * numArray = new int[num + 1];
	srand((int)time(NULL));
	for (int i = 0; i < num; i++) {
		numArray[i] = rand();
	}

	clock_t start = clock();
	long long swapTime = 0;
	for (int i = 0; i < num - 1; i++) {
		//将最小值初始化为INT的类型的最大值
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
	coutResult("选择排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;

}

//直接插入排序
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

	coutResult("直接插入排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	
	delete[] numArray;
}

//希尔排序
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
	coutResult("希尔排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}

//快排分割算法
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
//递归,使用swapTime的引用进行交换次数计数
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
	coutResult("快速排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
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
	coutResult("堆排序", myHeap.swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(myHeap.numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT

}

void merge(int *arrayOne, int first, int mid, int last, int * temp, long long& swapTime) {
	int left = first;
	int right = mid + 1;
	for (int i = first; i < last; i++) {
		temp[i] = arrayOne[i];
	}
	int count = first;
	//如果左右两个序列都未执行完毕
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
			//两个数相同情况
			arrayOne[count++] = temp[left++];
			swapTime++;
			arrayOne[count++] = temp[right++];
			swapTime++;
		}
	}
	//如果左序列未到头，而右序列已经结束
	while (left <= mid) {
		arrayOne[count++] = temp[left++];
		swapTime++;
	}
	//如果右序列未到头,而左序列已经结束
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
	coutResult("归并排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] temp;
	delete[] numArray;
}

//获得当前数字的最大位数
int getMaxDigit(int num) {
	int n = 1;
	while (static_cast<int> (num / pow(10,n))) {
		n++;
	}
	return n;
}
//获得当前数字的第n位
int getDigit(int num,int n) {
	//先整除 10^n 得到余数,再将余数除以 10^(n-1) 得到首位的数字
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

//数的区间为[left,right],右边为闭区间
void MSDsort(int *numArray, int left, int right, int index,long long &swapTime) {
	if (index <= 0) {
		//递归终止条件,处理完毕,返回
		return;
	}
	if (right - left < 200) {
		insertSortForMSD(numArray, left, right, swapTime);
		return;
	}
	int i, j,tempLeft,tempRight;
	int count[radix];
	int* tempArray = new int[right - left + 1];
	
	//初始化记录数位的数组
	for (i = 0; i < radix; i++) {
		count[i] = 0;
	}
	//写入count数组关于在当前位数下,每个数所有的元素的个数
	for (i = left; i <= right; i++) {
		count[getDigit(numArray[i], index)]++;
	}
	//重定向各个区间的位置
	for (j = 1; j < radix; j++) {
		count[j] += count[j - 1];
	}
	//将每个区域的数写入临时数组
	for (i = left; i <= right; i++) {
		j = getDigit(numArray[i], index);
		tempArray[count[j] - 1] = numArray[i];
		swapTime++;
		count[j]--;
	}
	//将临时数组中的数保存到相对应的真正存储的数组区间中
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
//第一次运行MSDsort时考虑负数情况
void MSDsortFirst(int *numArray, int left, int right, int index, int &swapTime) {
	if (index <= 0) {
		//递归终止条件,处理完毕,返回
		return;
	}
	int i, j;
	int count[2 * radix];
	int* tempArray = new int[right - left + 1];

	//初始化记录数位的数组
	for (i = 0; i < 2 * radix; i++) {
		count[i] = 0;
	}
	//写入count数组关于在当前位数下,每个数所有的元素的个数
	for (i = left; i <= right; i++) {
		if (numArray[i] < 0) {
			count[-getDigit(numArray[i], index) + 9]++;
		}
		else {
			count[getDigit(numArray[i], index) + 9]++;
		}
		
	}
	//重定向各个区间的位置
	for (j = 1; j < 2 * radix; j++) {
		count[j] += count[j - 1];
	}
	//将每个区域的数写入临时数组
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
	//将临时数组中的数保存到相对应的真正存储的数组区间中
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
	//获取随机生成的数中的最高位数
	for (int i = 0; i < num; i++) {
		int index = getMaxDigit(numArray[i]);
		if ( index > maxDigit) {
			maxDigit = index;
		}
	}
	MSDsort(numArray, 0, num - 1, maxDigit, swapTime);
	clock_t end = clock();
	double costTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	coutResult("基数排序", swapTime, costTime);
	#ifdef _JUDGE_SORT
		cout << "\n判断情况:\t" << judgeSort(numArray, num) << "\n\n";
	#endif // !_JUDGE_SORT
	delete[] numArray;
}




