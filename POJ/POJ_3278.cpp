/*
	BFS题目，一开始SB地当成DFS了，结果果然杯具地死循环了。
	这次RP掉的厉害，RE4次WA一次，最后才过，结果发现WA是因为两个判断条件设计有误。
	剪枝非常重要，处理过的点必须标记掉，不能再次处理。
	注意乘二的时候是允许超出K的，因为还可以减回来！
	开了大数组，占用内存有点大，但是16MS过，BFS算是不错了。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
int N, K, found, T, NUM, NUM_bak;
int nums[200002];
int bak[200002];
char visited[200002];
int main()
{
	//freopen( "in.txt", "r", stdin );
	int i, t;
	while ( cin >> N >> K )
	{
		if ( N >= K )
		{
			cout << N - K << endl;
			continue;
		}
		t = NUM = found = 0;
		memset(visited, 0, sizeof(visited));
		nums[NUM++] = N;
		while (!found)
		{
			NUM_bak = NUM;
			NUM = 0;
			for ( i = 0; i < NUM_bak; i++ )
			{
				visited[nums[i]] = 1;
				bak[i] = nums[i];
				if ( nums[i] == K )
				{
					cout << t << endl;
					found = 1;
					goto end;
				}
			}
			for ( i = 0; i < NUM_bak; i++ )
			{
				if ( bak[i] <= K && !visited[2 * bak[i]] )
					nums[NUM++] = 2 * bak[i];
				if ( bak[i] >= 1 && !visited[bak[i] - 1] )
					nums[NUM++] = bak[i] - 1;
				if ( bak[i] <= K && !visited[bak[i] + 1] )
					nums[NUM++] = bak[i] + 1;
			}
end:
			t++;
		}
	}
}