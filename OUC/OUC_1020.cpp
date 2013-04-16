/*
	由于一共就只有1、2、3，所以排序完就是三段。
	把每一段与其他段重合的部分减掉，剩下的需要交换两次。
	数据规模很大，10W，结果WA了N多次，坑爹啊……
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
int n[4], f[4][4];
int nums[100010];
int main()
{
	freopen( "in.txt", "r", stdin );
	int N, i, j, sum;
	while (cin >> N)
	{
		sum = 0;
		memset(n, 0, sizeof(n));
		memset(f, 0, sizeof(f));
		for ( i = 0; i < N; i++ )
		{
			cin >> nums[i];
			n[nums[i]]++;
		}
		for ( i = 0; i < n[1]; i++ )
			f[1][nums[i]]++;
		for ( i = n[1]; i < n[1] + n[2]; i++ )
			f[2][nums[i]]++;
		for ( i = n[1] + n[2]; i < n[1] + n[2] + n[3]; i++ )
			f[3][nums[i]]++;
		for ( i = 1; i <= 3; i++ )
			for ( j = 1; j <= 3; j++ )
				if ( i != j )
				{
					int t = MIN( f[i][j], f[j][i] );
					sum += t;
					f[i][j] -= t;
					f[j][i] -= t;
				}
		sum += ( f[1][2] + f[1][3] ) * 2;
		cout << sum << endl;
	}
}