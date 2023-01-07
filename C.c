#include"Quene.h";


void test1()
{
	Quene q;
	QueneInit(&q);
	QuenePush(&q, 1);
	QuenePush(&q, 2);

	//QDataType number = QueneFront(&q);
	//printf("%d ", number);
	//QuenePop(&q);


	QuenePush(&q, 3);	

	//QuenePop(&q);
	//Quenepop(&q);
	//Quenepop(&q);

	//QuenePush(&q, 1);
	//QuenePush(&q, 2);

	/*printf("%d ", QueneFront(&q));
	printf("%d ", QueneBack(&q));*/
	
	//printf("%d", QueneSize(&q));

	/*while (!QueneEmpty(&q))
	{
		QDataType number = QueneFront(&q);
		printf("%d ", number);
		QuenePop(&q);
	}*/
	QueneDestroy(&q);
}
int main()
{
	test1();
	return 0;
}