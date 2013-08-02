/**
 * @file HDU_3666.cpp
 * @brief   ���Լ��ģ����
 * ���ȣ����ǵ�����ͨͼ�����Կ��Բ�����Դ�㣬��ֱ�Ӵӵ�1��ʼ����SPFA��
 * ������Լ������һ���ڽӱ�Ȼ����һ��SPFA��ֻҪ�����ڸ�����˵�����ڽ⡣
 * ��Ҫע������жϸ����ķ���������ȡsqrt(M+N)Ϊ�����Ӵ���������M+N�Ļ���TLE��
 * ��Ŀ�ĺ��Ļ���������ν�ͼ��Ҫ�Ѵ��ڵ��ںŵ�Լ��ȡ��ֵ��ΪС�ڵ��ڣ������Ǹ��㲻�ÿ��Ǳ߽硣
 * ����Ҫ�����еı߼��뵽ͬһ��ͼ�У�������SPFAʱ���ǿ��ǵ������е�Լ����ϵ�������Ƿֿ���SPFA��
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-03
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
#define MAX_p 810
#define MAX_e 810 * 810
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int u[MAX_e], v[MAX_e], head[MAX_p], next_e[MAX_e], in_queue_times[MAX_p];
bool in_queue[MAX_p];
double w[MAX_e], d[MAX_p];
int limit;	//��Ӵ������ֵ
queue<int> q;
int N, M, L, U;
bool SPFA()
{
	int S = 0;
	while ( !q.empty() ) q.pop();
	for ( int i = 1; i <= M + N; ++i )
		d[i] = INF;
	d[S] = 0;
	CLR( in_queue, 0 );
	CLR( in_queue_times, 0 );
	q.push(S); in_queue[S] = true;
	//in_queue_times[S]++;
	while ( !q.empty() )
	{
		int p = q.front(); q.pop();
		in_queue[p] = false;
		for ( int e = head[p]; e != -1; e = next_e[e] ) if ( d[v[e]] > d[p] + w[e] )
		{
			d[v[e]] = d[p] + w[e];
			//������ɳڹ��ĵ㲻�ڶ����У��ͼ������
			if ( !in_queue[v[e]] )
			{
				in_queue[v[e]] = true;
				in_queue_times[v[e]]++;
				q.push(v[e]);
				if ( in_queue_times[v[e]] >= limit )
					return false;
			}
		}
	}
	return true;
}
int p = 0;	//��¼�ߵ����
void Add( int uu, int vv, double ww )
{
	u[p] = uu; v[p] = vv; w[p] = ww;
	next_e[p] = head[u[p]];
	head[u[p]] = p;
	p++;
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
	while ( scanf("%d %d %d %d", &N, &M, &L, &U) != EOF )
	{
		limit = sqrt( double(N + M) ) + 1;
		CLR( head, -1 ); CLR( next_e, -1 ); p = 0;
		int tmp; double log_c;
		double u = log( (double)U );
		double l = log( (double)L );
		for ( int i = 1; i <= M + N; ++i )
 			Add( 0, i, 0. );
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= M; ++j )
			{
				scanf("%d", &tmp);
				log_c = log( (double)tmp );
				Add( j + N, i, u - log_c );
				Add( i, j + N, log_c - l );
			}
		if ( SPFA() )
			printf("YES\n");
		else
			printf("NO\n");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
