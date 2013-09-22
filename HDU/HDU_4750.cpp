/**
 * @file HDU_4750.cpp
 * @brief   并查集题目。
 * @hint    比赛的时候已经想到了利用并查集最小生成树的性质，来获得点集从而算出答案；
 *	    也想到了将询问在线转离线，从而一次遍历得出结果。
 *	    主要是一些具体的细节没想好，首先是加边的顺序，要满足题目要求f>=t，就得从大到小，
 *	    但是这样就不满足“最长边中的最小值”这一正确性了。
 *	    另外就是如何合并集合中元素的顺序，这一点没有想好。
 *	    后来看了别人题解，对于第一个问题，可以反过来思考，即找出所有满足f<t的数量，用总数减掉就行；
 *	    第二个问题，将问题看作是处理不同连通分量的点集，每次合并一个连通分量，
 *	    增加的对数是两个连通分量的元素数量之和乘以2即可。
 *	    这样就在集合的合并过程中计算出了所有满足条件的点对数量。
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
	//合并的时候加上元素个数
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
