/*
	编辑距离，没什么可说的，1A无压力。
	还把字符串长度直接给了，无语ing……
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
#define MAX 1010
#define MIN(x, y) (x) < (y) ? (x) : (y)

using namespace std;

int DP[MAX][MAX];

int EditDistance( char * s, char * t, int len1, int len2 )
{
	int i, j, tmp;
	//int len1 = strlen(s), len2 = strlen(t);
	--s, --t;	//重新对齐
	for ( i = 0; i < MAX; ++i )
		DP[i][0] = DP[0][i] = i;
	for ( i = 1; i <= len1; ++i )
		for ( j = 1; j <= len2; ++j )
		{
			tmp = DP[i-1][j-1] + ( ( s[i] == t[j] ) ? 0 : 1 );
			if ( DP[i-1][j] + 1 < tmp )	//删除
				tmp = DP[i-1][j] + 1;
			if ( DP[i][j-1] + 1 < tmp )	//插入
				tmp = DP[i][j-1] + 1;
			DP[i][j] = tmp;
		}
		return DP[i-1][j-1];
}

int main()
{
	std::ios::sync_with_stdio(false);
	char str1[MAX], str2[MAX];
	int len1, len2;
	while ( cin >> len1 >> str1 )
	{
		cin >> len2 >> str2;
		cout << EditDistance( str1, str2, len1, len2 ) << '\n';
	}
}