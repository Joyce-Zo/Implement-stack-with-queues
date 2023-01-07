#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
typedef int QDataType;
typedef struct QueneNode
{
	struct QueneNode* next;
	QDataType data;
}QueneNode;

typedef struct Quene
{
	QueneNode* head;
	QueneNode* tail;
}Quene;

void QueneInit(Quene* pq);
void QueneDestroy(Quene* pq);
void QuenePush(Quene* pq, QDataType x);
void QuenePop(Quene* pq);
void QuenePrint(Quene pq);

QDataType QueneFront(Quene* pq); // ȡ��ͷ������
QDataType QueneBack(Quene* pq);  // ȡ��β������

int QueneSize(Quene* pq); // �������ݵĸ���
bool QueneEmpty(Quene* pq);

void QueneInit(Quene* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
}

void QueneDestroy(Quene* pq)
{
	assert(pq);
	QueneNode* cur = pq->head;

	while (cur)
	{
		QueneNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
}

void QuenePop(Quene* pq)
{
	assert(pq);
	assert(!QueneEmpty(pq)); // �ж�pq�Ƿ�Ϊ�գ����Ϊ�ղ��жϣ����������ֱ�ӱ�

	QueneNode* next = pq->head->next;
	free(pq->head);
	pq->head = next;
	if (pq->head == NULL)
	{
		pq->tail = NULL;
	}
}

void QuenePush(Quene* pq, QDataType x)
{
	assert(pq);

	QueneNode* newnode = (QueneNode*)malloc(sizeof(QueneNode));
	newnode->data = x;
	newnode->next = NULL;

	if (pq->head == NULL)
	{
		//pq->tail->next = new;
		pq->head = pq->tail = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}

QDataType QueneFront(Quene* pq)
{
	assert(pq);
	assert(!QueneEmpty(pq));

	return pq->head->data;
}

QDataType QueneBack(Quene* pq)
{
	assert(pq);
	assert(!QueneEmpty(pq));

	return pq->tail->data;
}

int QueneSize(Quene* pq)
{
	int num = 0;	// �ṹ��������size�������ֱ�ӷ���
	QueneNode* cur = pq->head;
	while (cur)
	{
		num++;
		cur = cur->next;
	}
	return num;
}
bool QueneEmpty(Quene* pq)
{
	assert(pq);
	return pq->head == NULL; // Ϊ�շ���True��
}

// �ö���ʵ��ջ
typedef struct
{
	Quene q1;
	Quene q2;
} MyStack;


MyStack* myStackCreate()
{
	MyStack* st = (MyStack*)malloc(sizeof(MyStack));
	QueneInit(&st->q1);
	QueneInit(&st->q2);
	return st; // malloc���ģ����Գ��˽ӿڻ��ڣ���һ��ľֲ�����������
}

void myStackPush(MyStack* st, int x) {
	if (!QueneEmpty(&st->q1))// q1��Ϊ�գ�˵�������ݣ���������ݵ������
	{
		QuenePush(&st->q1, x);
	}
	else
	{
		QuenePush(&st->q2, x);// ������뵽q2��ͬʱ����q1��q2ͬʱΪ�յ������������ĸ����С�
	}
}

int myStackPop(MyStack* st) {
	Quene* EmptyQ = &st->q1; // Ĭ��ʹq1Ϊ�գ�q2��Ϊ�գ������������
	Quene* NoneEmptyQ = &st->q2;
	if (!QueneEmpty(&st->q1)) // q1��Ϊ�շ��ؼ٣����󷵻���
	{   // ��q1��Ϊ�գ�q2Ϊ�գ����߽�������
		EmptyQ = &st->q2;
		NoneEmptyQ = &st->q1;
	}
	while (QueneSize(NoneEmptyQ) > 1) // ɾ����βǰ���������ݣ�ֱ������β
	{
		QuenePush(EmptyQ, QueneFront(NoneEmptyQ));
		// �ֱ��ö��е������ӿں�������ȡ���ǿն����е�Ԫ�أ��ٽ�����뵽�ն�����
		QuenePop(NoneEmptyQ);
	}
	// �Ѿ�����β����Pop����������
	int number = QueneFront(NoneEmptyQ);// ��ǰ�������һ������Ϊ��Ŀ��Ҫ���ظ�Ԫ��
	QuenePop(NoneEmptyQ);
	return number;
}

int myStackTop(MyStack* st) {
	if (!QueneEmpty(&st->q1))
	{   // ˭��Ϊ�գ�����˭�Ķ�β
		return QueneBack(&st->q1);
	}
	else
	{
		return QueneBack(&st->q2);
	}
}

bool myStackEmpty(MyStack* st) {
	// �ж�ջ�Ƿ�Ϊ�գ����ж�2�������Ƿ�Ϊ��
	return QueneEmpty(&st->q1) && QueneEmpty(&st->q2);
}

void myStackFree(MyStack* st) {
	QueneDestroy(&st->q1);
	QueneDestroy(&st->q2);
	free(st);
}

