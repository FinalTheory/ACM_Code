/*
	�򵥵��������������������ÿ�η���һ��block�Ϸ�����ô�͵ݹ�������Χ�����кϷ�blockΪ�Ƿ���
	���ݹ�ģ������Ҫע����ǵݹ��յ�����á�ֱ��0MS����һ��AC��
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
int m, n;
int z[8][2] = { -1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1 };
char map[105][105];
bool check( int a, int b )
{
	if ( a < 0 || b < 0 )
		return 0;
	if ( a >= m || b >= n )
		return 0;
	return 1;
}
void clear( int i, int j )
{
	if ( map[i][j] == '@' )
		map[i][j] = '*';
	else
		return;
	for ( int k = 0; k < 8; k++ )
		if ( check( i + z[k][0], j + z[k][1] ) )
			clear( i + z[k][0], j + z[k][1] );
}
int main()
{
	int i, j, sum;
	while ( cin >> m >> n && m )
	{
		sum = 0;
		for ( i = 0; i < m; i++ )
			scanf("%s", map[i]);
		for ( i = 0; i < m; i++ )
			for ( j = 0; j < n; j++ )
				if ( map[i][j] == '@' )
				{
					sum++;
					clear(i, j);
				}
		cout << sum << endl;
	}
}