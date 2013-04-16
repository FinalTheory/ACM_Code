/*
	变种的背包问题。设阶段为i，剩余体能为v，状态转移方程如下：
	f[i][v] = MIN( f[i-1][v] + T2, f[i-1][v+F1] + T1, f[i-1][v-F2] + T3 )
	也就是说对于每一个阶段，每一个体能状态，显然可以选三种模式。
	首先对于每一个阶段的体能状态，初始化为上一个阶段的再加上T2，
	也就是假设都是Normal，因为无论如何Normal肯定是合法的。
	然后逆序递推，进行状态转移（要检验其合法性，也就是看v的值是否合理，并进行处理）：
	当然，这样递推时每一阶段肯定存在同时符合这两个状态转移的体能状态。
	也就是说，对于每一个体能状态，我们比较了三个可以到它的模式，选择了值最小的。
	另外在初始化的时候，由于在第零阶段有m的能量，在拥有这个能量下的最短时间显然为0，所以dp[0][m]=0。
	但是在零阶段之前没有消耗体能的机会，所以其他体能状态没有合法值，因此初始化为INF。
*/
#include <iostream>
#include <cstdio>
#include <climits>
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
int dp[120][120];
int main()
{
	//freopen("in.txt", "r", stdin);
	int T, N, M, i, j, v, T1, T2, T3, F1, F2, mini;
	cin >> T;
	while ( T-- )
	{
		cin >> N >> M;
		for ( i = 0; i < M; i++ )
			dp[0][i] = INT_MAX - 1000;
		dp[0][M] = 0;
		for ( i = 1; i <= N; i++ )
		{
			cin >> T1 >> T2 >> T3 >> F1 >> F2;
			for ( v = M ; v >= 0; v-- )
				dp[i][v] = dp[i-1][v] + T2;
			for ( v = M + F2; v >= 0; v-- )
			{
				if ( v + F1 <= M )
					dp[i][v] = MIN(dp[i][v], dp[i-1][v+F1] + T1);
				if ( v >= F2 )
					( v < M ) ? dp[i][v] = MIN(dp[i][v], dp[i-1][v-F2] + T3) : dp[i][M] = MIN(dp[i][M], dp[i-1][v-F2] + T3);
			}
		}
		mini = INT_MAX - 1000;
		for( j = 0; j <= M; j++ )
			if( dp[N][j] < mini )
				mini = dp[N][j];
		cout << mini << endl;
	}
}