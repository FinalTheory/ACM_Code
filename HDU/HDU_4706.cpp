/**
 * @file HDU_4706.cpp
 * @brief   水题拼手速。
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
char _map[20][20];
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	char ch = 'a';
	for ( int size = 3; size <= 10; ++size )
	{
		CLR(_map, ' ');
		for ( int i = 0; i < size; ++i )
		{
			_map[i][0] = ch++;
			_map[i][size] = 0;
			if ( ch > 'z' ) ch = 'a';
		}
		for ( int i = 1; i < size - 1; ++i )
		{
			_map[size - 1 - i][i] = ch++;
			if ( ch > 'z' ) ch = 'a';
		}
		for ( int i = 0; i < size; ++i )
		{
			_map[i][size - 1] = ch++;
			if ( ch > 'z' ) ch = 'a';
		}
		for ( int i = 0; i < size; ++i )
			printf("%s\n", _map[i]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
