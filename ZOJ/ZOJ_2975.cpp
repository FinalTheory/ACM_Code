/*
	上来看到题就想暴力枚举，倒是没TLE，TMD直接WA！
	上网查了一下，用了别人的一个思路，把所有行相互比较，看每行中同样的位置有多少对相同的；
	注意分别尝试5次。然后每次相同的数量为n，那么总数就加上C(2,n)也就是两两组合即可。
	最好少用switch，打个表即可。速度慢了点，360MS。
*/
#include <iostream>
#include <cstdio>
#define DIMEN 255
using namespace std;
char map[DIMEN][DIMEN];
int main()
{
	//freopen("in.txt", "r", stdin);
	int T, M, N, j, i, k, l, sum, same;
	cin >> T;
	while ( T-- )
	{
		sum = 0;
		cin >> M >> N;
		for ( i = 0; i < M; i++ )
			scanf("%s", map[i]);
		if ( M == 1 || N == 1 )
		{
			cout << 0 << endl;
			continue;
		}
		for ( i = 0; i < M; i++ )
			for ( j = 0; j < N; j++ )
				switch ( map[i][j] )
				{
					case 'B' :
						map[i][j] = 1;
						break;
					case 'J' :
						map[i][j] = 2;
						break;
					case 'H' :
						map[i][j] = 3;
						break;
					case 'Y' :
						map[i][j] = 4;
						break;
					case 'N' :
						map[i][j] = 5;
				}
		for ( k = 1; k <= 5; k++ )
		for ( i = 0; i < M - 1; i++ )
			for ( j = i+1; j < M; j++ )
			{
				same = 0;
				for ( l = 0; l < N; l++ )
					if ( map[i][l] == map[j][l] && map[i][l] == k )
						same++;
				sum += same * ( same - 1 ) / 2;
			}
		cout << sum << endl;
	}
}