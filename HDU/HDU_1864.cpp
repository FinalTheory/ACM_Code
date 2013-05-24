/**
 * @file HDU_1864.cpp
 * @brief   这题还有更快的状态转移，但是懒得想直接用背包硬上了！
 * 题意各种模糊，具体只能看代码了，01背包敲起来倒是挺快，题意就尼玛呵呵了……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-22
 */
#include <algorithm>
#include <cstdio>
#define eps 0.00001
#define maxn 60000
using namespace std;
int DP[31*1000*100];
int V[35];
int p_V;
int main()
{
	double Q, price, type[3];
	int N, i, j, m, V_all, v;
	char buffer[50], kind, cont;
	while ( scanf("%lf %d", &Q, &N) && N )
	{
		V_all = Q * 100.;
		p_V = 0;
		for ( i = 0; i < N; ++i )
		{
			type[0] = type[1] = type[2] = cont = 0;
			scanf("%d", &m);
			for ( j = 0; j < m; ++j )
			{
				scanf("%s", buffer);
				if ( cont ) continue;
				sscanf(buffer, "%c%*c%lf", &kind, &price);
				if ( kind == 'A' || kind == 'B' || kind == 'C' )
					type[kind - 'A'] += price;
				else
					cont = 1;
			}
			double sum = type[0] + type[1] + type[2];
			if ( !cont && sum <= 1000. && type[0] <= 600. && type[1] <= 600. && type[2] <= 600. )
				V[p_V++] = sum * 100.;
		}
		for ( i = 0; i <= V_all; ++i )
			DP[i] = 0;
		for ( i = 0; i < p_V; ++i )
			for ( v = V_all; v >= V[i]; --v )
				DP[v] = max( DP[v - V[i]] + V[i], DP[v] );
		printf("%.2lf\n", DP[V_all] / 100.);
	}
}
