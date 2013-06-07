/**
 * @file FZU_2107.cpp
 * @brief   搜索问题，很简单的，但是组队赛太困了没做出来，直接枚举所有空位置就行了。
 * 剪枝都不用，因为可行局面太少了。但是注意如果被放了之后的DFS顺序！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-03
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int map[10][10];
int sum, N;
struct point
{
	int row, col;
} empty[12];

void put_cao( int i, int j )
{
	map[i][j] = map[i+1][j] = map[i][j+1] = map[i+1][j+1] = 4;
}

bool check()
{
	int i, j;
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < 4; ++j ) if ( !map[i][j] )
				return false;
	return true;
}

bool ava( int i, int j )
{
	if ( i >= 0 && i < N && j >= 0 && j < 4 )
		return true;
	return false;
}

void DFS( int n )
{
	if ( n ==  N * 4 - 4 )
	{
		if ( check() )
			sum++;
		return;
	}
	int row, col;
	row = empty[n].row;
	col = empty[n].col;
	
	if ( map[row][col] )
	{
		//如果这里已经被放了，仍然要继续DFS
		DFS( n + 1 );
		return;
	}

	//放一个战士
	if ( !map[row][col] )
	{
		map[row][col] = 1;
		DFS( n + 1 );
		map[row][col] = 0;
	}
	if ( !map[row][col] && ava( row + 1, col ) && !map[row + 1][col] )
	{
		map[row][col] = map[row + 1][col] = 2;
		DFS( n + 1 );
		map[row][col] = map[row + 1][col] = 0;
	}
	if ( !map[row][col] && ava( row - 1, col ) && !map[row - 1][col] )
	{
		map[row][col] = map[row - 1][col] = 2;
		DFS( n + 1 );
		map[row][col] = map[row - 1][col] = 0;
	}
	if ( !map[row][col] && ava( row, col + 1 ) && !map[row][col + 1] )
	{
		map[row][col] = map[row][col + 1] = 3;
		DFS( n + 1 );
		map[row][col] = map[row][col + 1] = 0;
	}
	if ( !map[row][col] && ava( row, col - 1 ) && !map[row][col - 1] )
	{
		map[row][col] = map[row][col - 1] = 3;
		DFS( n + 1 );
		map[row][col] = map[row][col - 1] = 0;
	}
	
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
	int i, j, ii, jj, k, T;
	cin >> T;
	while ( T-- )
	{
		cin >> N;
		if ( N < 2 )
		{
			puts("0");
			continue;
		}
		sum = 0;
		for ( i = 0; i < N - 1; ++i )
			for ( j = 0; j < 3; ++j )
			{
				CLR( map, 0 );
				put_cao( i, j );
				k = 0;
				for ( ii = 0; ii < N; ++ii )
					for ( jj = 0; jj < 4; ++jj ) if ( !map[ii][jj] )
					{
						empty[k].row = ii;
						empty[k++].col = jj;
					}
					DFS( 0 );
			}
			printf("%d\n", sum);
	}
	
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
