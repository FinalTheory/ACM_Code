/*
	ͼ�����⡣����Havel-Hakimi�㷨��
	�ж��Ƿ���Թ����һ����������������е�ͼ��
	������Ҳ��һ��̰���㷨��
	��ѭ����ʱ��ûע���޸���ѭ���յ㣬�������˰��찡���ꡭ��
	��������ѵ���һ��AC��������~~
	�п�������һ�±����������о�������������ݹ�ģҲ���Ǻܴ�����ӡ�
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct Node
{
	int du, index;
} nodes[10];
bool cmp( Node A, Node B )
{
	return A.du > B.du;
}
char map[10][10];
void link( int i, int j )
{
	map[i][j] = 1;
	map[j][i] = 1;
}
int main()
{
	int T, N, i, j, k, fail, stop;
	//freopen("123.txt", "r", stdin);
	cin >> T;
	while ( T-- )
	{
		cin >> N;
		stop = fail = 0;
		memset(map, 0, sizeof(map));
		for ( i = 0; i < N; i++ )
		{
			cin >> nodes[i].du;
			nodes[i].index = i;
		}
		sort(nodes, nodes + N, cmp);
		while(!stop)
		{
			k = nodes[0].du;
			for ( i = 1; i <= k; i++ )
			{
				link( nodes[0].index, nodes[i].index );
				nodes[0].du--;
				nodes[i].du--;
				if ( nodes[i].du < 0 )
				{
					fail = 1;
					stop = 1;
					break;
				}
			}
			sort(nodes, nodes + N, cmp);
			if ( nodes[0].du == 0 )
				stop = 1;
		}
		if ( !fail )
		{
			printf("YES\n");
			for ( i = 0; i < N; i++ )
			{
				for ( j = 0; j < N; j++ )
					printf("%d ", map[i][j]);
				printf("\n");
			}
			printf("\n");
		}
		else
			printf("NO\n\n");
	}
}