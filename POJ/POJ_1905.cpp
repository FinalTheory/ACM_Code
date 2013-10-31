/**
 * @file POJ_1905.cpp
 * @brief   推出公式之后就是二分求解单调函数了，但是注意这里是如何判断的！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-28
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
const double pi = acos(-1.);
const double eps = 1e-8;

double L, LL, n, C;
double calc( double val )
{
	return L * val - LL * sin(val);
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%lf %lf %lf", &L, &n, &C) != EOF )
	{
		LL = L * ( 1. + n * C );
		if ( L < 0 && n < 0 && C < 0 ) break;
		if ( fabs(L) < eps || fabs(n) < eps || fabs(C) < eps )
		{
			puts("0.000");
			continue;
		}
		double low = eps, high = pi, mid, tmp;
		while ( true )
		{
			mid = ( low + high ) / 2.;
			tmp = sin(mid);
			if ( fabs(L * mid - LL * tmp) < eps ) break;
			if ( L * mid > LL * tmp )
				high = mid;
			else
				low = mid;
		}
		printf( "%.3lf\n", LL * (1-cos(mid)) / (2 * mid) );
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
