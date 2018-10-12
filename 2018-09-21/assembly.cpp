//**************************************************************
// 제목: 어셈블리어 분석
// 기능: 어셈블리어 분석을 위한 기본 사항
// 파일이름: assembly.cpp
// 수정날짜: 2018년09월21일
// 작성자: 이재영
//**************************************************************

#include <windows.h>

void WINAPI wptrsum(int* p1, int* p2, int*p3);

void main() {
    int a, b, c;
    a = 10;
    b = 20;
    wptrsum(&a, &b, &c);
}

void WINAPI wptrsum(int* p1, int* p2, int* p3) {
    *p3 = *p1 + *p2;
}