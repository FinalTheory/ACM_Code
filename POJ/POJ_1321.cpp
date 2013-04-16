/*
	深度优先搜索，不过地图是不规则的这点比较讨厌。
	这种问题和八皇后不同点在于，它的棋子不一定是放满的，所以就要考虑多种情况。
	递归的时候第一个循环是从左到右竖着往下放，如果有位置放下了,就直接num+1去下一列。
	如果没有位置可放，还是去下一列，但是由于没有放下所以传递过去的是num而不是num+1。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <time.h>
#include <climits>
#define SIZE 10
int n, k;
char map[SIZE][SIZE];
char putted[SIZE];
unsigned long long sum;
using namespace std;
void DFS( int x, int num )
{
     if ( num == k )
     {
          sum++;
          return;
     }
    if ( x >= n )
    	return;
     for ( int i = 0; i < n; i++ )
          if ( map[i][x] == '#' && !putted[i] )
          {
               putted[i] = 1;
               DFS(x + 1, num+1);
               putted[i] = 0;
          }
     DFS( x + 1, num );
}

int main()
{
#ifndef ONLINE_JUDGE
     freopen( "in.txt", "r", stdin );
     //freopen( "out.txt", "w", stdout );
     clock_t program_start, program_end;
     program_start = clock();
#endif
     int i;
     
     while ( 1 )
     {
          cin >> n >> k;
          if ( n == -1 && k == -1 )
               break;
          sum = 0;
          for ( i = 0; i < n; i++ )
               scanf("%s", map[i]);
          memset(putted, 0, sizeof(putted));
          DFS(0, 0);
          cout << sum << endl;
     }
     
#ifndef ONLINE_JUDGE
     program_end = clock();
     cout << ( program_end - program_start ) << " MS" << endl;
#endif
}
