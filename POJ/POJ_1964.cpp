/**
 * @file POJ_1964.cpp
 * @brief   变种的最大矩阵和问题，或许是吧，反正卡着时间过了。
 * 不要用cin，就算关闭了IO同步效率也不行，可能跟编译器设置有关，反正因为这个TLE了一发。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-01
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
#define MAX 1000
#define MIN -1000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int num[MAX+10][MAX+10], sum[MAX+10][MAX+10];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, M, N;
	char c[5];
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &M, &N);
		CLR( sum, 0 );
		for ( int i = 1; i <= M; ++i )
			for ( int j = 1; j <= N; ++j )
			{
				scanf("%s", c);
				if ( c[0] == 'R' )
					num[i][j] = MIN;
				else
					num[i][j] = 1;
				sum[i][j] = sum[i-1][j] + num[i][j];
			}
			int max_value = MIN, sum_value;
			for ( int i = 1; i <= M; ++i )
				for ( int j = i; j <= M; ++j )
				{
					sum_value = 0;
					for ( int k = 1; k <= N; ++k )
					{
						int value = sum[j][k] - sum[i - 1][k];
						sum_value = max( 0, sum_value + value );
						if ( sum_value > max_value )
							max_value = sum_value;
					}
				}
			printf ("%d\n", max_value * 3);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
