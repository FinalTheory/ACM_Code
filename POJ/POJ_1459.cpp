/**
 * @file POJ_1459.cpp
 * @brief   最大流模版题
 * @hint    注意添加超级源点和超级汇点即可
 * @feeling 数组开小了，居然TLE两发！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-06
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
#define MAX_v 110
#define MAX_e 21000
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef long long LL;
using namespace std;
const int INF = 0x3f3f3f3f;

int _map[MAX_v][MAX_v];
//邻接表存储图
struct TMD
{
	int from, to, cap, flow, next;
} edges[MAX_e];
int head[MAX_v];
//到汇点的距离，某个点的前驱、间隙优化时记录到汇点距离为n的节点个数
int dist[MAX_v], pre[MAX_v], gap[MAX_v], cur[MAX_v];
bool vis[MAX_v];
int p_edges;
void Add_Edge( int _u, int _v, int _cap )
{
	edges[p_edges].from = _u; edges[p_edges].to = _v;
	edges[p_edges].cap = _cap; edges[p_edges].flow = 0;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
	edges[p_edges].from = _v; edges[p_edges].to = _u;
	edges[p_edges].cap = 0; edges[p_edges].flow = 0;
	edges[p_edges].next = head[_v];
	head[_v] = p_edges++;
}

//定义源点、汇点
int Src, Dst;
bool BFS()
{
	CLR(vis, 0);
	queue<int> Q;
	Q.push(Dst);
	vis[Dst] = true;
	dist[Dst] = 0;
	int u, v, e;
	while ( !Q.empty() )
	{
		u = Q.front(); Q.pop();
		for ( e = head[u]; e != -1; e = edges[e].next ) if ( !vis[edges[e].to] )
		{
			vis[edges[e].to] = true;
			dist[edges[e].to] = dist[u] + 1;
			Q.push(edges[e].to);
		}
	}
	return vis[Src];
}

int Augment()
{
	int u = Dst, cur_flow = INF, e;
	while ( u != Src )
	{
		e = pre[u];
		cur_flow = min( cur_flow, edges[e].cap - edges[e].flow );
		u = edges[e].from;
	}
	u = Dst;
	while ( u != Src )
	{
		e = pre[u];
		edges[e].flow += cur_flow;
		edges[e^1].flow -= cur_flow;
		u = edges[e].from;
	}
	return cur_flow;
}

int ISAP( int num_nodes )
{
	int max_flow = 0;
	BFS();
	CLR( gap, 0 );
	memcpy( cur, head, sizeof(head) );
	for ( int i = 0; i < num_nodes; ++gap[dist[i++]] );
	int u = Src, e;
	bool Advanced = false;
	while ( dist[Src] < num_nodes )
	{
		if ( u == Dst )
		{
			max_flow += Augment();
			u = Src;
		}
		Advanced = false;
		for ( e = cur[u]; e != -1; e = edges[e].next ) if ( edges[e].cap > edges[e].flow && dist[u] == dist[edges[e].to] + 1 )
		{
			Advanced = true;
			cur[u] = e;
			pre[edges[e].to] = e;
			u = edges[e].to;
			break;
		}
		if ( !Advanced )
		{
			int _min = num_nodes - 1;
			for ( e = head[u]; e != -1; e = edges[e].next ) if ( edges[e].cap > edges[e].flow )
				_min = min( _min, dist[edges[e].to] );
			if ( --gap[dist[u]] == 0 ) break;	//GAP优化
			gap[dist[u] = _min + 1]++;
			cur[u] = head[u];
			if ( u != Src )
				u = edges[pre[u]].from;
		}
	}
	return max_flow;
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
	int n, np, nc, m, u, v, z;
	char buffer[100];
	while ( scanf("%d %d %d %d", &n, &np, &nc, &m) != EOF )
	{
		CLR(_map, 0);
		p_edges = 0;
		CLR( head, -1 );
		for ( int i = 0; i < MAX_e; ++i ) edges[i].next = -1;
		Src = n; Dst = n + 1;
		char ch;
		for ( int i = 0; i < m; ++i )
		{
			scanf("%s", buffer);
			sscanf(buffer, "(%d,%d)%d", &u, &v, &z);
			_map[u][v] += z;
		}
		for ( int i = 0; i < np; ++i )
		{
			scanf("%s", buffer);
			sscanf(buffer, "(%d)%d", &u, &z);
			Add_Edge( Src, u, z );
		}
		for ( int i = 0; i < nc; ++i )
		{
			scanf("%s", buffer);
			sscanf(buffer, "(%d)%d", &u, &z);
			Add_Edge( u, Dst, z );
		}
		for ( int i = 0; i < n; ++i )
			for ( int j = 0; j < n; ++j ) if ( _map[i][j] )
				Add_Edge( i, j, _map[i][j] );
		printf("%d\n", ISAP( n + 2 ));
	}


#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
