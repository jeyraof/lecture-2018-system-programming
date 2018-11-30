#include <stdio.h>
#define MAX 1000
#define chois

#ifdef chois
	int gVar = 0;
#endif

#ifndef chois
	int gVar = 10;
#endif

#define SUM(a,b) a+b  // 매크로함수 (macro)

int main() {
	int a, b = 10;
	const int c = 30;
	a = b;
	a = c;
	a = MAX;
	
	printf("a = %d, gVar = %d, SUM(b,c) = %d\n", a, gVar, SUM(b,c));

	return 0;
}