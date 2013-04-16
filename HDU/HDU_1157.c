/*
这道题真心坑爹啊，居然是多组测试，你妹的！
三次编译错误，三次答案错误，尼玛我可怜的正确率啊！！！
又带着freopen()提交了，SB！
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