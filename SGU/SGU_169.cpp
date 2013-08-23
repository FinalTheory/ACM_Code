/**
 * @file SGU_169.cpp
 * @brief   先是打表找规律，然后发现前面全为1末尾为1~9的情况才符合。简单枚举一下就行了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-14
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
inline bool check( int num )
{
	char str[50];
	sprintf(str, "%d", num);
	int sum = 1;
	for ( int i = 0; i < strlen(str); ++i )
		sum *= str[i] - '0';
	if ( sum != 0 && num % sum == 0 )
		return true;
	else
		return false;
}

bool can_divide( int len, int num )
{
	int sum = 0;
	for ( int i = 0; i < len - 1; ++i )
	{
		sum *= 10;
		sum += 1;
		sum %= num;
	}
	sum *= 10; sum += num;
	if ( sum % num == 0 )
		return true;
	else
		return false;
};
bool res[10];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int K;
	while ( scanf("%d", &K) != EOF )
	{
		CLR(res, 0);
		for ( char c = '1'; c <= '9'; ++c )
			if ( can_divide( K, c - '0' ) )
				res[c - '0'] = true;
		int ans = 0;
		for ( int i = 1; i < 9; ++i )
			if ( res[i] && res[i+1] )
				ans++;
		printf("%d\n", ans);
	}

// 	for ( int i = 1; i <= MAX; ++i )
// 	{
// 		if ( check(i) )
// 			flag[i] = true;
// 	}
// 	for ( int i = 1; i <= MAX; ++i )
// 		if ( flag[i] && flag[i+1] )
// 			printf("%d\n", i);
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
