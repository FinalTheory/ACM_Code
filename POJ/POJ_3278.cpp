/*
	BFS��Ŀ��һ��ʼSB�ص���DFS�ˣ������Ȼ���ߵ���ѭ���ˡ�
	���RP����������RE4��WAһ�Σ����Ź����������WA����Ϊ�����ж������������
	��֦�ǳ���Ҫ��������ĵ�����ǵ��������ٴδ���
	ע��˶���ʱ����������K�ģ���Ϊ�����Լ�������
	���˴����飬ռ���ڴ��е�󣬵���16MS����BFS���ǲ����ˡ�
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