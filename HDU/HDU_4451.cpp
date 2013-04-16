/**
 * @file HDU_4451.cpp
 * @brief   HDU4451，枚举问题。
 * 重点是选取一个合适的策略。这道题的思考方式是，首先把不匹配的上衣和裤子放进map。
 * 然后枚举所有的衣服裤子组合，如果可以匹配的话总数可以加K也就是鞋子的总数,但是要减去与这条裤子不匹配的鞋子的数量。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-03-30
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAX 1010

using namespace std;

char map[MAX][MAX];
int disharmoniousshoes[MAX];

int main()
{
	int N, M, K, P, x, y, i, j;
	long long sum;
	char str1[20], str2[20];
	while ( scanf( "%d %d %d", &N, &M, &K ) == 3 && N && M && K )
	{
		memset( map, 0, sizeof(map) );
		memset( disharmoniousshoes, 0, sizeof(disharmoniousshoes) );
		scanf("%d", &P);
		while ( P-- )
		{
			scanf("%s %d %s %d", str1, &x, str2, &y);
			if ( !strcmp(str1, "clothes") )
				map[x][y] = 1;
			else
				disharmoniousshoes[x]++;
		}
		sum = 0;
		for ( i = 1; i <= N; ++i )
			for ( j = 1; j <= M; ++j )
				if ( !map[i][j] )
					sum += K - disharmoniousshoes[j];
		printf("%lld\n", sum);
	}
}
