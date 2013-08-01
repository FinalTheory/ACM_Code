/**
 * @file B.cpp
 * @brief   数论问题，求10个数的乘积的因子个数的最右位。
 * 做法是显然的，求出各个质因子的质数，加一之后全都相乘就是因子个数。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-31
 */
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define MAX 10010
using namespace std;
bool prime[MAX+10];
int yinzi[MAX+10];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int num, ans;
	vector<int> prime_num;
	memset( prime, 1, sizeof(prime) );
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	for ( int i = 2; i < MAX; ++i )
		if ( prime[i] ) prime_num.push_back(i);
	for ( int j = 1; j <= MAX; ++j )
		yinzi[j] = 1;
	for ( int i = 0; i < 10; ++i )
	{
		cin >> num;
		for ( int j = 0; j < prime_num.size(); ++j )
		{
			if ( !(num % prime_num[j]) )
				while ( !(num % prime_num[j]) )
				{
					num /= prime_num[j];
					yinzi[prime_num[j]]++;
				}
		}
		ans = 1;
	}
	for ( int j = 1; j <= MAX; ++j )
	{
		ans *= yinzi[j];
		ans %= 10;
	}
	cout << ans << endl;

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
