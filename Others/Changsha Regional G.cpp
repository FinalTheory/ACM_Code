/**
 * @file Changsha Regional G.cpp
 * @brief   本来是个数论，结果直接枚举卡着时间过了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-29
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
#define MAX 80000

#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
bool prime[MAX+10];

int X;
vector<int> P;

int try_ans( int cur, int _min, int flag )
{
	int ret = 0;
	int end = cur >> 1;
	if ( !flag )
		for ( int i = _min; P[i] <= end; ++i )
			if ( prime[cur - P[i]] ) ret++;
	end = sqrt( cur + 0.5 );
	for ( int i = flag ? _min : 0; P[i] <= end; ++i )
		if ( !(cur % P[i]) && prime[cur/P[i]] )
			ret++;
	return ret;
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
	P.clear();
	CLR(prime, 1);
	prime[0] = prime[1] = 0;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			P.push_back(i);
	while ( scanf("%d", &X) != EOF )
	{
		int XX = X / 2;
		long long sum = prime[X] ? 1 : 0;
		for ( int i = 0; P[i] <= X; ++i )
		{
			int c = X - P[i];
			if ( prime[c] && P[i] <= XX ) sum++;
			sum += try_ans( c, i, 0 );
		}
		XX = sqrt( X + 0.5 );
		for ( int i = 0; P[i] <= XX; ++i )
		{
			if ( X % P[i] ) continue;
			if ( prime[X / P[i]] ) sum++;
			sum += try_ans( X / P[i], i, 1 );
		}
		printf("%lld\n", sum % MOD);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
