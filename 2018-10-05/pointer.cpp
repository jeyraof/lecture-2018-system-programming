//**************************************************************
// 제목: 포인터, 구조체, 동적할당 예제
// 기능: 연결 리스트 사용을 위한 기본 사항
// 파일이름: pointer.cpp
// 수정날짜: 2018년10월05일
// 작성자: 이재영
//**************************************************************

#include <stdio.h> // printf 를 위해 필요
#include <stdlib.h> // malloc 을 위해 필요

typedef struct complex {
	double real; // member variable (멤버변수)
	double imag;
} Complex; // 구조체 선언은 ;으로 끝내야 한다.

// 자료형: 변수가 값을 가질 수 있는 범위

// 함수 printComplexVar
// 입력: 복소수
// 출력: 없음
// 부수효과: 화면에 복소수를 출력
void printComplexVar(Complex a) {
	printf("%f + j%f\n", a.real, a.imag);
}

// 함수 printComplex
// 입력: 복소수의 포인터
// 출력: 없음
// 부수효과: 화면에 복소수를 출력
void printComplex(Complex* a) {
	printf("%f + j%f\n", a->real, a->imag);
}

// 함수 addComplexReturnVar
// 입력: 두개의 복소수의 포인터
// 출력: 두 복소수의 합
// 부수효과: 없음
Complex addComplexReturnVar(Complex* ptr1, Complex* ptr2) {
	Complex c;
	c.real = ptr1->real + ptr2->real;
	c.imag = ptr1->imag + ptr2->imag;
	return c;
}

// 함수 addComplex
// 입력: 두개의 복소수의 포인터
// 출력: 두 복소수의 합의 포인터
// 부수효과: 없음
Complex* addComplex(Complex* ptr1, Complex* ptr2) {
	// Wrong: Complex c; 함수 종료 후 이 지역변수 공간은 소멸된다.
	Complex* ptr;
	ptr = (Complex*) malloc(sizeof(Complex));
	ptr->real = ptr1->real + ptr2->real;
	ptr->imag = ptr1->imag + ptr2->imag;
	return ptr;
}

int main() {
	// 포인터
	int a=10, b=20, c=30;

	int* ptr; // 포인터 변수 선언
	ptr = &a;
	*ptr = b;
	printf("a = %d\n", a);

	// 구조체
	// struct complex c1={1.0, 1.0}, c2={2.0, 3.0}, c3; // 구조체 변수 선언
	Complex c1={1.0, 1.0}, c2={2.0, 3.0}, c3; // 구조체 변수 선언
	// 불가능: c3 = c1 + c2;
	c3.real = c1.real + c2.real; // 멤버 변수 접근 -> 구조체변수이름.멤버변수이름
	c3.imag = c1.imag + c2.imag;
	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	// 구조체 포인터
	Complex* ptr1;
	ptr1 = &c3;
	ptr1->real = 10.0; // 멤버변수 접근: 구조체포인터변수이름->멤버변수이름
	ptr1->imag = 20.0;
	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	// 구조체가 매개변수인 함수
	c3 = c1;
	printComplexVar(c3); // 비효율적: 매개변수를 함수 내에서 지역변수로 메모리에 할당함.
	printComplex(&c3);

	// 동적 할당
	c3 = addComplexReturnVar(&c1, &c2);
	printComplex(&c3);

	ptr1 = addComplex(&c1, &c2);
	printComplex(ptr1);
	free(ptr1); // heap 공간 소멸

	return 0;
}