#include <stdio.h>

int sum(int, int);
int (*fff)(int, int); /// fff 는 함수 포인터이다.

int main() {
	// 1. 함수의 이름(sum) 은 그 함수의 시작 주소이다.
	// 2. 함수 포인터를 지정하려면 두 함수의 타입(반환형, 매개변수의 개수 및 자료형)이 동일해야한다.
	fff = sum;

	printf("value = %d\n", sum(10, 20) );
	printf("value = %d\n", fff(100, 200) );
	
	return 0;
}

int sum(int a, int b) {
	return a+b;
}