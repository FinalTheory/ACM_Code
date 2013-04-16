/*
	同样是DFS，POJ1562的升级版。只不过判断连通性麻烦了一些。
	一次AC，RP大爆发啊……
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
int M, N;
char map[51][51];
int z[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 };
struct
{
	char up, down, left, right;
} TMD[11] = { {1,0,1,0}, {1,0,0,1}, {0,1,1,0}, {0,1,0,1}, {1,1,0,0}, {0,0,1,1}, {1,0,1,1}, {1,1,1,0}, {0,1,1,1}, {1,1,0,1}, {1,1,1,1} };
bool check( int a, int b )
{
	if ( a < 0 || b < 0 )
		return 0;
	if ( a >= M || b >= N )
		return 0;
	return 1;
}
bool check_connect( char A, char B, int k )
{
	switch( k )
	{
		case 0 : 
			return TMD[A-65].up && TMD[B-65].down;
		case 3 : 
			return TMD[A-65].down && TMD[B-65].up;
		case 1 :
			return TMD[A-65].left && TMD[B-65].right;
		case 2 :
			return TMD[A-65].right && TMD[B-65].left;
	}
}
void clear( int i, int j )
{
	int x, y;
	char c = map[i][j];
	if ( map[i][j] != '0' )
		map[i][j] = '0';
	else
		return;
	for ( int k = 0; k < 4; k++ )
	{
		x = j + z[k][1];
		y = i + z[k][0];
		if ( check( y, x ) )
			if ( check_connect(c, map[y][x], k) )
				clear(y, x);
	}
}
int main()
{
	int i, j, sum;
	while ( cin >> M >> N && M != -1 )
	{
		sum = 0;
		for ( i = 0; i < M; i++ )
			scanf("%s", map[i]);
		for ( i = 0; i < M; i++ )
			for ( j = 0; j < N; j++ )
				if ( map[i][j] != '0' )
				{
					sum++;
					clear(i, j);
				}
		cout << sum << endl;
	}
}