#include <stdio.h>
#include <malloc.h>

typedef char element;

// Node = element와 link로 이루어짐
// element = 뭐 stack이 10개 쌓이면 위에서부터 나가잖아 그 한 개씩의 크기를 의미, 이게 int32면 스택 한덩어리가 32bit고 뭐 그런겨
// link = 어떤 Node가 Push나 Pop(스택에선 이렇게 부르고 Que는 또 다르게 부르더라) 되면 다음 순서가 뭔지 알기위해 쓰는거
typedef struct QNode { //  struct 이름(위에있는거)랑 별칭(아래있는거)랑 같아도 상관없음  
    element data;
    struct QNode *link; // QNode라는 구조체의 주소를 가리키는 포인터
} QNode;

typedef struct { // 연결 큐에서 사용하는 포인터 front와 rear를 구조체로 정의
                 // 익명 구조체 꼴 : 별칭(아래 있는거)만 사용
    struct QNode *front, *rear; // LQueueType은 QNode라는 구조체를 가리키는 포인터 두 개로 이루어진 구조체
} LQueueType;

// 공백 연결 큐 생성하기
LQueueType *createLinkedQueue() { // createLinkedQueue는 LQueueType 이라는 구조체의 주소를 가리키는 포인터를 반환 = LQ
    LQueueType *LQ;
    LQ = (LQueueType *)malloc(sizeof(LQueueType));
    // malloc 문법 설명 
    // X = (어떤 타입 A *)malloc(sizeof(어떤 타입 A));
    // X에 어떤 타입 A 의 크기만큼 메모리를 할당해라~
    LQ->front = NULL;
    LQ->rear = NULL;
    // LQ는 LQueueType이라는 구조체의 주소를 가리키는 포인터
    // LQ->front, LQ->rear는 python class를 어떤 값으로 선언해두고 class 안에 있는거 쓰는거처럼
    // LQ로 선언한 LQueueType 이라는 구조체 안의 QNode의 주소를 가리키는 포인터 front, rear에 NULL 할당
    // QNode : 큐 한덩어리(element + link)
    // 즉 수많은 QNode들 QNode1, QNode2, QNode3... 가 있고 얘내를 가리키는 애가 2개(front, rear)가 있음
    // 수 많은 애들중에 front가 첫 번째 rear가 마지막번쨰 QNode가 된다.
    // 예를들어 QNode3, QNode4, QNode5, QNode6 이 있으면 front는 QNode3을 가리키고 rear는 QNode6을 가리킨다.
    return LQ;
}

int isempty(LQueueType *LQ) {
    if (LQ->front == NULL) {
        printf("Linked Queue is empty!");
        return 1;
    }
    else return 0;
}

// 연결 큐의 rear에 원소를 삽입하는 연산
void enQueue (LQueueType *LQ, element item) {
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    newNode->data = item;
    newNode->link = NULL;

    if (LQ->front == NULL) { // front가 없을 때 (처음 삽임) = 현재 연결 큐가 공백 상태인 경우
        LQ->front = newNode;
        LQ->rear = newNode;
    }
    else {                   // front가 있을 때(일반적인 case) rear에만 넣어줌 = 현재 연결 큐가 공백 상태가 아닌 경우
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
}

// 연결 큐에서 원소를 삭제하고 반환하는 연산
element deQueue(LQueueType *LQ) { // LQ :  전체 Queue
	QNode *old = LQ->front;       // 전체 Queue LQ중 front에 있는 애를 old라고 부르자
	element item;
	if (isempty(LQ)) return 0;
	else {
		item = old->data;           // old에 있는 data를 item으로 저장
		LQ->front = LQ->front->link;// front에 있는 애의 주소를 가리키는 포인터를 front 다음에 연결되어있던 애의 주소를 가리키는 포인터로 바꿔
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}

// 연결 큐에서 front에 있는 원소를 검색하는 연산
element peek(LQueueType *LQ) {
	element item;
	if (isempty(LQ)) return 0;
	else {
		item = LQ->front->data; // front에 있는 data 줍줍
		return item; 
	}
}

// 연결 큐의 원소를 출력하는 연산
void printLQ(LQueueType *LQ) {
	QNode *temp = LQ->front;
	printf(" Linked Queue : [");
	while (temp) { // 유명한 문법이라는데 나만 몰랐네, 어떤 포인터 ptr을 if(ptr) or while(ptr) 이렇게 쓰면 if(ptr != NULL)과 동일한 표현이고 포인터가 NULL이 아니면 True
		printf("%3c", temp->data);
		temp = temp->link;
	}
	printf(" ] ");
}

void main(void) {
	LQueueType *LQ = createLinkedQueue();  // 연결 큐 생성
	element data;
	printf("\n ***** 연결 큐 연산 ***** \n");
	printf("\n 삽입 A>>");  enQueue(LQ, 'A'); printLQ(LQ);
	printf("\n 삽입 B>>");  enQueue(LQ, 'B'); printLQ(LQ);
	printf("\n 삽입 C>>");  enQueue(LQ, 'C'); printLQ(LQ);
	data = peek(LQ);    printf(" peek item : %c \n", data);
	printf("\n 삭제  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t삭제 데이터: %c", data);
	printf("\n 삭제  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t삭제 데이터: %c", data);
	printf("\n 삭제  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t\t삭제 데이터: %c", data);
	printf("\n 삽입 D>>");  enQueue(LQ, 'D'); printLQ(LQ);
	printf("\n 삽입 E>>");  enQueue(LQ, 'E'); printLQ(LQ);
	getchar();
}