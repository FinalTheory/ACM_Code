/*
	���Ϸ���ͦ�࣬��С�����������鼯����ġ��Լ��ķ���TLE�ˣ����ܵݹ��յ����õ������⡣
	copy�˱��˵�һ��̰�ĵ�˼·������������·����ʱ�������·���Ļ����Լ����˵�ֱ�ӱ�����map�Ϊ�˽�ʡ�������Ͳ�ѹ���ˣ���
	��������û��ͨ·������ǰ��ʼ����INF��Ȼ��ӱ��Ϊ0�ĵ㿪ʼ������0�㵽���е�Ļ���������cost���棬0���Ϊchecked��
	Ȼ�������ߵ�������̵�һ���㣨Ҳ���ǰ���������ӽ�sum�ǰ���������û�б��߹��������������ĵ�Ҳ���ǵ�ǰ��Ҳ��Ϊchecked��
	���Ÿ��»�����ö��һ�����е㣬�����ǰ�㵽���Ļ�����֮ǰ�Ǹ����٣���ô�������С�Ļ�������ԭ���Ļ�����
	�ٴ��ߵ�������С�ĵ㡣�ظ����Ϲ���N-1�Σ��������е㱻���Ϊchecked����ʱ����ÿ��ѡȡ�Ķ��ǻ�����С�ĵ㣬����·�߲��ظ�������ܻ���Ҳ����С�ġ�
	����˼·���ǣ���֤ÿ�λ�������С������±���һ�����е㣬���͵�̰�ġ�
	����ԭ���߰�ѭ������Ū���ˣ����±�������һ���жϲ���AC����Ϊѭ��N-1�κ����е�ȫ����checked����ʱminû�����ı仹��INF����Ȼ���ܱ��ӽ�ȥ��
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 100000000
#define DI 510
using namespace std;
int map[DI][DI], cost[DI];
char checked[DI];
int main()
{
	//freopen("in.txt", "r", stdin);
	int i, j, sum, K, min, bak, A, B, T, N, E;
	cin >> T;
	while( T-- )
	{
		cin >> N >> E;
		memset(checked, 0, sizeof(checked));
		sum = 0;
		for ( i = 0; i < N; i++ )
			for ( j = 0; j < N; j++ )
				map[i][j] = INF;
		for ( i = 0; i < E; i++ )
		{
			cin >> A >> B >> K;
			map[A][B] = map[B][A] = K;
		}
		bak = 0;
		for ( j = 0; j < N; j++ )
			cost[j] = map[0][j];
		checked[bak] = 1;
		for ( i = 0; i < N - 1; i++ )
		{
			min = INF;
			for ( j = 0; j < N; j++ )
				if ( !checked[j] && cost[j] < min )
				{
					bak = j;
					min = cost[j];
				}
			sum += min;
			checked[bak] = 1;
			for ( j = 0; j < N; j++ )
			{
				if ( !checked[j] && cost[j] > map[bak][j] )
					cost[j] = map[bak][j];
			}
		}
		cout << sum << endl;
	}
}