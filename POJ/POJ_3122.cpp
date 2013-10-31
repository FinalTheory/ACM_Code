/**
 * @file POJ_3122.cpp
 * @brief   二分思想，枚举范围内的体积，检查能切出多少块即可。
 * @feeling 精度卡得不严格，1A甚爽！
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
#define MAX 10010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
const double pi = acos(-1.);
const double eps = 1e-7;
int r[MAX];
int N, F;;
inline bool check( double val )
{
	int res = 0;
	for( int i = 0; i < N; ++i )
	{
		int num = ( r[i] * r[i] * pi ) / val;
		res += num;
	}
	if ( res >= F )
		return true;
	else
		return false;
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
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &N, &F); F++;
		int _max = 0;
		for ( int i = 0; i < N; ++i )
		{
			scanf("%d", &r[i]);
			if ( r[i] > _max ) _max = r[i];
		}
		double low = 0., high = pi * _max * _max, mid;
		while ( high - low > eps )
		{
			mid = ( low + high ) / 2.;
			if ( check(mid) )
				low = mid;
			else
				high = mid;
		}
		printf("%.4lf\n", mid);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

