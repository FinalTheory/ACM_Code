/*
	这道题就是练习一下Dijkstra，注意输入数据的时候做一个对称矩阵；
	另外，需要考虑起始点与目的地相同的情况。
*/
#include <iostream>
#include <string.h>
using namespace std;
int roads[200][200], way[200];
char changed;
void update( int s )
{
	int i;
	for ( i = 0; i < 200; i++ )
	{
		if ( roads[s][i] != -1 )
			if ( way[s] + roads[s][i] < way[i] )
			{
				way[i] = way[s] + roads[s][i];
				changed = 1;
			}
	}
}
int main()
{
	int n, m, s, t, town1, town2, len, i;
	freopen("123.txt", "r", stdin);
	while ( cin >> n >> m )
	{
		memset(roads, -1, sizeof(roads));
		for ( i = 0; i < m; i++ )
		{
			cin >> town1 >> town2 >> len;

			if ( roads[town1][town2] == -1 || len < roads[town1][town2] )
				roads[town1][town2] = roads[town2][town1] = len;
		}
		cin >> s >> t;
		if ( s == t )
		{
			cout << 0 << endl;
			continue;
		}
		for ( i = 0; i < 200; i++ )
		{
			way[i] = 100000000;
			if ( roads[s][i] != -1 )
				way[i] = roads[s][i];
		}
		changed = 1;
		while ( changed )
		{
			changed = 0;
			for ( i = 0; i < 200; i++ )
				if ( way[i] != 100000000 )
					update(i);
		}
		if ( way[t] != 100000000 )
			cout << way[t] << endl;
		else
			cout << "-1" << endl;
	}
}