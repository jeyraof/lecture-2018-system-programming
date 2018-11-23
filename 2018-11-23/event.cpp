//**************************************************************
// 제목: Event 예제 
// 기능: 
// 파일이름: event.cpp
// 수정날짜: 2018년11월23일
// 작성자: 이재영
//**************************************************************

#define WIN32_LEAN_AND_MEAN
#include <stdio.h> // printf 를 위해 필요
#include <stdlib.h> // malloc 을 위해 필요
#include <windows.h>
#include <time.h>

typedef struct input {
	HANDLE hEvent;
	int threadNum;
	long* pCount;
} Input;


DWORD WINAPI ThreadFunc(LPVOID ptr) {
	Input* pInput = (Input*) ptr;
	printf("Waiting for event to be signaled in Thread %d\n", pInput->threadNum);
	WaitForSingleObject(pInput->hEvent, INFINITE);
	printf("Event was just signaled in Thread %d\n", pInput->threadNum);
	InterlockedIncrement(pInput->pCount); // 함수 하나로 동기화 해결
	return 0;
}

int main() {
	int dummy;
	long count=0;
	HANDLE hEvent, hThrd[2];
	hEvent = CreateEvent(
		NULL,
		FALSE,  // true: manual reset, false: auto reset
		TRUE, // initial state false: non-signaled, true: signaled
		NULL
	);

	Input input1={hEvent, 1, &count}, input2={hEvent, 2, &count};
	hThrd[0] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&input1, 0, NULL);
	hThrd[1] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&input2, 0, NULL);

	printf("Press any key to continue\n");scanf_s("%d", &dummy);
	SetEvent(hEvent);

	printf("Press any key to continue\n");scanf_s("%d", &dummy);
	SetEvent(hEvent);
	
	DWORD result = WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);
	if (result == WAIT_FAILED) printf("Error code = %d\n", GetLastError());
	for (int i=0; i<2; i++) CloseHandle(hThrd[i]);

	printf("value of count = %d\n", count);

	printf("End of program \n");

	return EXIT_SUCCESS;
}
