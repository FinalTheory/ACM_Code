/*
	精度啊，各种坑爹啊有木有，WA了四五次啊有木有！！！
	以后做题先看数据规模啊！！！
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	unsigned long long sum, n, m, s, k;
	while ( cin >> n >> m >> s )
	{
		if ( n > m )
		{
			m ^= n;
			n ^= m;
			m ^= n;
		}
		if ( s >= m )
		{
			cout << (unsigned long long)m * n << endl;
			continue;
		}
		k = ( m - ( ( m - 1 ) / s ) * s ) * ( n - ( ( n - 1 ) / s ) * s );
		sum = (( ( m - 1 ) / s + 1 ) *  ( ( n - 1 ) / s + 1 ));
		sum *= k;
		cout << sum << endl;
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}