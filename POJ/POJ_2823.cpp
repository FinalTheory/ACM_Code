/*
	编译器要用g++ GNU的I/O不给力！
	单调队列时间也挺长，不知道那些500多MS的怎么过的，时间应该全卡在IO上了啊！
*/
#include <stdio.h>
#define MAX 1000001
struct node
{
	int value;
	int index;
} max_queue[MAX], min_queue[MAX];
int max[MAX];
int main()
{
	int queue_max_head, queue_min_head, queue_max_tail, queue_min_tail;
	int n, k, i, j, value;
	//freopen("123.txt", "r", stdin);
	queue_max_head = queue_min_head = 0;
	queue_max_tail = queue_min_tail = 0;
	scanf("%d %d", &n, &k);
	for ( i = 0, j = 0; i < n; i++ )
	{
		scanf("%d", &value);
		while ( queue_max_tail > queue_max_head && max_queue[queue_max_tail-1].value <= value && queue_max_tail ) queue_max_tail--;
		max_queue[queue_max_tail].value = value;
		max_queue[queue_max_tail++].index = i;
		while ( max_queue[queue_max_head].index < i - k + 1 ) queue_max_head++;
		if ( i >= k - 1 )
			max[j++] = max_queue[queue_max_head].value;

		while ( queue_min_tail > queue_min_head && min_queue[queue_min_tail-1].value >= value ) queue_min_tail--;
		min_queue[queue_min_tail].value = value;
		min_queue[queue_min_tail++].index = i;
		while ( min_queue[queue_min_head].index < i - k + 1 ) queue_min_head++;
		if ( i >= k - 1 )
			printf("%d ", min_queue[queue_min_head].value);
	}
	printf("\n");
	for ( i = 0; i <= n - k; i++ )
		printf("%d ", max[i]);
	printf("\n");

	return 0;
}