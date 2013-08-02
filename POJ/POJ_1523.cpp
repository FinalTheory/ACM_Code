/**
 * @file POJ_1523.cpp
 * @brief   Tarjan算法求割点，模版题。
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
#define MAX 1000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int LOW[MAX+10], DFN[MAX+10];
int TimeStamp;
vector<int> Adja[MAX+10];
vector< pair<int,int> > res;
int ans;
void Tarjan( int u, bool isroot )
{
	int v, cnt = 0;//记录节点的子树个数
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v, false);
			LOW[u] = min( LOW[u], LOW[v] );
			//是根节点的话，显然v就是一个叶子
			if ( isroot )
				cnt++;
			//非叶子节点，且不存在回边
			else if ( LOW[v] >= DFN[u] )
				cnt++;
		}
		else
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( isroot && cnt >= 2 )
		//如果是根节点，那么去掉之后剩余的连通分支个数就是子树个数
		//因为一定会有连通分支的
		res.push_back( make_pair(u, cnt) );
	else if ( !isroot && cnt )
		//如果不是根节点，图本身至少会有一个连通分支，所以要加上一
		res.push_back( make_pair(u, cnt + 1) );
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
	int u, v;
	bool has_input;
	int idx = 1;
	while (true)
	{
		has_input = false;
		for ( int i = 1; i <= MAX; ++i )
			Adja[i].clear();
		while ( true )
		{
			scanf("%d", &u);
			if ( u != 0 )
			{
				has_input = true;
				scanf("%d", &v);
				Adja[u].push_back(v);
				Adja[v].push_back(u);
			}
			else if ( has_input )
			{
				break;
			}
			else
			{
				goto end;
			}
		}
		CLR( DFN, 0 );
		res.clear();
		TimeStamp = 0; ans = 0; 
		Tarjan( 1, true );
		printf("Network #%d\n", idx++);
		if ( res.size() == 0 )
			printf("  No SPF nodes\n\n");
		else
		{
			sort( res.begin(), res.end() );
			for ( int i = 0; i < res.size(); ++i )
				printf("  SPF node %d leaves %d subnets\n", res[i].first, res[i].second);
			puts("");
		}
	}
	end:;
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
