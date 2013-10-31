/**
 * @file POJ_3258.cpp
 * @brief   还是二分思想，这次是真没搞明白边界，但是可以AC。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-27
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
int dist[50010];
int L, N, M;
bool check( int val )
{
	int j, res = 0;
	for ( int i = 0; i <= N + 1; i = j )
		for ( j = i + 1; dist[j] - dist[i] < val && j <= N + 1; ++j )
			res++;
	if ( res > M )
		return true;
	else
		return false;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%d %d %d", &L, &N, &M) != EOF )
	{
		int _min = 1000000010;
		dist[0] = 0;
		dist[N + 1] = L;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &dist[i]);
			if ( dist[i] - dist[i - 1] < _min ) _min = dist[i] - dist[i - 1];
		}
		sort( dist + 1, dist + N + 1 );
		int low = _min, high = L;
		while ( low <= high )
		{
			int mid = ( low + high ) >> 1;
			if ( check(mid) )
				high = mid - 1;
			else
				low = mid + 1;
		}
		printf("%d\n", high);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

