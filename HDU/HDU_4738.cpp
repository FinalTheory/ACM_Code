/**
 * @file HDU_4738.cpp
 * @brief   求权值最小割边的模版题
 * @hint    这题有几个大坑，首先是如果图不联通，输出0；
 *	    如果最小边权为0，则输出1；如果没有桥输出-1；
 *	    最后才是输出ans中的答案。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-20
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
#define MAX_e 1010
#define MAX 1010

int wei[MAX_e][MAX_e];
int TimeStamp, ans, v_num;
int LOW[MAX+10], DFN[MAX+10];
vector<int> Adja[MAX_e];
void Tarjan( int u, int fa )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( v == fa )
			continue;
		if ( !DFN[v] ) {
			Tarjan(v, u);
			LOW[u] = min( LOW[u], LOW[v] );
			if ( LOW[v] > DFN[u] && wei[u][v] < ans )
				ans = wei[u][v];
		} else {
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	++v_num;
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
	int N, M, u, v, w;
	while ( scanf("%d %d", &N, &M) && M + N )
	{
		for ( int i = 1; i <= N; ++i )
			Adja[i].clear();
		CLR( wei, -1 );
		for ( int i = 1; i <= M; ++i )
		{
			scanf("%d %d %d", &u, &v, &w);
			//这是一个不错的去除重边的办法，适用于节点数比较少的情况
			if ( wei[u][v] != -1 || wei[v][u] != -1 )
			{
				wei[u][v] = wei[v][u] = INF;
				continue;
			}
			Adja[u].push_back(v);
			Adja[v].push_back(u);
			wei[u][v] = wei[v][u] = w;
		}
		CLR( DFN, 0 ); CLR( LOW, 0 );
		TimeStamp = 0; ans = INF; v_num = 0;
		Tarjan(1, -1);
		if ( ans == INF )
			puts("-1");
		else if ( v_num < N )
			puts("0");
		else if ( ans == 0 )
			puts("1");
		else
			printf("%d\n", ans);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
