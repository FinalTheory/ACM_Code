/**
 * @file POJ_3648.cpp
 * @brief   2-SATģ����
 * @hint    ��������Ҫ��ѡ��һЩ������������һ�ߡ�Լ��������ÿ�Է�����ֻ��ѡһ���ˡ�
 *	    ���Ҵ��ںܶ���˲���ͬʱ��������Ķ��棬����ֻҪ����ȥ����Ҫ��ѡȡ�������������ˣ�
 *	    �������ģ�;�������2-SAT�������ж���ѡȡ�����Ҵ��ڳ�ͻ��ϵ��
 *	    ���ǵ���Ҫ��������������Աߵ��ˣ���������ѡȡȾɫ��������ͬ���ˡ�
 *	    ����Ⱦɫʱ�����ǿ϶�ѡȡ���������һ��Ҫѡȡ�����ɷ���ʱ����ѡ������ˣ���
 *	    ��������һ�������ﵽ�ɷ������ߣ���֤�˺��潨����ͼ��ʱ���ɷ򱻱��Ϊѡȡ��
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
const int INF = 0x3f3f3f3f;
#define MAX_v 100
#define MAX_e 100 * 100 * 2
int LOW[MAX_v], DFN[MAX_v];	//Tarjan�������������
bool Instack[MAX_v];		//��ǽڵ��Ƿ���ջ
int Belong[MAX_v];			//�ڵ������ڵ�ǿ��ͨ����
int TimeStamp, scc;			//ʱ�����ǿ��ͨ��������
int indeg[MAX_v];			//�������
int col[MAX_v];				//����Ⱦɫ
int _hash[MAX_v];			//�������¹�ͼ��Ķ�Ӧ���
struct TMD
{
	int to, next;
} edges[MAX_e], DAG[MAX_e];
int p_edges, p_dag;
struct NND
{
	int top;
	int elem[MAX_v];
} stk;
int head[MAX_v], head_DAG[MAX_v];
void Add_Edge( int _u, int _v )
{
	edges[p_edges].to = _v;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
}
void DAG_Edge( int _u, int _v )
{
	DAG[p_dag].to = _v;
	DAG[p_dag].next = head_DAG[_u];
	head_DAG[_u] = p_dag++;
}
void Init()
{
	stk.top = -1;
	scc = TimeStamp = 0;
	CLR( DFN, 0 ); CLR( Instack, 0 );
	CLR( head, -1 ); p_edges = 0;
}
int n, m;
void read()
{
	char str1[20], str2[20];
	char * ptr, * pos1, * pos2, c1, c2;
	int a, b;
	Add_Edge( 1, 0 );
	for ( int i = 0; i < m; ++i )
	{
		scanf("%s %s", str1, str2);
		for ( ptr = str1; *ptr; ++ptr ) if ( isalpha(*ptr) )
			pos1 = ptr;
		for ( ptr = str2; *ptr; ++ptr ) if ( isalpha(*ptr) )
			pos2 = ptr;
		c1 = *pos1; c2 = *pos2;
		*pos1 = *pos2 = 0;
		sscanf(str1, "%d", &a); sscanf(str2, "%d", &b);
		if ( c1 == 'h' && c2 == 'h' ) {
			Add_Edge( a * 2, b * 2 + 1 );
			Add_Edge( b * 2, a * 2 + 1 );
		} else if ( c1 == 'w' && c2 == 'h' ) {
			Add_Edge( a * 2 + 1, b * 2 + 1 );
			Add_Edge( b * 2, a * 2 );
		} else if ( c1 == 'h' && c2 == 'w' ) {
			Add_Edge( a * 2, b * 2 );
			Add_Edge( b * 2 + 1, a * 2 + 1 );
		} else if ( c1 == 'w' && c2 == 'w' ) {
			Add_Edge( a * 2 + 1, b * 2 );
			Add_Edge( b * 2 + 1, a * 2 );
		}
	}
}
void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	stk.elem[++stk.top] = u;
	Instack[u] = true;
	for ( int e = head[u]; e != -1; e = edges[e].next )
	{
		v = edges[e].to;
		if ( !DFN[v] ) {
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		} else if ( Instack[v] ) {
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] ) {
		++scc;
		do {
			v = stk.elem[stk.top--];
			Instack[v] = false;
			Belong[v] = scc;
		} while ( v != u );
	}
}
void Build_DAG()
{
	CLR( indeg, 0 );
	CLR( head_DAG, -1 ); p_dag = 0;
	for ( int u = 0; u < 2 * n; ++u )
		for ( int e = head[u]; e != -1; e = edges[e].next ) {
			int v = edges[e].to;
			if ( Belong[u] != Belong[v] ) {
				DAG_Edge( Belong[v], Belong[u] );
				indeg[Belong[u]]++;
			}
		}
}
void Topo_Sort()
{
	for ( int i = 0; i < n; ++i )
	{
		_hash[Belong[i * 2]] = Belong[i * 2 + 1];
		_hash[Belong[i * 2 + 1]] = Belong[i * 2];
	}
	CLR( col, 0 );
	stack<int> tmp;
	for ( int i = 1; i <= scc; ++i ) if ( !indeg[i] )
		tmp.push(i);
	while ( !tmp.empty() )
	{
		int u = tmp.top(); tmp.pop();
		if ( !col[u] ) {
			col[u] = 1;
			col[_hash[u]] = 2;
		}
		for ( int e = head_DAG[u]; e != -1; e = DAG[e].next ) {
			indeg[DAG[e].to]--;
			if ( indeg[DAG[e].to] == 0 )
				tmp.push(DAG[e].to);
		}
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
	while ( scanf("%d %d", &n, &m) && m + n )
	{
		Init();
		read();
		for ( int i = 0; i < 2 * n; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < n; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if ( !flag ) {
			puts("bad luck");
			continue;
		}
		Build_DAG();
		Topo_Sort();
		for ( int i = 2; i < 2 * n; i += 2 )
			if ( col[Belong[i]] == col[Belong[1]] ) {
				printf("%dh ", i / 2);
			} else {
				printf("%dw ", i / 2);
			}
		puts("");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

