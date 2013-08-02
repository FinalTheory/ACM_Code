/**
 * @file POJ_1050.cpp
 * @brief   最大子矩阵和，模版题。跟最长子列和差不多的意思。
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
#define MAX 100
#define MIN -100000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int num[MAX+10][MAX+10], sum[MAX+10][MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N;
	while ( cin >> N )
	{
		CLR( sum, 0 );
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= N; ++j )
			{
				cin >> num[i][j];
				sum[i][j] = sum[i-1][j] + num[i][j];
			}
		int max_value = MIN, sum_value;
		for ( int i = 1; i <= N; ++i )
			for ( int j = i; j <= N; ++j )
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
		cout << max_value << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
