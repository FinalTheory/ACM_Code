/**
 * @file CF_235A.cpp
 * @brief   数论，水题。
 * 奇数的情况显然很好处理，连续三个一定是互质的。
 * 对于偶数的情况，随便枚举一下。
 * 注意取值范围，另外一开始gcd写错了居然还能跑到第33个case，奇葩……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
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
typedef long long LL;
int res[10] = { -1, 1, 2, 6, 12, 60, 60, 210, 280, 504 };

LL gcd( LL a, LL b )
{
	if ( b == 0 )
		return a;
	else
		return gcd( b, a % b );
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
	LL ans, n;
	while ( cin >> n )
	{
		//cout << gcd( 91LL, 60LL ) << endl;
		if ( n < 10 )
		{
			cout << res[n] << endl;
			continue;
		}
		if ( n % 2 )
			ans = n * ( n - 1 ) * ( n - 2 );
		else
			ans = max ( max(n * ( n - 1 ) * ( n - 2 ) / gcd( n, n - 2 ), n * ( n - 1 ) * ( n - 3 ) / gcd( n, n - 3 )), ( n - 1 ) * ( n - 2 ) * ( n - 3 ) ) ;
		cout << ans << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
