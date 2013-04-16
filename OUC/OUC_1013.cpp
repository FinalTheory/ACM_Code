/*
	���͵�01�������⡣����Ŀ����װ�����ҡ���ֵ��С����
	WA�����Σ������Լ�������һ���������ݡ�
	����ע���ʼ����ʱ��ע�ⷶΧ�����ڱ����˱�����������Ҫ�����µ������㡣
	����INT_MAX - 1000�Ա��������
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