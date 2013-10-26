/**
 * @file CF_358A.cpp
 * @brief   思路题，直接求出圆心位置，枚举判断圆是否相交即可。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-26
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
const double eps = 1e-10;
struct TMD
{
	double mid;
	double l;
};
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n;
	double x[1010];
	vector<TMD> mid;
	TMD tmp;
	scanf("%d", &n);
	for ( int i = 0; i < n; ++i )
		scanf("%lf", &x[i]);
	if ( n == 1 ) {
		puts("no");
		exit(0);
	}
	for ( int i = 1; i < n; ++i ) {
			tmp.mid = (x[i - 1] + x[i]) / 2.;
			tmp.l = fabs( x[i - 1] - x[i] ) / 2.;
			mid.push_back(tmp);
	}
	bool found = false;
	for ( unsigned i = 0; i < mid.size(); ++i )
		for ( unsigned j = i + 1; j < mid.size(); ++j )
		{
			if ( fabs(mid[i].mid - mid[j].mid) < mid[i].l + mid[j].l && fabs(mid[i].mid - mid[j].mid) > fabs(mid[i].l - mid[j].l) )
			{
				found = true;
				break;
			}
		}
	if ( found )
		puts("yes");
	else
		puts("no");
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

