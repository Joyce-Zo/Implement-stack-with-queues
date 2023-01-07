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

QDataType QueneFront(Quene* pq); // 取队头的数据
QDataType QueneBack(Quene* pq);  // 取队尾的数据

int QueneSize(Quene* pq); // 返回数据的个数
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
	assert(!QueneEmpty(pq)); // 判断pq是否为空，如果为空不判断，走下面代码直接崩

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
	int num = 0;	// 结构体中若有size，则可以直接返回
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
	return pq->head == NULL; // 为空返回True，
}

// 用队列实现栈
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
	return st; // malloc出的，所以出了接口还在，而一般的局部变量会销毁
}

void myStackPush(MyStack* st, int x) {
	if (!QueneEmpty(&st->q1))// q1不为空，说明有数据，则插入数据到其后面
	{
		QuenePush(&st->q1, x);
	}
	else
	{
		QuenePush(&st->q2, x);// 否则插入到q2。同时包含q1和q2同时为空的情况，则插入哪个都行。
	}
}

int myStackPop(MyStack* st) {
	Quene* EmptyQ = &st->q1; // 默认使q1为空，q2不为空，进行下面代码
	Quene* NoneEmptyQ = &st->q2;
	if (!QueneEmpty(&st->q1)) // q1不为空返回假，！后返回真
	{   // 若q1不为空，q2为空，二者交换即可
		EmptyQ = &st->q2;
		NoneEmptyQ = &st->q1;
	}
	while (QueneSize(NoneEmptyQ) > 1) // 删除队尾前的所有数据，直至到队尾
	{
		QuenePush(EmptyQ, QueneFront(NoneEmptyQ));
		// 分别用队列的两个接口函数，先取出非空队列中的元素，再将其插入到空队列中
		QuenePop(NoneEmptyQ);
	}
	// 已经到队尾，则Pop掉最后的数据
	int number = QueneFront(NoneEmptyQ);// 提前保存最后一个，因为题目中要返回该元素
	QuenePop(NoneEmptyQ);
	return number;
}

int myStackTop(MyStack* st) {
	if (!QueneEmpty(&st->q1))
	{   // 谁不为空，返回谁的队尾
		return QueneBack(&st->q1);
	}
	else
	{
		return QueneBack(&st->q2);
	}
}

bool myStackEmpty(MyStack* st) {
	// 判断栈是否为空，即判断2个队列是否都为空
	return QueneEmpty(&st->q1) && QueneEmpty(&st->q2);
}

void myStackFree(MyStack* st) {
	QueneDestroy(&st->q1);
	QueneDestroy(&st->q2);
	free(st);
}

