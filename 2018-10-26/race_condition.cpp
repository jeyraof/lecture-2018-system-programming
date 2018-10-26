//**************************************************************
// 제목: 레이스 컨디션 예제
// 기능: 연결리스트와 쓰레드를 이용한 레이스 컨디션 확인
// 파일이름: race_condition.cpp
// 수정날짜: 2018년10월26일
// 작성자: 이재영
//**************************************************************

#define WIN32_LEAN_AND_MEAN
#include <stdio.h> // printf 를 위해 필요
#include <stdlib.h> // malloc 을 위해 필요
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);

typedef struct node {
	int data;
	struct node* pNext;
} Node;

typedef struct llist {
	Node* pHead;
	CRITICAL_SECTION criticalSection;
} LList;

// 함수 insertHead
// 입력: linked list 의 헤드 포인터, 새 노드의 포인터
// 출력: 없음
// 부수효과: 연결리스트의 헤드가 새 노드로 변경됨
void insertHead(LList* pLList, Node* pNewNode) {
	EnterCriticalSection(&(pLList->criticalSection));
	pNewNode->pNext = pLList->pHead;
	pLList->pHead = pNewNode;
	LeaveCriticalSection(&(pLList->criticalSection));
}

// 함수 deleteHead
// 입력: linked list 의 헤드 포인터
// 출력: 없음
// 부수효과: 연결리스트의 헤드가 사라짐
void deleteHead(LList* pLList) {
	Node* prevHead = pLList->pHead;
	pLList->pHead = prevHead->pNext;
	free(prevHead);
}

// 함수 createNode
// 입력: 데이터
// 출력: Heap에서 생성한 노드의 포인터, 노드의 data는 입력값으로, pNext는 NULL로 설정
// 부수효과: 없음
Node* createNode(int val) {
	Node *ptr;
	ptr = (Node*) malloc(sizeof(Node));
	ptr->data = val;
	ptr->pNext = NULL;
	return ptr;
}

// 함수 printLL
// 입력: linked list 의 헤드 포인터
// 출력: 없음
// 부수효과: 화면에 각 노드 데이터를 출력
void printLL(LList* pLList) {
	Node* ptr = pLList->pHead;
	while (ptr) {
		printf("data = %d\n", ptr->data);
		ptr = ptr->pNext;
	}
}

// 함수 numNode
// 입력: Linked List 구조체 포인터
// 출력: Linked List 노드 갯수
// 부수효과 없음
int numNode(LList* pLList) {
	Node* ptr = pLList->pHead;
	int num = 0;
	while (ptr) {
		num++;
		ptr = ptr->pNext;
	}
	return num;
}

typedef struct input {
	LList* pLList;
	int threadNum;
} input;

int main() {
	LList myLList;
	LList* pLList = &myLList;
	InitializeCriticalSection(&(pLList->criticalSection));
	pLList->pHead = NULL;

	input Input;
	input* pInput = &Input;
	pInput->pLList = pLList;

	HANDLE hThrd[5];
    DWORD threadId;

    for (int i=0; i<5; i++)
    {
		pInput->threadNum = i;
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)pInput, 0, &threadId);
    }

	DWORD result;
	result = WaitForMultipleObjects(5, hThrd, true, INFINITE);
	if (result == WAIT_FAILED) {
		printf("Error code = %d\n", GetLastError());
	}
	for (int i=0; i<5; i++) {
		CloseHandle(hThrd[i]);
	}

	printf("number of nodes = %d\n", numNode(pLList));

	return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID ptr) {
	input* pInput = (input*)ptr;
	for (int i=0; i<10000; i++) {
		insertHead(pInput->pLList, createNode((int)pInput->threadNum));
	}
    return 0;
}