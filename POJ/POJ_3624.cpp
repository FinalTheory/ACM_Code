/*
	01背包例题，由于数据规模相当大，必须进行空间复杂度优化，否则MLE。优化版本被注释掉了。
	注意这两重循环，第一重是从第一个物品到最后一个物品，计算在考虑它的情况下的最大价值。
	第二重循环建议逆序来，但是如果不优化空间复杂度的话顺序也可以。但是这样需要手动把上面一行先复制到下面。
	它是从第i个物品的体积往上加，然后看在当前对应的体积下的最大价值。
	最后考虑完所有物品后，最后一项（对应体积最大）即为最大价值。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
using namespace std;
int DP[3500][13000];
//int DP[13000];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, W[3500], D[3500], i, v;
	while ( cin >> N >> M )
	{
		for ( i = 1; i <= N; i++ )
			cin >> W[i] >> D[i];
		for ( i = 1; i <= N; i++ )
		{
			for ( v = 0; v <= M; v++ )
				DP[i][v] = DP[i-1][v];
			for ( v = W[i] ; v <= M; v++ )
				//DP[v] = MAX( DP[v], DP[v-W[i]] + D[i] );
				DP[i][v] = MAX( DP[i-1][v], DP[i-1][v-W[i]] + D[i] );
		}
		cout << DP[N][M] << endl;
		//cout << DP[M] << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}