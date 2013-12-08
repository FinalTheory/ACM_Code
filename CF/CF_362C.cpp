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
#define MAX 5010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int Tree[MAX], nums[MAX];
int dp[MAX][MAX];
inline int Lowbit( int x )
{
	return x & (-x);
}
int n;
void Add( int pos, int num )
{
	while ( pos <= n )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}
int Query( int pos )
{
	int sum = 0;
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
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
	while ( scanf("%d", &n) != EOF )
	{
		CLR(Tree, 0);
		int res = 0;
		for ( int i = 1; i <= n; ++i )
			{scanf("%d", &nums[i]); nums[i]++;}
		for ( int i = 1; i <= n; ++i )
		{
			Add(nums[i], 1);
			for ( int j = 1; j <= n; ++j )
				dp[i][j] = Query(nums[j] - 1);
			res += i - Query(nums[i]);
		}
//		for ( int i = 1; i <= n; ++i )
//		{
//			for ( int j = 1; j <= n; ++j )
//				printf("%d ", dp[i][j]);
//			puts("");
//		}
		int _max = -1, cnt = 0;
		for ( int i = 1; i <= n; ++i )
			for ( int j = i + 1; j <= n; ++j )
			{
				int tn=j-i-1;
                int si=dp[j][i]-dp[i][i];
                int bi=tn-si;
                int sj=dp[j][j]-dp[i][j];
                int bj=tn-sj;
                int tmp=si-bi+bj-sj-1;
				if ( tmp > _max )
				{
					cnt = 1;
					_max = tmp;
				}
				else if ( tmp == _max )
				{
					cnt++;
				}
			}
		printf("%d %d\n", res - _max, cnt);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

