#include <stdio.h>
#include <malloc.h>

typedef char element;

// Node = element�� link�� �̷����
// element = �� stack�� 10�� ���̸� ���������� �����ݾ� �� �� ������ ũ�⸦ �ǹ�, �̰� int32�� ���� �ѵ���� 32bit�� �� �׷���
// link = � Node�� Push�� Pop(���ÿ��� �̷��� �θ��� Que�� �� �ٸ��� �θ�����) �Ǹ� ���� ������ ���� �˱����� ���°�
typedef struct QNode { //  struct �̸�(�����ִ°�)�� ��Ī(�Ʒ��ִ°�)�� ���Ƶ� �������  
    element data;
    struct QNode *link; // QNode��� ����ü�� �ּҸ� ����Ű�� ������
} QNode;

typedef struct { // ���� ť���� ����ϴ� ������ front�� rear�� ����ü�� ����
                 // �͸� ����ü �� : ��Ī(�Ʒ� �ִ°�)�� ���
    struct QNode *front, *rear; // LQueueType�� QNode��� ����ü�� ����Ű�� ������ �� ���� �̷���� ����ü
} LQueueType;

// ���� ���� ť �����ϱ�
LQueueType *createLinkedQueue() { // createLinkedQueue�� LQueueType �̶�� ����ü�� �ּҸ� ����Ű�� �����͸� ��ȯ = LQ
    LQueueType *LQ;
    LQ = (LQueueType *)malloc(sizeof(LQueueType));
    // malloc ���� ���� 
    // X = (� Ÿ�� A *)malloc(sizeof(� Ÿ�� A));
    // X�� � Ÿ�� A �� ũ�⸸ŭ �޸𸮸� �Ҵ��ض�~
    LQ->front = NULL;
    LQ->rear = NULL;
    // LQ�� LQueueType�̶�� ����ü�� �ּҸ� ����Ű�� ������
    // LQ->front, LQ->rear�� python class�� � ������ �����صΰ� class �ȿ� �ִ°� ���°�ó��
    // LQ�� ������ LQueueType �̶�� ����ü ���� QNode�� �ּҸ� ����Ű�� ������ front, rear�� NULL �Ҵ�
    // QNode : ť �ѵ��(element + link)
    // �� ������ QNode�� QNode1, QNode2, QNode3... �� �ְ� �곻�� ����Ű�� �ְ� 2��(front, rear)�� ����
    // �� ���� �ֵ��߿� front�� ù ��° rear�� ���������� QNode�� �ȴ�.
    // ������� QNode3, QNode4, QNode5, QNode6 �� ������ front�� QNode3�� ����Ű�� rear�� QNode6�� ����Ų��.
    return LQ;
}

int isempty(LQueueType *LQ) {
    if (LQ->front == NULL) {
        printf("Linked Queue is empty!");
        return 1;
    }
    else return 0;
}

// ���� ť�� rear�� ���Ҹ� �����ϴ� ����
void enQueue (LQueueType *LQ, element item) {
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    newNode->data = item;
    newNode->link = NULL;

    if (LQ->front == NULL) { // front�� ���� �� (ó�� ����) = ���� ���� ť�� ���� ������ ���
        LQ->front = newNode;
        LQ->rear = newNode;
    }
    else {                   // front�� ���� ��(�Ϲ����� case) rear���� �־��� = ���� ���� ť�� ���� ���°� �ƴ� ���
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
}

// ���� ť���� ���Ҹ� �����ϰ� ��ȯ�ϴ� ����
element deQueue(LQueueType *LQ) { // LQ :  ��ü Queue
	QNode *old = LQ->front;       // ��ü Queue LQ�� front�� �ִ� �ָ� old��� �θ���
	element item;
	if (isempty(LQ)) return 0;
	else {
		item = old->data;           // old�� �ִ� data�� item���� ����
		LQ->front = LQ->front->link;// front�� �ִ� ���� �ּҸ� ����Ű�� �����͸� front ������ ����Ǿ��ִ� ���� �ּҸ� ����Ű�� �����ͷ� �ٲ�
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}

// ���� ť���� front�� �ִ� ���Ҹ� �˻��ϴ� ����
element peek(LQueueType *LQ) {
	element item;
	if (isempty(LQ)) return 0;
	else {
		item = LQ->front->data; // front�� �ִ� data ����
		return item; 
	}
}

// ���� ť�� ���Ҹ� ����ϴ� ����
void printLQ(LQueueType *LQ) {
	QNode *temp = LQ->front;
	printf(" Linked Queue : [");
	while (temp) { // ������ �����̶�µ� ���� ������, � ������ ptr�� if(ptr) or while(ptr) �̷��� ���� if(ptr != NULL)�� ������ ǥ���̰� �����Ͱ� NULL�� �ƴϸ� True
		printf("%3c", temp->data);
		temp = temp->link;
	}
	printf(" ] ");
}

void main(void) {
	LQueueType *LQ = createLinkedQueue();  // ���� ť ����
	element data;
	printf("\n ***** ���� ť ���� ***** \n");
	printf("\n ���� A>>");  enQueue(LQ, 'A'); printLQ(LQ);
	printf("\n ���� B>>");  enQueue(LQ, 'B'); printLQ(LQ);
	printf("\n ���� C>>");  enQueue(LQ, 'C'); printLQ(LQ);
	data = peek(LQ);    printf(" peek item : %c \n", data);
	printf("\n ����  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t���� ������: %c", data);
	printf("\n ����  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t���� ������: %c", data);
	printf("\n ����  >>");  data = deQueue(LQ); printLQ(LQ);
	printf("\t\t���� ������: %c", data);
	printf("\n ���� D>>");  enQueue(LQ, 'D'); printLQ(LQ);
	printf("\n ���� E>>");  enQueue(LQ, 'E'); printLQ(LQ);
	getchar();
}