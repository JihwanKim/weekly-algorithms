#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "main.h"
using namespace std;

/*
@�ۼ��� : jihwanKim
@�ۼ��� : 2018-06-17
@IDE : Visual Studio 2017
@��� : C++
�ı�
���� ��������, �ذ��� ��ü�� �����س��� ������ �󸶰ɸ��� �ʾҴµ�, �ͼ��������� C++�� ¥�ٺ���,
������ ����ؼ� �ϰ��־���.
getLastArrSumResult function�� ���߷�����������, ������ ���� �־����� ��, ���ԵǸ� O(n) �� ����.
ex [1,2,3] -> [1],[1,2],[1,2,3], [2],[2,3], [3]
ex [1,2,3,4,5] -> [1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5] , [2],[2,3],[2,3,4],[2,3,4,5], [3],[3,4],[3,4,5], [4],[4,5], [5]
 3���� ���ڿ� ���� ������ �� ��, 6����.
 5���� ���ڿ� ���� ������ �� ��, 15����.

arr ���� �������൵ ũ�Ⱑ 8�� ��µǴ� ������ ����. -> �ذ�� ã�µ��� �����ؼ� Ŀ�� �� �߰� �׽�Ʈ �ʿ�.

x64 ���� ����� ��� ��������� ��������.

10, -1, 3 -> 12
1,2,3 -> 6

=======================================================================================================
* �� ������ ��ó�� �������α׷����Դϴ�.
 https://mailprogramming.com/

 ������ �� ��� �ش� ����Ҵ� ������ �� �ֽ��ϴ�.
���� �迭(int array)�� �־����� ���� ū �̾����� ���ҵ��� ���� ���Ͻÿ�. ��, �ð����⵵�� O(n).
Given an integer array, find the largest consecutive sum of elements.
����}

Input: -1, 3, -1, 5
Output: 7 // 3 + (-1) + 5

Input: -5, -3, -1
Output: -1 // -1

Input: 2, 4, -2, -3, 8
Output: 9 // 2 + 4 + (-2) + (-3) + 8
*/


int main() {
	cout << "input the values. string length limit is 100 byte. delimiters : ',' please input value -> ";
	char strings[100] = "";
	scanf_s("%99s", strings, sizeof(strings));

	int i = 0;
	int * arr = splitStrAtCommaAndGetIntValue(strings);

	if (sizeof(arr)) {
		int value = arr[i];
		while (value) {
			i++;
			value = arr[i];
		}
	}
	printf_s("result : %i", getLastArrSumResult(arr, i+1));
	system("pause");
	return 0;
}


int* splitStrAtCommaAndGetIntValue(char * strings) {
	char * restStr = NULL;
	char * splitValues = strtok_s(strings, ",", &restStr);
	int *intValues = new int[5];
	int i = 0;
	while (splitValues) {
		intValues = checkArrLengthAndCurrentPosition(intValues, i);
		intValues[i] = atoi(splitValues);
		printf_s("value [%i] %i \n", i, intValues[i]);
		i++;
		splitValues = strtok_s(NULL, " ,", &restStr);
	}
	i--;
	int * returnArr = arrResize(intValues, i);
	printf_s("arr split result return size %i \n", sizeof(returnArr));
	return returnArr;
}

int * checkArrLengthAndCurrentPosition(int * intArr, int currentPosition) {
	int arrSize = sizeof(intArr);

	if (arrSize < currentPosition) {
		// copy new int values
		return arrResize(intArr, arrSize + arrSize / 2);
	}
	return intArr;
}

int * arrResize(int * intArr, int newSize) {
	int * newIntArr = new int[newSize];
	int size = sizeof(intArr);
	int loopSize = 0;
	printf_s("arr length resize %i to %i \n", size + 1, newSize + 1);
	if (size < newSize) {
		loopSize = size;
	}
	else {
		loopSize = newSize;
	}
	for (int i = 0; i < loopSize + 1 ; i++) {
		newIntArr[i] = intArr[i];
	}
	printf_s("return new arr %p to %p // size %d to %d\n", intArr, newIntArr, sizeof(intArr), sizeof(newIntArr));
	return newIntArr;

}

// ���߷�����������, ������ ���� �־����� ��, ���ԵǸ� O(n) �� ����.
// ex [1,2,3,4,5] -> [1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5] , [2],[2,3],[2,3,4],[2,3,4,5], [3],[3,4],[3,4,5], [4],[4,5], [5]
int getLastArrSumResult(int * arr, int size) {
	int maxValue = arr[0];
	for (int i = 0; i < size ; i++) {
		int newSum = 0;
		for (int j = i; j < size; j++) {
			newSum += arr[j];
			if (newSum > maxValue) {
				maxValue = newSum;
			}
		}
	}
	return maxValue;
}