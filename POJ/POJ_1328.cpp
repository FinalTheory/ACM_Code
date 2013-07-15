/**
 * @file POJ_1328.cpp
 * @brief   贪心问题，每个点可以允许的雷达位置构成一个区间，从左到右寻找区间重叠就可以了。
 * 这题如果扩大规模的话，可能需要上线段树离散化插入区间。
 * 思路很清晰，但是一开始一直WA，各种郁闷人啊。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-01
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
#define INF 0x3f3f3f3f
#define eps 10e-7
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	int x, y;
	double left, right;
} points[1010];

bool fuck( TMD A, TMD B )
{
	return ( A.left - B.left ) < eps;
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
	int n, d, i, index = 1;
	double pos;
	char fail;
	int sum;
	while ( scanf("%d %d", &n, &d) != EOF && (n != 0 || d != 0) )
	{
		fail = 0; sum = 1;
		for ( i = 0; i < n; ++i )
		{
			scanf( "%d %d", &points[i].x, &points[i].y );
			if ( !fail && points[i].y <= d )
			{
				double tmp = sqrt( (double)d * d - points[i].y * points[i].y );
				points[i].left = points[i].x - tmp;
				points[i].right = points[i].x + tmp;
			}
			else
				fail = 1;
		}
		if ( fail )
		{
			printf("Case %d: -1\n", index++ );
			continue;
		}
		sort( points, points + n, fuck );
		pos = points[0].right;
		for ( i = 1; i < n; ++i )
		{
			if ( points[i].left - pos > eps )
			{
				++sum;
				pos = points[i].right;
			}
			else
			{
				if ( points[i].right - pos < eps )
					pos = points[i].right;
			}
		}
		printf("Case %d: %d\n", index++, sum );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

