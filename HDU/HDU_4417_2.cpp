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
#define MAX 100010
const int INF = 0x3f3f3f3f;
int nums[MAX], sorted[MAX], root[MAX];
int cnt;
struct TMD
{
	int sum, L_son, R_son;
} Tree[MAX<<5];
inline int CreateNode( int _sum, int _L_son, int _R_son )
{
	int idx = ++cnt;
	Tree[idx].sum = _sum;
	Tree[idx].L_son = _L_son;
	Tree[idx].R_son = _R_son;
	return idx;
}
void Insert( int & root, int pre_rt, int pos, int L, int R )
{
	root = CreateNode( Tree[pre_rt].sum + 1, Tree[pre_rt].L_son, Tree[pre_rt].R_son );
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M )
		Insert( Tree[root].L_son, Tree[pre_rt].L_son, pos, L, M );
	else
		Insert( Tree[root].R_son, Tree[pre_rt].R_son, pos, M + 1, R );
}
int Query( int S, int E, int L, int R, int K )
{
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	int sum = Tree[Tree[E].L_son].sum - Tree[Tree[S].L_son].sum;
	if ( K <= sum )
		return Query( Tree[S].L_son, Tree[E].L_son, L, M, K );
	else
		return Query( Tree[S].R_son, Tree[E].R_son, M + 1, R, K - sum );
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
	int n, m, num, pos, T;
	scanf("%d", &T);
	for ( int idx = 1; idx <= T; ++idx )
	{
		scanf("%d %d", &n, &m);
		cnt = 0; root[0] = 0;
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &nums[i]);
			sorted[i] = nums[i];
		}
		sort( sorted + 1, sorted + 1 + n );
		num = unique( sorted + 1, sorted + n + 1 ) - ( sorted + 1 );
		for ( int i = 1; i <= n; ++i )
		{
			pos = lower_bound( sorted + 1, sorted + num + 1, nums[i] ) - sorted;
			Insert( root[i], root[i - 1], pos, 1, num );
		}
		int l, r, h;
		printf("Case %d:\n", idx);
		while ( m-- )
		{
			scanf("%d %d %d", &l, &r, &h);
			++l; ++r;
			if ( r == l ) {
				if ( nums[l] <= h ) puts("1");
				else puts("0");
				continue;
			}
			int low = 1, high = r - l + 1, mid, res = 0;
			while ( low <= high )
			{
				mid = ( low + high ) >> 1;
				pos = Query( root[l - 1], root[r], 1, num, mid );
				if ( sorted[pos] <= h ) {
					res = mid;
					low = mid + 1;
				} else {
					high = mid - 1;
				}
			}
			printf("%d\n", res);
		}
	}
}
