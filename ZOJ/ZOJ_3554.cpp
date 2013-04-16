/**
 * @file ZOJ_3554.cpp
 * @brief   ZOJ 3554
 * 动态规划问题，由于状态空间有限，可以考虑直接保存状态枚举即可。
 * 状态定义：dp[i][j][k]表示三台机器是否分别能工作到i,j,k秒。
 * 为了解决物品选取冲突的问题，使用dp_prev记录上一个物品对状态的影响。
 * 遍历一遍所有物品，每次枚举所有状态，如果上一个物品使该状态可以达到，则记录到dp中。
 * 最后遍历所有物品后，如果有哪个时间满足dp[t][t][t]=1，则说明存在相应的解。
 * 由于条件的约束，可以看出每个物品一定会对状态产生影响，所以不会存在物品没用完的问题。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-03
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define MAX 120
using namespace std;

int a[MAX+10], b[MAX+10], c[MAX+10];
char dp[MAX+10][MAX+10][MAX+10], dp_prev[MAX+10][MAX+10][MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, i, j, k, l;
	while ( cin >> N )
	{
		memset( dp, 0, sizeof(dp) );
		memset( dp_prev, 0, sizeof(dp) );
		dp_prev[0][0][0] = 1;
		for ( i = 0; i < N; ++i )
			cin >> a[i] >> b[i] >> c[i];
		for ( l = 0; l < N; ++l )
		{
			for ( i = 0; i <= MAX; ++i )
				for ( j = 0; j <= MAX; ++j )
					for ( k = 0 ; k <= MAX; ++k )
						if ( dp_prev[i][j][k] )
						{
							if ( i + a[l] <= MAX )
								dp[i+a[l]][j][k] = 1;
							if ( j + b[l] <= MAX )
								dp[i][j+b[l]][k] = 1;
							if ( k + c[l] <= MAX )
								dp[i][j][k+c[l]] = 1;
						}
			memcpy( dp_prev, dp, sizeof(dp) );
			memset( dp, 0, sizeof(dp) );
		}
		char found = 0;
		for ( i = 1; i <= MAX; ++i )
		{
			if ( dp_prev[i][i][i] == 1 )
			{
				found = 1;
				break;
			}
		}
		if ( found )
			cout << i << endl;
		else
			cout << "NO" << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
