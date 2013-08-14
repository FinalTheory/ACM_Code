/**
 * @file CF_239B.cpp
 * @brief   模拟水题，注意边界处理。
 * 一开始装逼用string来写，但是不知道为什么迭代器用着会出错，迫不得已改用数组模拟了一遍。
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
#define MAX 110
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
bool removed[MAX];
int res[10];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, q, l, r, CP, DP, prev;
	char str[MAX], command[MAX];
	while ( scanf("%d %d", &n, &q) != EOF )
	{
		scanf("%s", str);
		for ( int k = 0; k < q; ++k )
		{
			CLR( res, 0 ); CLR( removed, 0 );
			scanf("%d %d", &l, &r);
			int j = 1;
			for ( int i = l - 1; i < r; ++i, ++j )
				command[j] = str[i];
			command[j] = 0;
			int len = r - l + 1;
			CP = DP = 1; prev = -1;
			while ( true )
			{
				if ( command[CP] >= '0' && command[CP] <= '9' ) {
					res[command[CP] - '0']++;
					prev = CP;
					if (!DP ) {
						do 
						{
							CP--;
						} while (removed[CP]);
					}
					else {
						do 
						{
							CP++;
						} while (removed[CP]);
					}
					if ( CP < 1 || CP > len ) break;
					if ( command[prev] > '0' ) {
						command[prev]--;
					}
					else {
						removed[prev] = true;
					}
				} else {
					if ( command[CP] == '<' )
						DP = 0;
					else
						DP = 1;
					if ( prev != -1 && (command[prev] == '<' || command[prev] == '>') )
						removed[prev] = true;
					prev = CP;
					if (!DP ) {
						do 
						{
							CP--;
						} while (removed[CP]);
					}
					else {
						do 
						{
							CP++;
						} while (removed[CP]);
					}
					if ( CP < 1 || CP > len ) break;
				}
			}
			printf("%d", res[0]);
			for ( int i = 1; i < 10; ++i )
				printf(" %d", res[i]);
			puts("");
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
