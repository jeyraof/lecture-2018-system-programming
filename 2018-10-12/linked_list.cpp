//**************************************************************
// 제목: 연결리스트 예제
// 기능: 연결 리스트 기본 연산함수 작성
// 파일이름: linked_list.cpp
// 수정날짜: 2018년10월05일
// 작성자: 이재영
//**************************************************************

#include <stdio.h> // printf 를 위해 필요
#include <stdlib.h> // malloc 을 위해 필요

typedef struct node {
	int data;
	struct node* pNext;
} Node;

// 함수 createNode
// 입력: 데이터
// 출력: Heap에서 생성한 노드
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
void printLL(Node* ptr) {
	while (ptr) {
		printf("data = %d\n", ptr->data);
		ptr = ptr->pNext;
	}
	printf("\n");
}

// 함수 insertHead
// 입력: linked list 의 헤드 포인터, 새 노드의 포인터
// 출력: 없음
// 부수효과: 연결리스트의 헤드가 새 노드로 변경됨
void insertHead(Node** ppHead, Node* pNewNode) {
	pNewNode->pNext = *ppHead;
	*ppHead = pNewNode;
}

// 함수 deleteHead
// 입력: linked list 의 헤드 포인터
// 출력: 없음
// 부수효과: 연결리스트의 헤드가 사라짐
void deleteHead(Node** ppHead) {
	*ppHead = (*ppHead)->pNext;
	// free 는 어떻게?
}

int main() {
	Node *ptr1, *ptr2, *pHead;
	// pHead == NULL: (약속) 연결리스트가 비어있다는 의미이다.
	// pNext == NULL: (약속) 이 노드가 연결리스트의 마지막 노드라는 의미이다.
	ptr1 = createNode(10);
	ptr2 = createNode(20);
	ptr1->pNext = ptr2;
	pHead = ptr1;
	printLL(pHead);

	// 연결리스트 헤드에 새로운 노드를 삽입
	insertHead(&pHead, createNode(50));
	printLL(pHead);

	// 연결리스트 헤드를 제거
	deleteHead(&pHead);
	printLL(pHead);

	return 0;
}