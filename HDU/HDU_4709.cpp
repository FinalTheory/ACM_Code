/**
 * @file hdu_4709.cpp
 * @brief   最水的计算几何，注意三角形面积是怎么计算的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-11
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX 110
#define eps 0.000001
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
double x[MAX], y[MAX];

inline double calc( double x0, double y0, double x1, double y1, double x2, double y2 )
{
	return fabs( x0*y1 + x1*y2 + x2*y0 - x1*y0 - x2*y1 - x0*y2 );
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
	int T, N;
	scanf("%d", &T);
	while ( T-- )
	{
		double area = INF;
		scanf("%d", &N);
		for ( int i = 1; i <= N; ++i )
			scanf("%lf %lf", &x[i], &y[i]);
		for ( int i = 1; i <= N; ++i )
			for ( int j = i + 1; j <= N; ++j )
				for ( int k = j + 1; k <= N; ++k )
				{
					double tmp = calc( x[i], y[i], x[j], y[j], x[k], y[k] );
					if ( tmp > eps && tmp < area )
						area = tmp;
				}
		if ( area < INF )
			printf("%.2lf\n", area / 2.);
		else
			puts("Impossible");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
