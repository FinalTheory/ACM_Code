/*
	图论问题。套用Havel-Hakimi算法。
	判断是否可以构造出一个满足给定顶点序列的图。
	本质上也是一种贪心算法。
	内循环的时候没注意修改了循环终点，单步调了半天啊尼玛……
	不过最近难得能一次AC啊，哈哈~~
	有空这题试一下暴力搜索，感觉极限情况下数据规模也不是很大的样子。
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct Node
{
	int du, index;
} nodes[10];
bool cmp( Node A, Node B )
{
	return A.du > B.du;
}
char map[10][10];
void link( int i, int j )
{
	map[i][j] = 1;
	map[j][i] = 1;
}
int main()
{
	int T, N, i, j, k, fail, stop;
	//freopen("123.txt", "r", stdin);
	cin >> T;
	while ( T-- )
	{
		cin >> N;
		stop = fail = 0;
		memset(map, 0, sizeof(map));
		for ( i = 0; i < N; i++ )
		{
			cin >> nodes[i].du;
			nodes[i].index = i;
		}
		sort(nodes, nodes + N, cmp);
		while(!stop)
		{
			k = nodes[0].du;
			for ( i = 1; i <= k; i++ )
			{
				link( nodes[0].index, nodes[i].index );
				nodes[0].du--;
				nodes[i].du--;
				if ( nodes[i].du < 0 )
				{
					fail = 1;
					stop = 1;
					break;
				}
			}
			sort(nodes, nodes + N, cmp);
			if ( nodes[0].du == 0 )
				stop = 1;
		}
		if ( !fail )
		{
			printf("YES\n");
			for ( i = 0; i < N; i++ )
			{
				for ( j = 0; j < N; j++ )
					printf("%d ", map[i][j]);
				printf("\n");
			}
			printf("\n");
		}
		else
			printf("NO\n\n");
	}
}