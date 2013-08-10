/**
 * @file POJ_2181.cpp
 * @brief   DP问题，求一个奇增偶减的最大和子序列
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

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
#define MAX 150010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
int P[MAX];
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
	while ( scanf("%d", &N) != EOF )
	{
		long long res = 0;
		P[0] = P[N + 1] = 0;
		for ( int i = 1; i <= N; ++i )
			scanf("%d", &P[i]);
		bool flag = true;
		for ( int i = 1; i <= N; ++i )
		{
			if ( P[i] >= P[i - 1] && P[i] >= P[i + 1] && flag )
			{
				res += P[i];
				flag = false;
			}
			else if ( P[i] <= P[i - 1] && P[i] <= P[i + 1] && !flag )
			{
				res -= P[i];
				flag = true;
			}
		}
		printf("%lld\n", res);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
