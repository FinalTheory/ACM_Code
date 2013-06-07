/**
 * @file POJ_2109.cpp
 * @brief   本来这题应该是二分+高精度乘法。
 * 但是应该是题目本身数据限制太大了，利用double的特性可以直接这样水过……
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	double n, p;
	while ( scanf("%lf %lf", &n, &p) != EOF )
	{
		printf("%.0lf\n", pow( p, 1. / n ));
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
