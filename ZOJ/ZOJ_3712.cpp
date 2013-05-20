/**
 * @file ZOJ_3712.cpp
 * @brief   贪心水题，不废话了，辉神居然还TLE了……
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

int num[2000];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, A, B, C, i, all, min, max;
	scanf("%d", &T);
	for ( i = 1; i <= 1600; ++i )
		num[i] = 2 * (i-1) + 1;
	while ( T-- )
	{
		min = max = 0;
		scanf("%d %d %d", &A, &B, &C);
		for ( i = 1; i <= A; ++i )
			min += 300 * num[i];
		for ( i = A + 1; i <= A + B; ++i )
			min += 100 * num[i];
		for ( i = A + B + 1; i <= A + B + C; ++i )
			min += 50 * num[i];

		for ( i = 1; i <= C; ++i )
			max += 50 * num[i];
		for ( i = C + 1; i <= C + B; ++i )
			max += 100 * num[i];
		for ( i = C + B + 1; i <= A + B + C; ++i )
			max += 300 * num[i];
		printf("%d %d\n", min, max);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

