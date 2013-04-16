/*
	网上方法挺多，最小生成树、并查集神马的。自己的方案TLE了，可能递归终点设置的有问题。
	copy了别人的一个贪心的思路。首先在输入路径的时候把所有路径的花销以及两端点直接保存在map里（为了节省代码量就不压缩了）。
	如果两点间没有通路就是先前初始化的INF。然后从编号为0的点开始，将从0点到所有点的花销保存在cost里面，0点标为checked。
	然后从零点走到花销最短的一个点（也就是把这个花销加进sum里，前提是这个点没有被走过），并将检查过的点也就是当前点也标为checked。
	接着更新花销，枚举一遍所有点，如果当前点到它的花销比之前那个点少，那么就用这个小的花销覆盖原本的花销。
	再次走到花销最小的点。重复以上过程N-1次，最终所有点被标记为checked，此时由于每次选取的都是花销最小的点，并且路线不重复，因此总花销也是最小的。
	总体思路就是，保证每次花销都最小的情况下遍历一遍所有点，典型的贪心。
	另外原作者把循环次数弄错了，导致必须增加一个判断才能AC，因为循环N-1次后所有点全部被checked，此时min没发生改变还是INF，自然不能被加进去。
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 100000000
#define DI 510
using namespace std;
int map[DI][DI], cost[DI];
char checked[DI];
int main()
{
	//freopen("in.txt", "r", stdin);
	int i, j, sum, K, min, bak, A, B, T, N, E;
	cin >> T;
	while( T-- )
	{
		cin >> N >> E;
		memset(checked, 0, sizeof(checked));
		sum = 0;
		for ( i = 0; i < N; i++ )
			for ( j = 0; j < N; j++ )
				map[i][j] = INF;
		for ( i = 0; i < E; i++ )
		{
			cin >> A >> B >> K;
			map[A][B] = map[B][A] = K;
		}
		bak = 0;
		for ( j = 0; j < N; j++ )
			cost[j] = map[0][j];
		checked[bak] = 1;
		for ( i = 0; i < N - 1; i++ )
		{
			min = INF;
			for ( j = 0; j < N; j++ )
				if ( !checked[j] && cost[j] < min )
				{
					bak = j;
					min = cost[j];
				}
			sum += min;
			checked[bak] = 1;
			for ( j = 0; j < N; j++ )
			{
				if ( !checked[j] && cost[j] > map[bak][j] )
					cost[j] = map[bak][j];
			}
		}
		cout << sum << endl;
	}
}