/*
��������Ŀӵ�������Ȼ�Ƕ�����ԣ����õģ�
���α���������δ𰸴��������ҿ�������ȷ�ʰ�������
�ִ���freopen()�ύ�ˣ�SB��
*/
#include <stdio.h>
#include <stdlib.h>
int cmp ( const void *a , const void *b )
{
	return *(int *)a > *(int *)b ? 1 : -1;
}
void main()
{
	int n, i, data[10010];
	//freopen("123.txt","r",stdin);
	while(scanf("%d", &n)!=EOF)
	{
		for ( i = 0; i < n; i++ )
			scanf("%d", data + i);
		qsort( data, n, sizeof(int), cmp );
		printf("%d\n", data[n/2]);
	}
}