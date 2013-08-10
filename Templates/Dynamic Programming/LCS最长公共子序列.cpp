/**
 * @file LCS最长公共子序列.cpp
 * @brief   滚动数组优化版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#define MAX 5010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char str1[MAX], str2[MAX];
int DP[2][MAX];

int LCS( int len )
{
	DP[0][0] = 0;
	for ( int i = 1; i <= len; ++i )
		for ( int j = 1; j <= len; ++j )
			DP[i%2][j] = max( max( DP[(i-1)%2][j], DP[i%2][j - 1] ), DP[(i-1)%2][j - 1] + ( str1[i] == str2[j] ? 1 : 0 ) );
	return DP[len%2][len];
}

int main()
{
	int len;
	while ( scanf("%d", &len) != EOF )
	{
		scanf("%s", str1 + 1);
		str2[len + 1] = 0;
		for ( int i = len; i >= 1; --i )
			str2[len - i + 1] = str1[i];
		printf( "%d\n", len - LCS( len ) );
	}
}
