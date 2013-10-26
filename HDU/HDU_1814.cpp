/**
 * @file HDU_1814.cpp
 * @brief   2-SAT题目，由于要求输出最小字典序，所以是暴力求解。
 * @hint    还是和正常的2-SAT一样的建图思路，但是直接DFS求解。
 *	    遍历每个未染色的点试图DFS染色，按照边的关系把“选取”标记传递下去，并将对应点标记“不选取”。
 *	    当DFS遇到“选取”时，说明当前这个有效的连通分量已经染色完毕了；
 *	    如果遇到“不选取”，说明需要选取一个已经标记为不能选取的点，即染色失败。
 *	    在遍历的时候。如果从某个点染失败了的话，就试图从对应点染色；
 *	    如果再失败的话，说明找不到可行解了。
 *	    注意DFS的时候要染色点的序号，这样可以在清除染色标记的时候节省时间。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-25
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
#define MAX_v 16010
#define MAX_e 40010
int col[MAX_v];
struct TMD
{
	int from, to, next;
} edges[MAX_e];
int p_edges, head[MAX_v];
void Add_Edge( int _u, int _v )
{
	edges[p_edges].from = _u; edges[p_edges].to = _v;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
}
void Init()
{
	CLR( col, 0 );
	CLR( head, -1 );
	p_edges = 0;
}
int ans[MAX_v], p_ans;
bool DFS( int u )
{
	if ( col[u] == 1 ) return true;
	if ( col[u] == 2 ) return false;
	col[u] = 1;
	col[u ^ 1] = 2;
	ans[p_ans++] = u;
	for ( int e = head[u]; e != -1; e = edges[e].next ) {
		int v = edges[e].to;
		if ( !DFS(v) ) return false;
	}
	return true;
}
int n, m;
bool Solve()
{
	for ( int i = 0; i < 2 * n; ++i ) {
		if ( col[i] ) continue;
		p_ans = 0;
		if ( !DFS(i) ) {
			//如果选择一个点找不到合法答案
			//就清除先前的所有染色
			for ( int j = 0; j < p_ans; ++j ) {
				col[ans[j] ^ 1] = 0;
				col[ans[j]] = 0;
			}
			//然后再去染色它的对应点
			//如果再失败就是真的失败了
			p_ans = 0;
			if ( !DFS(i ^ 1) )
				return false;
		}
	}
	return true;
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
	int a, b;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		Init();
		for ( int i = 0; i < m; ++i ) {
			scanf("%d %d", &a, &b);
			a--; b--;
			Add_Edge( a, b ^ 1 );
			Add_Edge( b, a ^ 1 );
		}
		if ( Solve() ) {
			for ( int i = 0; i < 2 * n; ++i ) if ( col[i] == 1 )
				printf("%d\n", i + 1);
		} else {
			puts("NIE");
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

