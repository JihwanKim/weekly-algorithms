#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "main.h"
using namespace std;

/*
@작성자 : jihwanKim
@작성일 : 2018-06-17
@IDE : Visual Studio 2017
@언어 : C++
후기
비교적 쉬운문제였어서, 해결방법 자체를 생각해내는 데에는 얼마걸리지 않았는데, 익숙하지않은 C++로 짜다보니,
삽질만 계속해서 하고있었음.
getLastArrSumResult function은 이중루프문이지만, 실제로 값이 주어졌을 때, 돌게되면 O(n) 이 나옴.
ex [1,2,3] -> [1],[1,2],[1,2,3], [2],[2,3], [3]
ex [1,2,3,4,5] -> [1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5] , [2],[2,3],[2,3,4],[2,3,4,5], [3],[3,4],[3,4,5], [4],[4,5], [5]
 3개의 숫자에 대해 루프를 돌 때, 6개임.
 5개의 숫자에 대해 루프를 돌 때, 15개임.

arr 값을 지정해줘도 크기가 8로 출력되는 문제가 있음. -> 해결법 찾는데로 수정해서 커밋 및 추가 테스트 필요.

x64 기준 디버그 결과 현재까지는 문제없음.

10, -1, 3 -> 12
1,2,3 -> 6

=======================================================================================================
* 본 문제의 출처는 매일프로그래밍입니다.
 https://mailprogramming.com/

 문제가 될 경우 해당 저장소는 삭제될 수 있습니다.
정수 배열(int array)가 주어지면 가장 큰 이어지는 원소들의 합을 구하시오. 단, 시간복잡도는 O(n).
Given an integer array, find the largest consecutive sum of elements.
예제}

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

// 이중루프문이지만, 실제로 값이 주어졌을 때, 돌게되면 O(n) 이 나옴.
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