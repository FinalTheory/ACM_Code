/*
	标准的DP问题，状态转移方程略，好吧我承认做之前先看了别人的代码。
	这道蛋疼东西输入字符串的时候要用gets，用scanf会WA，因为scanf不读空行，
	但是测试数据里面貌似有空行，这个时候应该输出零。
	直接写成函数形式了，省的以后还要用。
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