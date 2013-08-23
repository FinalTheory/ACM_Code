/**
 * @file CF_245E.cpp
 * @brief   贪心问题
 * @hint    想明白是如何统计人数的。可以假设屋中允许负数个人，这样每出去一个人就减一，进来一个就加一；
 *	    如果人能够对应的话，自然就消去了；如果不能，最后的最大值减最小值就把人数恢复了出来。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-16
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
	stack<char> stk;
	char buffer[1000];
	scanf("%s", buffer);
	int len = strlen(buffer);
	int _max = 0, _min = 0, num = 0;
	for ( int i = 0; i < len; ++i )
	{
		if ( buffer[i] == '+' )
			num++;
		else
			num--;
		_min = min( num, _min );
		_max = max( num, _max );
	}
	printf("%d\n", _max - _min);

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
