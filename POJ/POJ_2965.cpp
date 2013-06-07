/**
 * @file POJ_2965.cpp
 * @brief   枚举水题，用了搜索写法，速度还不错。
 * 尼玛一开始更新的时候给弄错了，半天没调出来，气死了！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-31
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[4][4];
char flags[16];
char res[16];
int sum, _min;
bool check()
{
	int i, j;
	for ( i = 0; i < 4; ++i )
		for ( j = 0; j < 4; ++j )
			if ( !map[i][j] )
				return 0;
	return 1;
}

void DFS( int n )
{

	if ( n == 16 )
	{
		if ( check() && sum < _min )
		{
			_min = sum;
			memcpy( res, flags, sizeof(res) );
		}
		return;
	}
	int row = n / 4;
	int col = n % 4;
	DFS(n+1);
	sum++;
	flags[n] = 1;
	map[row][col] ^= 1;
	for ( int i = 0; i < 4; ++i )
	{
		if ( i != col )
			map[row][i] ^= 1;
		if ( i != row )
			map[i][col] ^= 1;
	}
	DFS(n+1);
	map[row][col] ^= 1;
	for ( int i = 0; i < 4; ++i )
	{
		if ( i != col )
			map[row][i] ^= 1;
		if ( i != row )
			map[i][col] ^= 1;
	}
	sum--;
	flags[n] = 0;
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
	int i, j;
	for ( i = 0; i < 4; ++i )
		scanf("%s", map[i]);
	for ( i = 0; i < 4; ++i )
		for ( j = 0; j < 4; ++j )
		{
			if ( map[i][j] == '-' )
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
		sum = 0; _min = INF;
		CLR(flags, 0); CLR( res, 0 );
		DFS( 0 );
		printf("%d\n", _min);
		for ( i = 0; i < 16; ++i )
			if ( res[i] )
				printf("%d %d\n", i / 4 + 1, i % 4 + 1);
#ifndef ONLINE_JUDGE
		program_end = clock();
		cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
