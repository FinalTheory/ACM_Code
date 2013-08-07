/**
 * @file POJ_1050.cpp
 * @brief  最优子矩阵模版，与最长子列和的原理实际上是一样的。复杂度O(n^3) 
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-01
 */
#define MAX 100
#define MIN -100000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int num[MAX+10][MAX+10], sum[MAX+10][MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
	int N;
	while ( cin >> N )
	{
		CLR( sum, 0 );
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= N; ++j )
			{
				cin >> num[i][j];
				sum[i][j] = sum[i-1][j] + num[i][j];
			}
		int max_value = MIN, sum_value;
		for ( int i = 1; i <= N; ++i )
			for ( int j = i; j <= N; ++j )
			{
				sum_value = 0;
				for ( int k = 1; k <= N; ++k )
				{
					int value = sum[j][k] - sum[i - 1][k];
					sum_value = max( 0, sum_value + value );
					if ( sum_value > max_value )
						max_value = sum_value;
				}
			}
		cout << max_value << endl;
	}
}
