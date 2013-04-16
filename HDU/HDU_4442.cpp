/**
 * @file HDU_4442.cpp
 * @brief   贪心问题
 * 这类求解最优顺序的问题可以用对换思想来考虑。
 * 假设两队列分别为a1,b1,a2,b2，若1队在前，总时间为：a1+a1*b2+a2;
 * 若2队在前，总时间为a2+a2*b1+a1，这样时间差为a1*b2-a2*b1，即乘积较小者优先。
 * 以此为规律对所有数据排列，便得出正确的顺序。由对换规律，这是最优解。
 * 然后递推求出时间和即可。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-03-31
 */
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX 100000
#define MOD 31536000
using namespace std;

typedef long long LL;

struct TMD
{
	LL a, b;
} data[MAX+10];

bool fuck( TMD P, TMD Q )
{
	return P.a * Q.b <= Q.a * P.b;
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
	int n, i;
	while ( cin >> n && n )
	{
		if ( n == 0 )
			break;
		for ( i = 0; i < n; ++i )
			cin >> data[i].a >> data[i].b;
		sort( data, data + n, fuck );
		LL ans = 0;
		for ( i = 0; i < n; ++i )
			ans = ( ans + data[i].a + ans * data[i].b ) % MOD;
		cout << ans << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
