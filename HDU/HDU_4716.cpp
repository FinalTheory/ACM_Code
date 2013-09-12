/**
 * @file HDU_4716.cpp
 * @brief   水题练手速。
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, N, idx;
	scanf("%d", &T);
	for ( idx = 1; idx <= T; ++idx )
	{
		scanf("%d", &N);
		N /= 10;
		printf("Case #%d:\n", idx);
		puts("*------------*");
		for ( int i = 1; i <= (10 - N); ++i )
			puts("|............|");
		for ( int i = 1; i <= N; ++i )
			puts("|------------|");
		puts("*------------*");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
