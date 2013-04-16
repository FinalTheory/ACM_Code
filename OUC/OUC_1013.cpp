/*
	典型的01背包问题。但是目的是装满并且“价值最小”。
	WA了两次，所以自己构造了一个极限数据。
	另外注意初始化的时候注意范围，由于倍增了背包容量所以要按照新的容量算。
	并且INT_MAX - 1000以避免溢出。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
unsigned dp[500500], c[1005], T, M, N, mini;
void DP( int m )
{
	int i, v;
	dp[0] = 0;
	for ( i = 1; i <= m; i++ )
		dp[i] = INT_MAX - 1000;
	for ( i = 1; i <= N; i++ )
		for ( v = m; v >= c[i]; v-- )
			dp[v] = MIN( dp[v-c[i]] + 1, dp[v] );
	if ( dp[m] < mini )
		mini = dp[m];
}
int main()
{
	//freopen( "in.txt", "r", stdin );
	unsigned long long i, sum;
	cin >> T;
	while ( T-- )
	{
		sum = 0;
		cin >> M >> N;
		for ( i = 1; i <= N; i++ )
		{
			cin >> c[i];
			sum += c[i];
		}
		mini = 2000;
		sort(c + 1, c + N + 1);
		for ( i = M; i <= sum && mini == 2000; i += M )
			DP(i);
		if ( mini == 2000 )
			cout << "-1" << endl;
		else
			cout << mini << endl;
	}
}