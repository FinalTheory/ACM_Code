/*
	������������뱩��ö�٣�����ûTLE��TMDֱ��WA��
	��������һ�£����˱��˵�һ��˼·�����������໥�Ƚϣ���ÿ����ͬ����λ���ж��ٶ���ͬ�ģ�
	ע��ֱ���5�Ρ�Ȼ��ÿ����ͬ������Ϊn����ô�����ͼ���C(2,n)Ҳ����������ϼ��ɡ�
	�������switch��������ɡ��ٶ����˵㣬360MS��
*/
#include <iostream>
#include <cstdio>
#define DIMEN 255
using namespace std;
char map[DIMEN][DIMEN];
int main()
{
	//freopen("in.txt", "r", stdin);
	int T, M, N, j, i, k, l, sum, same;
	cin >> T;
	while ( T-- )
	{
		sum = 0;
		cin >> M >> N;
		for ( i = 0; i < M; i++ )
			scanf("%s", map[i]);
		if ( M == 1 || N == 1 )
		{
			cout << 0 << endl;
			continue;
		}
		for ( i = 0; i < M; i++ )
			for ( j = 0; j < N; j++ )
				switch ( map[i][j] )
				{
					case 'B' :
						map[i][j] = 1;
						break;
					case 'J' :
						map[i][j] = 2;
						break;
					case 'H' :
						map[i][j] = 3;
						break;
					case 'Y' :
						map[i][j] = 4;
						break;
					case 'N' :
						map[i][j] = 5;
				}
		for ( k = 1; k <= 5; k++ )
		for ( i = 0; i < M - 1; i++ )
			for ( j = i+1; j < M; j++ )
			{
				same = 0;
				for ( l = 0; l < N; l++ )
					if ( map[i][l] == map[j][l] && map[i][l] == k )
						same++;
				sum += same * ( same - 1 ) / 2;
			}
		cout << sum << endl;
	}
}