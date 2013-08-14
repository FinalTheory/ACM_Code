/**
 * @file CF_288C.cpp
 * @brief   贪心问题，从大到小每次选取最优的情况即可。位运算不好写。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-14
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
#define MAX 1000010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int NF = 0x3f3f3f3f;

inline bool check( unsigned n, int index )
{
	return ( n >> index ) && 1;
}
bool _hash[MAX];
int res[MAX];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n;
	while ( scanf("%d", &n) != EOF )
	{
		CLR(_hash, 0);
		int j, max_pos;
		long long sum = 0;
		for ( j = 0; j <= 31; ++j )
			if ( (n >> j) && 1 )
				max_pos = j;
		for ( int num = n; num > 0; num-- )
		{
			unsigned expected = num, _mask = 0xffffffff;;
			_mask <<= ( max_pos + 1 );
			_mask = ~_mask;
			expected = ~expected;
			expected &= _mask;
			int high = max_pos;
			while (true)
			{
				if ( expected <= n && !_hash[expected] ) {
					res[num] = expected;
					sum += num ^ expected;
					_hash[expected] = true;
					break;
				}
				else {
					expected &= (~( 1 << high ));
					high--;
				}
			}
		}
		for ( int i = 0; i <= n; ++i )
			if ( !_hash[i] ) {
				sum += i ^ 0;
				res[0] = i;
				break;
			}
		printf("%lld\n%d", sum, res[0]);
		for ( int i = 1; i <= n; ++i )
			printf(" %d", res[i]);
		puts("");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
