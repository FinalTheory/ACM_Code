/**
 * @file HDU_4750.cpp
 * @brief   ���鼯��Ŀ��
 * @hint    ������ʱ���Ѿ��뵽�����ò��鼯��С�����������ʣ�����õ㼯�Ӷ�����𰸣�
 *	    Ҳ�뵽�˽�ѯ������ת���ߣ��Ӷ�һ�α����ó������
 *	    ��Ҫ��һЩ�����ϸ��û��ã������Ǽӱߵ�˳��Ҫ������ĿҪ��f>=t���͵ôӴ�С��
 *	    ���������Ͳ����㡰����е���Сֵ����һ��ȷ���ˡ�
 *	    ���������κϲ�������Ԫ�ص�˳����һ��û����á�
 *	    �������˱�����⣬���ڵ�һ�����⣬���Է�����˼�������ҳ���������f<t���������������������У�
 *	    �ڶ������⣬�����⿴���Ǵ���ͬ��ͨ�����ĵ㼯��ÿ�κϲ�һ����ͨ������
 *	    ���ӵĶ�����������ͨ������Ԫ������֮�ͳ���2���ɡ�
 *	    �������ڼ��ϵĺϲ������м�������������������ĵ��������
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-22
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
#define MAX 10010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int _set[MAX], num[MAX];
int ANS[100010];
int find( int x )
{
	int r = x, i = x, j;
	while ( _set[r] != r )
		r = _set[r];
	while ( i != r )
	{
		j = _set[i];
		_set[i] = r;
		i = j;
	}
	return r;
}
void merge( int a, int b )
{
	//�ϲ���ʱ�����Ԫ�ظ���
	if ( a < b )
	{
		num[a] += num[b];
		_set[b] = a;
	}
	else
	{
		num[b] += num[a];
		_set[a] = b;
	}
}
struct TMD
{
	int u, v, w;
} roads[500010];
bool operator < ( const TMD & A, const TMD & B )
{
	return A.w < B.w;
}
struct NND
{
	int idx, t;
} Querys[100010];
bool fuck1( const NND & A, const NND & B )
{
	return A.t < B.t;
}
bool fuck2( const NND & A, const NND & B )
{
	return A.idx < B.idx;
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
	int n, m, a, b, c, p;
	TMD tmp;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		int total = n * ( n - 1 );
		for ( int i = 0; i < n; i++ )
		{
			_set[i] = i;
			num[i] = 1;
		}
		for ( int i = 0; i < m; ++i )
			scanf("%d %d %d", &roads[i].u, &roads[i].v, &roads[i].w);
		sort( roads, roads + m );
		scanf("%d", &p);
		for ( int i = 0; i < p; ++i )
		{
			scanf("%d", &Querys[i].t);
			Querys[i].idx = i;
		}
		sort( Querys, Querys + p, fuck1 );
		int p_roads = 0;
		int ans = 0;
		for ( int i = 0; i < p; ++i )
		{
			
			while ( p_roads < m && roads[p_roads].w < Querys[i].t )
			{
				int rt_a = find( roads[p_roads].u );
				int rt_b = find( roads[p_roads].v );
				if ( rt_a == rt_b )
				{
					p_roads++;
					continue;
				}
				ans += num[rt_a] * num[rt_b] * 2;
				merge( rt_a, rt_b );
				p_roads++;
			}
			ANS[Querys[i].idx] = total - ans;
		}
		for ( int i = 0; i < p; ++i )
			printf("%d\n", ANS[i]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
