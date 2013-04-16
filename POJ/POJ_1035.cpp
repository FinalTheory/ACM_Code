/*
	坑爹的题，本来还以为是编辑距离，结果TLE了几次之后发现原来简单做一下判断就行。
	写函数的时候注意是否能有返回值，嵌套多了编译器检查不出来不会报错的！
	另外多写的编辑距离还得扔到另外一道题上。
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
#define MAX 20

using namespace std;

int DP[MAX][MAX];
char dict[10010][18];
int dictlen[10010];

int EditDistance( char * s, char * t )
{
	int i, j, tmp;
	int len1 = strlen(s), len2 = strlen(t);
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

bool check( char * s, char * t, int len1, int len2 )
{
	int i, j, sum;
	char jumped;
	if ( len1 == len2 )
	{
		sum = 0;
		for ( i = 0; i < len1; ++i )
			if ( s[i] != t[i] )
				++sum;
		if ( sum > 1 )
			return 0;
		else
			return 1;
	}
	if ( len1 > len2 )
	{
		jumped = 0;
		i = j = 0;
		while ( s[i] != 0 && t[j] != 0 )
		{
			if ( s[i] != t[j] )
			{
				if ( jumped )
					return 0;
				else
				{
					++i;
					jumped = 1;
					continue;
				}
			}
			++i, ++j;
		}
		return 1;
	}
	else
	{
		return check( t, s, len2, len1 );
	}
}


int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int k = 0, i, wordlen;
	char word[20], found;
	while ( 1 )
	{
		scanf("%s", dict[k]);
		dictlen[k] = strlen(dict[k]);
		if ( dict[k][0] == '#' )
			break;
		++k;
	}
	while ( 1 )
	{
		scanf("%s", word);
		wordlen = strlen(word);
		if ( word[0] == '#' )
			break;
		found = 0;
		for ( i = 0; i < k; ++i )
		{
			if ( wordlen != dictlen[i] )
				continue;
			if ( !strcmp( word, dict[i] ) )
			{
				printf( "%s is correct\n", word );
				found = 1;
				break;
			}
		}
		if ( !found )
		{
			printf( "%s:", word);
			for ( i = 0; i < k; ++i )
			{
				if ( wordlen - dictlen[i] > 1 || wordlen - dictlen[i] < -1 )
					continue;
				if ( check( word, dict[i], wordlen, dictlen[i] ) )
					printf(" %s", dict[i]);
			}
			printf("\n");
		}
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}