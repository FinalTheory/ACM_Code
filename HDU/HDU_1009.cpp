/*
	第一眼看上去还以为是背包。
	尼玛读完题，TMD最简单的贪心！
	一次AC的题，不废话了。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
struct TMD
{
	int F, J;
	double rate;
} rooms[1001];
bool fuck( TMD A, TMD B )
{
	return A.rate > B.rate;
}
int main()
{
	freopen("in.txt", "r", stdin);
	int m, n, i;
	double beans;
	while (1)
	{
		cin >> m >> n;
		beans = 0;
		if ( m == -1 && n == -1 )
			break;
		for ( i = 0; i < n; i++ )
		{
			cin >> rooms[i].J >> rooms[i].F;
			rooms[i].rate = (double)rooms[i].J / rooms[i].F;
		}
		sort(rooms, rooms + n, fuck);
		for ( i = 0; i < n && m; i++ )
			if ( m >= rooms[i].F )
			{
				m -= rooms[i].F;
				beans += rooms[i].J;
			}
			else
			{
				beans += (rooms[i].J * m) / (double)rooms[i].F;
				m = 0;
			}
		printf("%.3lf\n", beans);
	}
}