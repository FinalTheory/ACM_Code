/**
 * @file POJ_3273.cpp
 * @brief   二分思想
 * @hint    二分的地方比较绕，具体见下面
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-27
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int nums[MAX];
int N, M;
//定义一个函数用来检查当前的最大值是否可以满足生成小于等于M个子序列。
//如果能生成的话，显然一定也能生成M个，只需要再拆分即可。
//所以这个函数是用来判断当前值是否合法的，实现的思想是贪心法。
inline bool check( int val )
{
	int sum = 0, res = 1;
	for ( int i = 1; i <= N; ++i )
		if ( sum + nums[i] <= val )
			sum += nums[i];
		else
		{
			sum = nums[i];
			res++;
		}
	if ( res <= M )
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
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		int _max = 0, sum = 0;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &nums[i]);
			sum += nums[i];
			if ( nums[i] > _max ) _max = nums[i];
		}
		//首先生成二分边界
		int low = _max, high = sum;
		while ( low < high )
		{
			int mid = ( low + high ) >> 1;
			//如果mid合法，它可能是答案，所以缩小上界但是不加一
			if ( check(mid) ) {
				high = mid;
			} else {
			    //如果不合法，说明应该增加下界，并且这个mid值不可能是答案
				low = mid + 1;
			}
		}
		printf("%d\n", low);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

