/**
 * @file HDU_1814.cpp
 * @brief   2-SAT��Ŀ������Ҫ�������С�ֵ��������Ǳ�����⡣
 * @hint    ���Ǻ�������2-SATһ���Ľ�ͼ˼·������ֱ��DFS��⡣
 *	    ����ÿ��δȾɫ�ĵ���ͼDFSȾɫ�����ձߵĹ�ϵ�ѡ�ѡȡ����Ǵ�����ȥ��������Ӧ���ǡ���ѡȡ����
 *	    ��DFS������ѡȡ��ʱ��˵����ǰ�����Ч����ͨ�����Ѿ�Ⱦɫ����ˣ�
 *	    �����������ѡȡ����˵����Ҫѡȡһ���Ѿ����Ϊ����ѡȡ�ĵ㣬��Ⱦɫʧ�ܡ�
 *	    �ڱ�����ʱ�������ĳ����Ⱦʧ���˵Ļ�������ͼ�Ӷ�Ӧ��Ⱦɫ��
 *	    �����ʧ�ܵĻ���˵���Ҳ������н��ˡ�
 *	    ע��DFS��ʱ��ҪȾɫ�����ţ��������������Ⱦɫ��ǵ�ʱ���ʡʱ�䡣
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
			//���ѡ��һ�����Ҳ����Ϸ���
			//�������ǰ������Ⱦɫ
			for ( int j = 0; j < p_ans; ++j ) {
				col[ans[j] ^ 1] = 0;
				col[ans[j]] = 0;
			}
			//Ȼ����ȥȾɫ���Ķ�Ӧ��
			//�����ʧ�ܾ������ʧ����
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

