/**
 * @file POJ_2186.cpp
 * @brief   Tarjan模版题，加缩点。
 * 这里利用了图论的一个性质，有向无环图（DAG）中，从任意一个点出发，必定可以到达某一个出度为0的点。
 * 将强连通分量视作点就可以了，这也就是所谓的缩点。
 * 首先跑一遍Tarjan算法，然后将每个强连通分量视为点，计算其出度。
 * 如果出度为零的强连通分量多于一个，就说明不存在，否则那个出度为零的强连通分量的点的个数即为答案。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-01
 */
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
#define MAX 10000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int LOW[MAX+10], DFN[MAX+10], Belong[MAX+10], TimeStamp, ans, out_deg[MAX+10];
bool Instack[MAX+10];
vector<int> Adja[MAX+10];
stack<int> Stack;
void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	Stack.push(u); Instack[u] = true;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		}
		else if ( Instack[v] )
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] )
	{
		++ans;
		do 
		{
			v = Stack.top();
			Stack.pop();
			Instack[v] = false;
			Belong[v] = ans;
		} while ( v != u );
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
	int N, M;
	while ( cin >> N >> M )
	{
		int u, v;
		for ( int i = 0; i <= N; ++i )
			Adja[i].clear();
		for ( int i = 0; i < M; ++i )
		{
			cin >> u >> v;
			Adja[u].push_back(v);
		}
		//各种初始化
		while ( !Stack.empty() ) Stack.pop();
		CLR( DFN, 0 ); CLR( Instack, 0 );
		TimeStamp = 0; ans = 0;
		for ( int i = 1; i <= N; ++i )
			if ( !DFN[i] )
				Tarjan(i);
		CLR( out_deg, 0 );
		for ( int u = 1; u <= N; ++u )
			for ( int i = 0; i < Adja[u].size(); ++i )
			{
				int v = Adja[u][i];
				if ( Belong[u] != Belong[v] )
					out_deg[Belong[u]]++;
			}
		int sum = 0, target = -1;
		bool found = false;
		for ( int i = 1; i <= ans; ++i )
			if ( !out_deg[i] )
			{
				if ( !found )
				{
					found = true;
					target = i;
				}
				else
				{
					target = -1;
					break;
				}
			}
		if ( target == -1 )
			cout << "0\n";
		else
		{
			for ( int u = 1; u <= N; ++u ) if ( Belong[u] == target )
				sum++;
			cout << sum << endl;
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
