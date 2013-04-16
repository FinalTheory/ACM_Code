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
#define SIZE 50
using namespace std;
char map1[SIZE];	//记录纵坐标方向有没有放置皇后。
char map2[SIZE];	//记录主对角线方向有没有放置皇后。
char map3[SIZE];	//记录副对角线方向有没有放置皇后。
int N;	//棋盘大小
int K;	//皇后数目
unsigned long long sum;	//方法总数

//num既表示当前已经放置的皇后数目，也表示已经放到了第几列。
//利用num的增大就可以遍历横坐标方向，也就是按列放皇后。
void DFS( int num )
{
	if ( num == K )
	{
		 sum++;
		 return;
	}
	//遍历纵坐标方向。
	for ( int i = 0; i < N; i++ )
		if ( !map1[i] && !map2[num - i + N - 1] && !map3[num + i] )	//这里(num - i + N - 1)中的-1是为了让map2从0开始记录。
		{
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 1;	//设置标记
			DFS(num + 1);
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 0;	//回溯
		}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif

	while( cin >> N >> K )
	{
		sum = 0;
		memset(map1, 0, sizeof(map1));
		memset(map2, 0, sizeof(map2));
		memset(map3, 0, sizeof(map3));
		DFS(0);
		cout << sum << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}