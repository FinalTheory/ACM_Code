/**
 * @file HDU_4296.cpp
 * @brief   贪心问题
 *只要对自身重量与承载能力之和做排序即可。
 *利用对换法证明贪心策略的正确性。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-03-31
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	long long a, b;
} data[100010];

long long sum[100010];

bool fuck( TMD & a, TMD & b )
{
	return a.a + a.b < b.a + b.b;
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
	long long max;
	while ( cin >> n && n )
	{
		memset( sum, 0, sizeof(sum) );
		memset( data, 0, sizeof(data) );
		for ( i = 0; i < n; ++i )
			cin >> data[i].a >> data[i].b;
		sort( data, data + n, fuck );
		//千万要注意这里！当都能承载的时候是要输出零的！！！不要画蛇添足把这里设成负数！
		max = 0;
		sum[0] = data[0].a;
		for ( i = 1; i < n; ++i )
		{
			if ( sum[i-1] - data[i].b > max )
				max = sum[i-1] - data[i].b;
			sum[i] = sum[i-1] + data[i].a;
		}
		cout << max << endl;

	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
