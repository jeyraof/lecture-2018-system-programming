// 고쳐야됨

//**************************************************************
// 제목: 데드락 예제
// 기능: Mutex 로 데드락을 해결해본다.
// 파일이름: deadlock_mutex.cpp
// 수정날짜: 2018년11월16일
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
	HANDLE hMutex;
} LList;

// 함수 insertHead
// 입력: linked list 의 헤드 포인터, 새 노드의 포인터
// 출력: 없음
// 부수효과: 연결리스트의 헤드가 새 노드로 변경됨
void insertHead(LList* pLList, Node* pNewNode) {
    WaitForSingleObject(pLList->hMutex, INFINITE);
	pNewNode->pNext = pLList->pHead;
	pLList->pHead = pNewNode;
    ReleaseMutex(pLList->hMutex);
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

// 함수 swapLists
// 입력: 두 연결리스트 포인터
// 출력: 없음
// 부수효과: 두 연결리스트의 헤드가 바뀜
void swapLists(LList* llist1, LList* llist2, int threadNum) {
	Node *tmp_list;
	tmp_list = llist1->pHead;
	llist1->pHead = llist2->pHead;
	llist2->pHead = tmp_list;
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
	LList* pLList1;
	LList* pLList2;
	int thrdNumber;
} Input;

int main() {
	HANDLE hThrd[2];
	DWORD threadId;
	LList myLList, yourLList;
	LList* pLList1 = &myLList, *pLList2 = &yourLList;
    pLList1->hMutex = CreateMutex(NULL, FALSE, NULL);
    pLList2->hMutex = CreateMutex(NULL, FALSE, NULL);
	pLList1->pHead = NULL;
	pLList2->pHead = NULL;
	insertHead(pLList1, createNode(10));
	insertHead(pLList2, createNode(20));

	Input myInput1;
	myInput1.pLList1 = pLList1;
	myInput1.pLList2 = pLList2;
	myInput1.thrdNumber = 0;
	hThrd[0] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&myInput1, 0, &threadId);

	Input myInput2;
	myInput2.pLList1 = pLList2;
	myInput2.pLList2 = pLList1;
	myInput2.thrdNumber = 1;
	hThrd[1] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&myInput2, 0, &threadId);

	DWORD result;
	result = WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);
	if (result == WAIT_FAILED) printf("Error code = %d\n", GetLastError());
	for (int i=0; i<2; i++) CloseHandle(hThrd[i]);

	printf("Program Ends!!!\n");
    
	return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID ptr) {
	Input* pInput = (Input*)ptr;
	for (int i=0; i<1000000; i++) {
		swapLists(pInput->pLList1, pInput->pLList2, pInput->thrdNumber);
	}
    return 0;
}