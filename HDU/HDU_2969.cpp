/*
	������Ӧ����̰�����⡣���ȶ����и߶����򣬼�¼ԭ����λ�á�
	Ȼ��߶ȴӵ�����ö�٣��������ڵȸ������������鶼����ô�����Ժ�ͼ�һ��������߶��;�Ҫ��һ��
	��ʼ��ʱ����˵�����Լ����Ҷ˵��ұ߶�Ϊ�㣬���Ǳ߽����⡣
	���ע��I/O�����������Ҫ��scanf��printf����������g++��
	�������Ϊ���TLE��N��ΰ�������
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <ctime>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SIZE 1001000
using namespace std;
struct TMD
{
	int height, index;
} bulidings[SIZE];
int height[SIZE];
bool fuck( TMD A, TMD B )
{
	if ( A.height != B.height )
		return A.height < B.height;
	else
		return A.index < B.index;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int t, n, d, i, j, sum, day, left, right;
	cin >> t;
	while ( t-- )
	{
		scanf("%d %d", &n, &d);
		sum = 1;
		for ( i = 1; i <= n; i++ )
		{
			scanf("%d", height + i);
			bulidings[i].height = height[i];
			bulidings[i].index = i;
		}
		sort( bulidings + 1, bulidings + n + 1, fuck );
		bulidings[0].height = bulidings[n+1].height = 0;
		i = 1;
		for ( j = 0; j < d; j++ )
		{
			scanf("%d", &day);
			while ( bulidings[i].height <= day && i <= n )
			{
				left = i;
				while ( bulidings[i+1].index == bulidings[i].index + 1 && bulidings[i].height == bulidings[i+1].height )
					i++;
				right = i;
				if ( height[bulidings[left].index - 1] > bulidings[left].height )
					if ( height[bulidings[right].index + 1] > bulidings[right].height )
						sum++;
				if ( height[bulidings[left].index - 1] < bulidings[left].height )
					if ( height[bulidings[right].index + 1] < bulidings[right].height )
						sum--;
				i++;
			}
			printf("%d ", sum);
		}
		printf("\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}