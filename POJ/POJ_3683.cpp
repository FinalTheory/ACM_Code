/**
 * @file POJ_3683.cpp
 * @brief   2-SAT�ж�+�����ģ����
 * @hint    ע������ж�����ʱ�������Ƿ��ཻ��
 *	    �������ǽ������¼Ϊ����ҿ�����ʽ��
 *	    ����ж���β��ص���ȡ�����ɡ�
 *	    2-SAT�Ĳ�����Щ�ط���Ҫע�⣬������ע�͡�
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
#include <stack>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
#define MAX_v 2010
#define MAX_e 1010 * 1010 * 2
int LOW[MAX_v], DFN[MAX_v];	//Tarjan�������������
bool Instack[MAX_v];		//��ǽڵ��Ƿ���ջ
int Belong[MAX_v];			//�ڵ������ڵ�ǿ��ͨ����
int TimeStamp, scc;			//ʱ�����ǿ��ͨ��������
int indeg[MAX_v];			//�������
int col[MAX_v];				//����Ⱦɫ
int _hash[MAX_v];			//�������¹�ͼ��Ķ�Ӧ���
struct Nodes
{
	int s, e;
} T[MAX_v];
bool not_overlap( int i, int j )
{
	if ( T[i].e <= T[j].s || T[j].e <= T[i].s ) return true;
	return false;
}
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
void Init()
{
	stk.top = -1;
	scc = TimeStamp = 0;
	CLR( DFN, 0 ); CLR( Instack, 0 );
}
int N;
void read()
{
	int h1, h2, m1, m2, len;
	char str1[20], str2[20];
	for ( int i = 0; i < N; ++i ) {
		scanf("%s %s %d", str1, str2, &len);
		sscanf(str1, "%d:%d", &h1, &m1);
		sscanf(str2, "%d:%d", &h2, &m2);
		T[i * 2].s = h1 * 60 + m1;
		T[i * 2].e = h1 * 60 + m1 + len;
		T[i * 2 + 1].s = h2 * 60 + m2 - len;
		T[i * 2 + 1].e = h2 * 60 + m2;
	}
}
void Build()
{
	CLR( head, -1 ); p_edges = 0;
	for ( int i = 0; i < 2 * N; i += 2 )
		for ( int j = i + 2; j < 2 * N; j += 2 )
		{
			if ( !not_overlap( i, j ) ) {
				Add_Edge( i, j + 1 );
				Add_Edge( j, i + 1 );
			}
			if ( !not_overlap( i, j + 1 ) ) {
				Add_Edge( i, j );
				Add_Edge( j + 1, i + 1 );
			}
			if ( !not_overlap( i + 1, j ) ) {
				Add_Edge( i + 1, j + 1 );
				Add_Edge( j, i );
			}
			if ( !not_overlap( i + 1, j + 1 ) ) {
				Add_Edge( i + 1, j );
				Add_Edge( j + 1, i );
			}
		}
}
//����ͼ�ȽϾ��м�����
//�������ǰ����е����һ�飬�ӵ�ǰ����ڽӵ�������scc����ǰ�㱾��������scc��һ����
//ע��ǰ�����������㲻����ͬһ��scc�У������Ҫ���µ�ǰ������scc����ȡ�
void Build_DAG()
{
	CLR( indeg, 0 );
	CLR( head_DAG, -1 ); p_dag = 0;
	for ( int u = 0; u < 2 * N; ++u )
		for ( int e = head[u]; e != -1; e = edges[e].next ) {
			int v = edges[e].to;
			if ( Belong[u] != Belong[v] ) {
				DAG_Edge( Belong[v], Belong[u] );
				indeg[Belong[u]]++;
			}
		}
}
//�������������Ҳ�и���Trick�ĵط�
//��������Ҫ���½���scc��ŵ���Թ�ϵ��
//����֪�������κ�һ��2i/2i+1�Ǵ�����Թ�ϵ�ĵ㣻
//���ǵ�ӳ�䵽scc�ı�ź�Ͳ����ˣ���������Ҫ�ֶ��ٹ�ϣһ�¡�
void Topo_Sort()
{
	for ( int i = 0; i < N; ++i )
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
		//Ȼ������������Ĺ����У����ǿ���ֱ�ӶԵ����Ⱦɫ��
		//��Ϊ���ǰ�����������ֵģ���������ѡȡ�����ʱ����Ҫ��
		//���ڡ���ѡȡ����ǣ����ǵ��Գ��ԣ���ǰ��ǡ�ѡȡ�����������ȼ�ȻΪ�㣬
		//��ô����Եġ���ѡȡ���ĵ���Ⱦ����㣬Ҳ����˵����Ҳ�޷������´����ˡ�
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
void out( int i )
{
	printf("%02d:%02d " , T[i].s / 60, T[i].s % 60);
	printf("%02d:%02d\n", T[i].e / 60, T[i].e % 60);
}
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_s, program_end;
	program_s = clock();
#endif
	while ( scanf("%d", &N) != EOF )
	{
		Init();
		read();
		Build();
		for ( int i = 0; i < 2 * N; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < N; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if (!flag) {
			puts("NO");
			continue;
		}
		Build_DAG();
		Topo_Sort();
		puts("YES");
		//��󣬵�����������ɺ󣬱������е���������ͨ��֧���鿴��Ⱦɫ�����
		//������scc��Ⱦɫ���������������������Եĵ㣬��������������ɡ�
		for ( int i = 0; i < 2 * N; i += 2 )
			if ( col[Belong[i]] == 1 ) {
				out(i);
			} else {
				out(i ^ 1);
			}
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_s ) << " MS" << endl;
#endif
}
