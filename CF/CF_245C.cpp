/**
 * @file CF_245C.cpp
 * @brief   贪心问题
 * @hint    想明白为什么要从后往前更新，因为2*x+1的位置只能由后面的得到，所以一定先减少它，可达最小。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-16
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int a[110], n;
int min_depth, sum_all;

void DFS( int depth )
{
	int _max = -1, sum = 0;
	if ( sum_all == 0 )
	{
		min_depth = min(min_depth, depth);
		return;
	}
	for ( int x = 1; 2 * x + 1 <= n; ++x )
	{
		_max = -1; sum = 0;
		if ( a[x] ) sum++;
		if ( a[2*x] ) sum++;
		if ( a[2*x+1] ) sum++;
		if ( sum > _max ) {
			_max = sum;
		}
	}
	if ( _max == 0 )
		return;
	bool z1, z2, z3;
	for ( int x = 1; 2 * x + 1 <= n; ++x )
	{
		sum = 0; z1 = z2 = z3 = false;
		if ( a[x] ) {sum++;z1 = true;}
		if ( a[2*x] ) {sum++;z2 = true;}
		if ( a[2*x+1] ) {sum++;z3 = true;}
		if ( sum == _max )
		{
			if ( a[x] ) {sum_all--;a[x]--;}
			if ( a[2*x] ) {sum_all--;a[2*x]--;}
			if ( a[2*x+1] ) {sum_all--;a[2*x+1]--;}
			DFS(depth+1);
			if ( z1 ) {a[x]++;sum_all++;}
			if ( z2 ) {a[2*x]++;sum_all++;}
			if ( z3 ) {a[2*x+1]++;sum_all++;}
		}
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%d", &n) != EOF )
	{
		sum_all = 0;
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &a[i]);
			sum_all += a[i];
		}
		if ( n % 2 == 0 || n < 3 )
		{
			puts("-1");
			continue;
		}
		int ans = 0;
		for ( int x = n / 2; x >= 1; --x )
		{
			while ( a[2 * x] > 0 || a[2 * x + 1] > 0 )
			{
				a[x]--;
				a[2 * x]--;
				a[2 * x + 1]--;
				ans++;
			}
		}
		if ( a[1] > 0 )
			ans += a[1];
		printf("%d\n", ans);
// 		min_depth = INF;
// 		DFS(0);
// 		if ( min_depth != INF )
// 			printf("%d\n", min_depth);
// 		else
// 			puts("-1");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
