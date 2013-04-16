/*
	注意这道题，如果输入数据全是负数的话，最大子列和应该只加一个最大的负数，而不是不加。
*/
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
	int t, n, data[100002], i, j, sum, sum_max, start, start_max, end_max;
	//freopen("123.txt", "r", stdin);
	cin >> t;
	for ( j = 1; j <= t; j++ )
	{
		memset(data, 0, sizeof(data));
		sum = end_max = start_max = 0;
		start = 1;
		sum_max = -65535;
		cin >> n;
		for ( i = 1; i <= n; i++ )
			cin >> data[i];
		for ( i = 1; i <= n; i++ )
		{
			sum += data[i];
			if ( sum > sum_max )
			{
				sum_max = sum;
				start_max = start;
				end_max = i;
			}
			if ( sum < 0 )
			{
				sum = 0;
				start = i + 1;
			}
		}
		cout << "Case " << j << ":\n" << sum_max << ' ' << start_max << ' ' << end_max << '\n';
		if ( j < t )
			cout << '\n';
	}
}