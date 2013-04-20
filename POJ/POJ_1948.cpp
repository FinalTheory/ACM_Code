/**
 * @file POJ_1948.cpp
 * @brief   DP���⣬��������״̬�Ϳ��ԣ���Ϊ�������ߵĳ��ȿ��Լ�������
 * ע�����ͽضϵ����⣬����������WA�����Σ�
 * ��ʱ�Ƚϴ꣬����ûTLE�������Ż��ˣ��������ɣ�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-18
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#define MAX 1600
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char DP[MAX+10][MAX+10], DP_new[MAX+10][MAX+10];
int segments[50];

double calc( int a, int b, int c )
{
	//������������������ͽضϿ���һ�Σ�
	double p = (double)(a + b + c) / 2;
	if ( a + b > c && b + c > a && c + a > b )
		return sqrt( p * ( p - a ) * ( p - b ) * ( p - c ) );
	else
		return -1;
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
	int N, i, j, k, sum;
	while ( cin >> N )
	{
		CLR( DP, 0 );
		CLR( DP_new, 0 );
		sum = 0;
		for ( i = 0; i < N; ++i )
		{
			cin >> segments[i];
			sum += segments[i];
		}
		DP[0][0] = 1;
		for ( k = 0; k < N; ++k )
		{
			for ( i = 0; i <= sum; ++i )
				for ( j = 0; j <= sum; ++j )
					if ( DP[i][j] )
					{
						DP_new[i+segments[k]][j] = 1;
						DP_new[i][j+segments[k]] = 1;
					}
			memcpy( DP, DP_new, sizeof(DP) );
		}
		double res, res_max = -1;
		for ( i = 1; i <= sum; ++i )
			for ( j = 1; j <= sum; ++j )
				if ( DP[i][j] )
				{
					res = calc( i, j, sum - i - j );
					if ( res > res_max )
						res_max = res;
				}
		int out = res_max * 100;
		if ( out > 0 )
			cout << out << endl;
		else
			cout << "-1" << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
