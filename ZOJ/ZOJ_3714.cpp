/**
 * @file ZOJ_3714.cpp
 * @brief   水题，枚举！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-18
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
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int data[600];
int nums[300];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, N, M, i;
	scanf("%d", &T);
	while ( T-- )
	{
		CLR(data, 0);
		scanf("%d %d", &N, &M);
		for ( i = 1; i <= N; ++i )
		{
			scanf("%d", &nums[i]);
			data[i] = data[i-1] + nums[i];
		}
		for ( i = N + 1; i <= 2 * N; ++i )
			data[i] = data[i-1] + nums[i-N];
		int max = -1;
		for ( i = 1; i <= N; ++i )
			if ( data[i + M - 1] - data[i-1] > max )
				max = data[i + M - 1] - data[i-1];
		printf("%d\n", max);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

