/*
	��׼��DP���⣬״̬ת�Ʒ����ԣ��ð��ҳ�����֮ǰ�ȿ��˱��˵Ĵ��롣
	������۶��������ַ�����ʱ��Ҫ��gets����scanf��WA����Ϊscanf�������У�
	���ǲ�����������ò���п��У����ʱ��Ӧ������㡣
	ֱ��д�ɺ�����ʽ�ˣ�ʡ���Ժ�Ҫ�á�
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define BIG 1100
using namespace std;
int dp[BIG][BIG]; 
int LCS( char * str1, char * str2 )
{
	int len1, len2, len, i, j;
	len1 = strlen(str1);
	len2 = strlen(str2);
	len = ( len1 > len2 ) ? len1 : len2;
	for ( i = 0; i <= len; i++ )
		dp[i][0] = dp[0][i] = 0;
	for ( i = 1; i <= len1; i++ )
		for ( j = 1; j <= len2; j++ )
		{
			if ( str1[i-1] == str2[j-1] )
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = MAX( dp[i][j-1], dp[i-1][j] );
		}
	return dp[len1][len2];
}
int main()
{
	//freopen( "in.txt", "r", stdin );
	char str1[BIG], str2[BIG];
	while( gets(str1), gets(str2) )
		cout << LCS(str1, str2) << endl;
}