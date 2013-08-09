/**
 * @file HDU_3905.cpp
 * @brief   动态规划问题，需要压缩状态.
 * DP[i][j]记录状态，表示在第i分钟休息了j分钟后获得的最大收益。
 * 转移方程显然为DP[i][j] = max{DP[i-1][j-1], max{dp[k][j] + sum[i] - sum[k]}}，其中k >= j && k <= i - L
 * 表示这一分钟选择休息时是从DP[i-1][j-1]转移而来，选择听课时是从max{dp[k][j] + sum[i] - sum[k]}转移来。
 * 其中k是枚举了开始听课的时间，已经很小心地进行了边界处理，但是这样的复杂度是O(n^3)。
 * 所以记录另外一个状态tmp[i][j]表示当前分钟在听课并且已经休息了j分钟时的最大收益。
 * 它会由两个状态转移而来：一直听课到前一分钟的最大收益tmp[i-1][j] + nums[i]，所以要满足i >= j + L；
 * 以及最近从i-L分钟开始听课的最大收益DP[i - L][j] + sum[i] - sum[i - L]。
 * 这样就完成了状态压缩，复杂度降至O(n^2)。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-08
 */
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <queue>
#include <iomanip>
#define MAX 1010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
const int INF = 0x3f3f3f3f;
int sum[MAX], nums[MAX], DP[MAX][MAX], tmp[MAX][MAX];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, L;
	while ( scanf("%d %d %d", &N, &M, &L) != EOF )
	{
		CLR( DP, 0 ); CLR( tmp, 0 ); CLR( sum, 0 );
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &nums[i]);
			sum[i] = sum[i - 1] + nums[i];
		}
		//注意这里的初始化，只有满足条件至少听课L分钟时才是合法初值。
		for ( int i = 1; i <= N; ++i ) if ( i >= L )
			DP[i][0] = sum[i];
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= M; ++j )
			{
// 				int max_tmp = -INF;
// 				for ( int k = j; k <= i - L; ++k )
// 					if ( max_tmp < DP[k][j] + sum[i] - sum[k] )
// 						max_tmp = DP[k][j] + sum[i] - sum[k];
				if ( i >= j + L )
					tmp[i][j] = max( tmp[i - 1][j] + nums[i], DP[i - L][j] + sum[i] - sum[i - L] );
				DP[i][j] = max(DP[i - 1][j - 1], tmp[i][j]);
			}
		printf("%d\n", DP[N][M]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
