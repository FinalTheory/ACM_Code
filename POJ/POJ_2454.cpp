/**
 * @file POJ_2454.cpp
 * @brief   还是随机化乱搞
 * @hint    题意有点绕，是要求将3*K个数分为三组，其中两组的和要大于K*500。
 *	    由于数据规模太小，可以考虑随机化方法。
 *	    首先贪心一下，把最小的K个扔出去，显然放弃这一组。
 *	    然后对另外两组，随机交换一个值并检查，如果可行，直接输出，否则一直循环。
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
const int INF = 0x3f3f3f3f;
struct TMD
{
	int idx;
	int num;
} cities[200];
bool fuck( const TMD & A, const TMD & B )
{
	return A.num < B.num;
}
int K;
inline bool check()
{
	int sum1 = 0, sum2 = 0, sum = K * 500;
	for ( int i = K; i < K * 2; ++i )
		sum1 += cities[i].num;
	for ( int i = 2 * K; i < K * 3; ++i )
		sum2 += cities[i].num;
	if ( sum1 > sum && sum2 > sum )
		return true;
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
	srand(time(NULL));
	while ( scanf("%d", &K) != EOF )
	{
		for ( int i = 0; i < 3 * K; ++i )
		{
			scanf("%d", &cities[i].num);
			cities[i].idx = i + 1;
		}
		sort( cities, cities + 3 * K, fuck );
		for ( int i = 0; i < K; ++i )
			printf("%d\n", cities[i].idx);
		while (1)
		{
			if ( check() ) break;
			int a = rand() % K;
			int b = rand() % K;
			swap( cities[K + a], cities[2 * K + b] );
		}
		for ( int i = K; i < 3 * K; ++i )
			printf("%d\n", cities[i].idx);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

