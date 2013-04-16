/*
	虽然是水题，但是这个东西背后蕴含的可是非常深啊！
	简单的规则却可以生成丝毫不重复的图案！
*/
#include <iostream>
#include <stdio.h>
using namespace std;
short densities[21][21], densities_new[21][21];
void sum( int i, int j, int *K )
{
	*K = densities[i][j];
	if ( i - 1 >= 0 ) *K += densities[i-1][j];
	if ( i + 1 < 20 ) *K += densities[i+1][j];
	if ( j - 1 >= 0 ) *K += densities[i][j-1];
	if ( j + 1 < 20 ) *K += densities[i][j+1];
}
int main()
{
	//freopen("123.txt", "r", stdin);
	int D[17], i, j, days, K;
	char s[5] = ".!X#";
	cin >> days;
	for ( i = 0; i < 16; i++ )
		cin >> D[i];
	for ( i = 0; i < 20; i++ )
		for ( j = 0; j < 20; j++ )
			cin >> densities_new[i][j];
	while ( days-- )
	{
		for ( i = 0; i < 20; i++ )
			for ( j = 0; j < 20; j++ )
				densities[i][j] = densities_new[i][j];
		for ( i = 0; i < 20; i++ )
			for ( j = 0; j < 20; j++ )
			{
				sum( i, j, &K );
				densities_new[i][j] += D[K];
				if ( densities_new[i][j] < 0 )
					densities_new[i][j] = 0;
				if ( densities_new[i][j] > 3 )
					densities_new[i][j] = 3;
			}
	}
	for ( i = 0; i < 20; i++ )
	{
		for ( j = 0; j < 20; j++ )
			printf("%c", s[densities_new[i][j]]);
		printf("\n");
	}
}