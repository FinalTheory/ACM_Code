/*
	�����һ�ѣ�������������֤�ˣ�ֱ����һ����������Ƿ�Ϸ���
	����û�е���������������ʱ�����㹻�ˡ�
	�ύ�����Σ�C++û��G++�͹��ˣ����죬���ƻ������������⡣
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
using namespace std;
int ans[1000];
bool check( int N, int X )
{
	int i, j, k, Y;
	char num[20], num_new[20];
	sprintf( num, "%d", X );
	for ( i = 0; i < strlen(num); ++i )
	{
		for ( k = j = 0; num[j]; ++j )
			if ( j != i )
				num_new[k++] = num[j];
		num_new[k] = 0;
		sscanf( num_new, "%d", &Y );
		if ( X + Y == N )
			return 1;
	}
	return 0;
}

int main()
{
	//freopen( "in.txt", "r", stdin );
	int i, N, k, tmp, a, b, c1, c2, TMP, p;
	vector <int> res, res2;
	vector <int> :: iterator pointer;
	while ( scanf("%d", &N) && N )
	{
		if ( N < 10 )
		{
			printf("%d\n", N);
			continue;
		}
		res.clear(); res2.clear();
		for ( k = 1; k <= N; k *= 10 )
		{
			tmp = N / k;
			a = tmp / 11;
			b = tmp - a * 11;
			c1 = ( N - ( 11 * a + b ) * k ) / 2;
			c2 = ( N - ( 11 * a + b - 1 ) * k ) / 2;
			TMP = a * k * 10 + b * k + c1;
			if ( check( N, TMP ) )
				res.push_back(TMP);			
			TMP = a * k * 10 + ( b - 1 ) * k + c2;
			if ( check( N, TMP ) )
				res.push_back(TMP);
		}
		sort( res.begin(), res.end() );
		if ( res.empty() )
			printf("No solution.\n");
		else
		{
			memset( ans, 0, sizeof(ans) );
			ans[0] = *(res.begin());
			for ( pointer = res.begin() + 1, p = 1; pointer < res.end(); ++pointer )
			{
				if ( *pointer != ans[p - 1] )
					ans[p++] = *pointer;
			}
			for ( i = 0; i < p; ++i )
				printf( ( i == p - 1 ) ? "%d\n" : "%d ", ans[i] );
		}
	}
}