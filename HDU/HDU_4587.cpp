/**
 * @file HDU_4587.cpp
 * @brief   Tarjan求割点。
 * @hint    枚举所有点先去掉，然后运行Tarjan，求出总共有多少个连通分量（这一步非常重要，深刻理解算法！）；
 *	    求连通分量的Tarjan算法，本质上求出的是去掉这个点之后增加的连通分量个数。
 *	    所以只要加上了原本总共的，再减去一也就是图中原本至少会有一个连通分量，就是答案了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-20
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
#define MAX 5000
int _remove;
int LOW[MAX+10], DFN[MAX+10], res[MAX+10];
bool visited[MAX+10];
int TimeStamp;
vector<int> Adja[MAX+10];
void Tarjan( int u, bool isroot )
{
	visited[u] = true;
	int v, cnt = 0;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( v == _remove ) continue;
		if ( !DFN[v] ) {
			Tarjan(v, false);
			LOW[u] = min( LOW[u], LOW[v] );
			if ( isroot )
				cnt++;
			else if ( LOW[v] >= DFN[u] )
				cnt++;
		} else {
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( isroot && cnt >= 2 )
		res[u] = cnt;
	else if ( !isroot && cnt )
		res[u] = cnt + 1;
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
	int N, M, u, v;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		for ( int i = 0; i < N; ++i )
			Adja[i].clear();
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d", &u, &v);
			Adja[u].push_back(v);
			Adja[v].push_back(u);
		}
		int ans = 1, sum;
		for ( _remove = 0; _remove < N; ++_remove )
		{
			CLR( DFN, 0 ); CLR(res, 0);
			sum = 0; TimeStamp = 0;
			for ( int i = 0; i < N; ++i ) if ( i != _remove && !DFN[i] )
			{
				Tarjan( i, true );
				sum++;
			}
			for ( int i = 0; i < N; ++i ) if ( i != _remove )
			{
				if ( sum + res[i] - 1 > ans )
					ans = sum + res[i] - 1;
			}
		}
		printf("%d\n", ans);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
