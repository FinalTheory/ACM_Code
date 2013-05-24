/**
 * @file HDU_1171.cpp
 * @brief   背包问题，尝试装一半即可。
 * 似乎没有被数据卡得TLE，但是对于那些0MS过的表示理解不能……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-21
 */
#include <algorithm>
#include <cstdio>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
int V[60], M[60];
int DP[250010];
int main()
{
	int N, sum, i, j, k, sum_all;
	while ( scanf("%d", &N) && N > 0 )
	{
		sum = 0;
		for ( i = 0; i < N; ++i )
		{
			scanf("%d %d", &V[i], &M[i]);
			sum += V[i] * M[i];
		}
		sum_all = sum;
		sum >>= 1;
		CLR(DP, 0);
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < M[i]; ++j )
				for ( k = sum; k >= V[i]; --k )
					DP[k] = max( DP[k], DP[k - V[i]] + V[i] );
		int a = max( DP[sum], sum_all - DP[sum] );
		printf("%d %d\n", a, sum_all - a);
	}
}
