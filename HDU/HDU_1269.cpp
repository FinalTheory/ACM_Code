/**
 * @file HDU_1269.cpp
 * @brief   求强连通分量的Tarjan算法的模版题。
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
//最早根节点数组以及时间戳数组
int LOW[MAX+10], DFN[MAX+10];
//标记是否在栈中
bool Instack[MAX+10];
//记录所属的强联通分量
int Belong[MAX+10];
//时间戳变量
int TimeStamp;
//Vector存储邻接表
vector<int> Adja[MAX+10];
//DFS遍历堆栈
stack<int> Stack;
//保存强连通分量个数
int ans;
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
	while ( cin >> N >> M && M + N )
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
		if ( ans == 1 )
			cout << "Yes\n";
		else
			cout << "No\n";
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
