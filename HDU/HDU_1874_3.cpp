/**
 * @file HDU_1874_3.cpp
 * @brief   Dijkstraģ���⣬ʹ�����ȶ����Ż�������������ͼ��ʹ���˾�̬�ڽӱ���
 * �����Ǵ洢�����бߣ����Բ��ÿ����رߵ��������������д����رߵĻ����Կ������ڽӾ����ϣȥ�ء�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-02
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
#define MAX_p 100
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef pair<int, int> TMD;
int u[MAX+10], v[MAX+10], w[MAX+10], head[MAX_p+10], next_e[MAX+10], d[MAX_p+10];
bool visited[MAX_p+10];
priority_queue< TMD, vector<TMD>, greater<TMD> > q;

int N, M, S, T;

void Dijkstra()
{
	CLR( d, 0x3f );
	CLR( visited, 0 );
	d[S] = 0;
	q.push( make_pair(d[S], S) );
	while ( !q.empty() )
	{
		TMD tmp = q.top(); q.pop();
		int p = tmp.second;
		//������Ѿ����ʹ��ĵ㣬ֱ�Ӽ����������ǵ�
		if ( visited[p] )
			continue;
		visited[p] = true;
		//�Ե�ǰ�Ľ϶̾����ɳ������ڽӵ�
		for ( int e = head[p]; e != -1; e = next_e[e] ) if ( d[v[e]] > d[p] + w[e] )
		{
			d[v[e]] = d[p] + w[e];
			//���ɳڹ�����ڽӵ����
			q.push( make_pair(d[v[e]], v[e]) );
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
	while ( cin >> N >> M && M + N )
	{
		CLR( head, -1 );
		CLR( next_e, -1 );
		for ( int i = 0; i < 2 * M; i += 2 )
		{
			cin >> u[i] >> v[i] >> w[i];
			next_e[i] = head[u[i]];
			head[u[i]] = i;
			u[i+1] = v[i]; v[i+1] = u[i]; w[i+1] = w[i];
			next_e[i+1] = head[u[i+1]];
			head[u[i+1]] = i + 1;
		}
		cin >> S >> T;
		//S = 1; T = N;
		Dijkstra();
		if ( d[T] < INF )
			cout << d[T] << endl;
		else
			cout << "-1" << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}