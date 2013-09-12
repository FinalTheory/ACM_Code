/**
 * @file 1002.cpp
 * @brief   图论水题，直接BFS一遍就行。注意题意！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-11
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
#define MAX 100010
const int INF = 0x3f3f3f3f;
vector<int> _map[MAX];
int dist[MAX];
bool vis[MAX];
queue<int> Q;
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, D, T;
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &N, &D);
		int u, v;
		CLR( vis, 0 );
		for ( int i = 0; i < N; ++i )
		{
			_map[i].clear();
			dist[i] = 0;
		}
		for ( int i = 1; i < N; ++i )
		{
			scanf("%d %d", &u, &v);
			_map[u].push_back(v);
			_map[v].push_back(u);
		}
		Q.push(0); vis[0] = true;
		while ( !Q.empty() )
		{
			u = Q.front(); Q.pop();
			for ( int i = 0; i < _map[u].size(); ++i )
			{
				v = _map[u][i];
				if ( !vis[v] )
				{
					vis[v] = true;
					dist[v] = dist[u] + 1;
					Q.push(v);
				}
			}
		}
		int sum = 0;
		for ( int i = 0; i < N; ++i )
			if ( dist[i] > D ) sum++;
		printf("%d\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
