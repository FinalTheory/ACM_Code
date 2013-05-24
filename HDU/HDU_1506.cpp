/**
 * @file HDU_1506.cpp
 * @brief   DP问题，通过迭代快速确定每个高度的有效左右边界。
 * 扒的别人思路，惭愧了……不知道为什么TLE了一次，然后精度问题WA了一次，这尼玛……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-22
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
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

long long h[MAX], l[MAX], r[MAX];

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	long long max;
	int n, i;
	while ( scanf("%d", &n) && n )
	{
		max = 0;
		h[0] = h[n+1] = -1;
		for ( i = 1; i <= n; ++i )
		{
			l[i] = r[i] = i;
			scanf("%I64d", &h[i]);
		}
		for ( i = 1; i < n; ++i )
			while ( h[l[i] - 1] >= h[i] )
				l[i] = l[l[i] - 1];
		for ( i = n; i >= 1; --i )
			while ( h[r[i] + 1] >= h[i] )
				r[i] = r[r[i] + 1];
		for ( i = 1; i <= n; ++i )
		{
			long long area = ( r[i] - l[i] + 1 ) * h[i];
			if ( area > max ) max = area;
		}
		printf("%I64d\n", max);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
