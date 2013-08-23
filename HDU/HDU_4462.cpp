/**
 * @file HDU_4462.cpp
 * @brief   裸的枚举，题意读错了简直跪烂！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-23
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
int x[100], y[100], R[100];
bool _map[100][100];
bool used[20];
int N, K;
int _res;
void DFS( int depth )
{
	if ( depth == K + 1 )
		return;
	for ( int i = 1; i <= N; ++i )
		for ( int j = 1; j <= N; ++j ) if ( !_map[i][j] )
		{
			bool found = false;
			for ( int k = 0; k < K; ++k ) if ( used[k] )
			{
				if ( abs( i - x[k] ) + abs( j - y[k] ) <= R[k] )
				{
					found = true;
					break;
				}
			}
			if ( !found )
				goto cont;
		}
	int sum = 0;
	for ( int i = 0; i < K; ++i ) if ( used[i] )
		++sum;
	if ( sum < _res ) _res = sum;
cont:
	used[depth] = true;
	DFS(depth + 1);
	used[depth] = false;
	DFS(depth + 1);
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
	while ( scanf("%d", &N) && N )
	{
		CLR( used, 0 );
		CLR( _map, 0 );
		scanf("%d", &K);
		for ( int i = 0; i < K; ++i )
		{
			scanf("%d %d", &x[i], &y[i]);
			_map[x[i]][y[i]] = true;
		}
		for ( int i = 0; i < K; ++i )
			scanf("%d", &R[i]);
		if ( K == N * N )
		{
			puts("0");
			continue;
		}
		_res = INF;
		DFS(0);
		if ( _res < INF )
			printf("%d\n", _res);
		else
			puts("-1");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
