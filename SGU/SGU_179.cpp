/**
 * @file SGU_179.cpp
 * @brief   构造匹配括号序列的下一个排列，一开始用暴力跪了一发。
 * 从右到左找满足条件的可以更换的括号位置，然后将其改为右括号，将下一个改为左括号。
 * 用一个小Trick就是对后面的部分直接排序即可，保证了结果肯定会是正确的序列。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
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

stack<char> S;

bool check( char * str )
{
	while ( !S.empty() ) S.pop();
	for ( int i = 0; i < strlen(str); ++i )
	{
		
	}
	if ( S.size() == 0 )
		return true;
	else
		return false;
}
char buffer[10010];
int sum_left[10010];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%s", buffer + 1) != EOF )
	{
		int left_all = 0, left;
		int len = strlen(buffer + 1);
		for ( int i = 1; i <= len; ++i )
		{
			sum_left[i] = sum_left[i - 1];
			if ( buffer[i] == '(' )
				sum_left[i]++;
		}
		char found = false;
		for ( int i = len; i >= 1; --i ) if ( buffer[i] == '(' && 2 * sum_left[i] - i >= 2 )
		{
			found = true;
			buffer[i] = ')';
			buffer[i+1] = '(';
			sort( buffer + i + 1, buffer + len + 1 );
			break;
		}
		if ( found )
			puts(buffer+1);
		else
			puts("No solution");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
