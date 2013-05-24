/**
 * @file HDU_2159.cpp
 * @brief   二维背包模板题，尼玛劳资一开始当成一维完全背包处理了！！！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-21
 */
#include <cstdio>
#include <algorithm>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
int DP[110][110], v[110], w[110];
int main()
{
	int m, n, z, s, i, j, k;
	char stop;
	while ( scanf("%d %d %d %d", &n, &m, &z, &s) != EOF )
	{
		CLR(DP, 0);
		for ( i = 0; i < z; ++i )
			scanf("%d %d", &w[i], &v[i]);
		for ( i = 0; i < z; ++i )
			for ( j = v[i]; j <= m; ++j )
				for ( k = 1; k <= s; ++k )
					DP[j][k] = max( DP[j][k], DP[j - v[i]][k - 1] + w[i] );
		for ( j = 0; j <= m; ++j )
			for ( k = 0; k <= s; ++k )
				if ( DP[j][k] >= n )
				{
					printf("%d\n", m - j );
					goto end;
				}
		printf("-1\n");
end:;
	}
}
