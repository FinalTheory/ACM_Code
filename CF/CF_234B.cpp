/**
 * @file CF_234B.cpp
 * @brief   排序水题
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
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

struct TMD
{
	int time, index;
	bool yes;
} hours[1010];

bool fuck( const TMD & A, const TMD & B )
{
	return A.time > B.time;
}
bool fuck2( const TMD & A, const TMD & B )
{
	return A.index < B.index;
}
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#else
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );
#endif
	int n, k;
	while ( scanf("%d %d", &n, &k) != EOF )
	{
		for ( int i = 0; i < n; ++i )
		{
			scanf("%d", &hours[i].time);
			hours[i].index = i + 1;
			hours[i].yes = false;
		}
		sort( hours, hours + n, fuck);
		for ( int i = 0; i < k; ++i )
			hours[i].yes = true;
		int ans = hours[k - 1].time;
		bool outed = false;
		sort( hours, hours + n, fuck2);
		printf("%d\n", ans);
		for ( int i = 0; i < n ; ++i ) if ( hours[i].yes )
		{
			if ( outed )
				printf(" %d", hours[i].index);
			else
			{
				outed = true;
				printf("%d", hours[i].index);
			}
		}
		puts("");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
