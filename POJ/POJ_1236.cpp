/**
 * @file POJ_1236.cpp
 * @brief   强连通分量Tarjan算法。
 * 首先缩点，然后统计入度为零的点有多少，即为第一问的答案；
 * 对于第二问，显然要在不同的连通分量之间添加边，所以答案是入度为零的点数和出度为零的点数的最大值。
 * 注意对于整个图强连通的情况需要特判，也就是不需要增加边，在这里跪了一发。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

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
#define MAX 100
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
const int INF = 0x3f3f3f3f;
//强连通分量出入度
int In[MAX+10], Out[MAX+10];
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
	int N, num;
	while ( scanf("%d", &N) != EOF )
	{
		for ( int i = 1; i <= N; ++i )
			Adja[i].clear();
		for ( int i = 1; i <= N; ++i )
		{
			while (true)
			{
				scanf("%d", &num);
				if ( num == 0 ) break;
				Adja[i].push_back(num);
			}
		}
		while ( !Stack.empty() ) Stack.pop();
		CLR( DFN, 0 ); CLR( Instack, 0 ); CLR( In, 0 );
		TimeStamp = 0; ans = 0;
		for ( int i = 1; i <= N; ++i )
			if ( !DFN[i] )
				Tarjan(i);
		if ( ans == 1 )
		{
			printf("1\n0\n");
			continue;
		}
		for ( int u = 1; u <= N; ++u )
		{
			for ( int j = 0; j < Adja[u].size(); ++j )
			{
				int v = Adja[u][j];
				if ( Belong[u] != Belong[v] )
				{
					++Out[Belong[u]];
					++In[Belong[v]];
				}
			}
		}
		int res = 0, a = 0, b = 0;
		for ( int i = 1; i <= ans; ++i )
			if ( !In[i] ) ++res;
		for ( int i = 1; i <= ans; ++i )
		{
			if ( !In[i] ) ++a;
			if ( !Out[i] ) ++b;
		}
		printf("%d\n%d\n", res, max(a, b));
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
