//**************************************************************
// 제목: Semaphore 예제 
// 기능: 
// 파일이름: semaphore.cpp
// 수정날짜: 2018년11월16일
// 작성자: 이재영
//**************************************************************

#define WIN32_LEAN_AND_MEAN
#include <stdio.h> // printf 를 위해 필요
#include <stdlib.h> // malloc 을 위해 필요
#include <windows.h>
#include <time.h>

int main() {
	HANDLE hMutex, hSemaphore;
	hMutex = CreateMutex(NULL, TRUE, NULL);
	// 뮤텍스는 동일 쓰레드 내에서의 접근을 허락한다.
	WaitForSingleObject(hMutex, INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	printf("end of mutex\n");

	hSemaphore = CreateSemaphore(NULL, 1, 2, NULL); // initial count = 1, max count = 2;
	WaitForSingleObject(hSemaphore, INFINITE);
	printf("end of semaphore1 \n");
	ReleaseSemaphore(hSemaphore, 1, NULL);
	WaitForSingleObject(hSemaphore, INFINITE);
	printf("end of semaphore2 \n");

	// 여기는 그냥 테스트 코드
	HANDLE hSem[3];
	HANDLE hSem1 = CreateSemaphore(NULL, 2, 3, NULL);
	hSem[0] = hSem[1] = hSem[2] = hSem1;
	
	DWORD result;
	result = WaitForMultipleObjects(3 , hSem, TRUE, INFINITE);
	if (result == WAIT_FAILED) printf("Error code = %d\n", GetLastError());
	printf("end of semaphore3 \n");

	return EXIT_SUCCESS;
}