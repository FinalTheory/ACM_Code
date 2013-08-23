/**
 * @file HDU_4417.cpp
 * @brief   树状数组区间查询
 * @hint    由于只是查询比某个数小的数有多少，限制条件只有一个，所以将静态查询改为动态即可。
 *	    也就是利用了排序思想，边查询边插入，然后记录答案再输出。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-23
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
int res[MAX];
struct TMD
{
	int num, idx;
} data[MAX];
struct NND
{
	int H, L, R, idx;
} query[MAX];
bool fuck( const TMD & A, const TMD & B )
{
	return A.num < B.num;
}
bool fuck2( const NND & A, const NND & B )
{
	return A.H < B.H;
}
int Tree[MAX];
inline int Lowbit( int x )
{
	return x & (-x);
}
int N;
void Add( int pos, int num )
{
	while ( pos <= N )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}
int Query( int pos )
{
	int sum = 0;
	//注意这里，不能为零，否则死循环
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
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
	int T, idx, n, m;
	scanf("%d", &T);
	for ( idx = 1; idx <= T; ++idx )
	{
		scanf("%d %d", &n, &m);
		CLR( Tree, 0 );
		N = n;
		for ( int i = 0; i < n; ++i )
		{
			scanf("%d", &data[i].num);
			data[i].idx = i + 1;
		}
		sort( data, data + n, fuck );
		for ( int i = 0; i < m; ++i )
		{
			scanf("%d %d %d", &query[i].L, &query[i].R, &query[i].H);
			query[i].idx = i + 1;
		}
		sort( query, query + m, fuck2 );
		int p_data = 0, p_query = 0;
		while ( p_query < m )
		{
			while ( p_data < n && data[p_data].num <= query[p_query].H )
			{
				Add(data[p_data].idx, 1);
				p_data++;
			}
			res[query[p_query].idx] = Query( query[p_query].R + 1 ) - Query( query[p_query].L );
			++p_query;
		}
		printf("Case %d:\n", idx);
		for ( int i = 1; i <= m; ++i )
			printf("%d\n", res[i]);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
