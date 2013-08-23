/**
 * @file A.cpp
 * @brief   树状数组求逆序对数
 * @hint    模版题，注意数据溢出
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
#define MAX 65557
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int Tree[MAX];
int nums[MAX], nums_s[MAX];
int N;
inline int Lowbit( int x )
{
	return x & (-x);
}
int Query( int pos )
{
	int sum = 0;
	//注意这里，不能为零，否则死循环
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
}
void Add( int pos, int num )
{
	while ( pos <= N )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}
int Search( int key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( key < nums[mid] )
			high = mid - 1;
		else if ( key > nums[mid] )
			low = mid + 1;
		else
			return mid;
	}
	return -1;
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
	
	while ( scanf("%d", &N) != EOF )
	{
		CLR( Tree, 0 );
		for ( int i = 1; i <= N; ++i )
			scanf("%d", &nums[i]);
		memcpy(nums_s, nums, sizeof(nums));
		sort( nums + 1, nums + N + 1 );
		long long sum = 0;
		for ( int i = 1; i <= N; ++i )
		{
			int pos = Search( nums_s[i], 1, N );
			sum += Query( N ) - Query( pos );
			Add( pos, 1 );
		}
		printf("%lld\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
