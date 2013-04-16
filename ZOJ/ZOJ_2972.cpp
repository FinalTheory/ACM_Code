/*
	���ֵı������⡣��׶�Ϊi��ʣ������Ϊv��״̬ת�Ʒ������£�
	f[i][v] = MIN( f[i-1][v] + T2, f[i-1][v+F1] + T1, f[i-1][v-F2] + T3 )
	Ҳ����˵����ÿһ���׶Σ�ÿһ������״̬����Ȼ����ѡ����ģʽ��
	���ȶ���ÿһ���׶ε�����״̬����ʼ��Ϊ��һ���׶ε��ټ���T2��
	Ҳ���Ǽ��趼��Normal����Ϊ�������Normal�϶��ǺϷ��ġ�
	Ȼ��������ƣ�����״̬ת�ƣ�Ҫ������Ϸ��ԣ�Ҳ���ǿ�v��ֵ�Ƿ�����������д�������
	��Ȼ����������ʱÿһ�׶ο϶�����ͬʱ����������״̬ת�Ƶ�����״̬��
	Ҳ����˵������ÿһ������״̬�����ǱȽ����������Ե�����ģʽ��ѡ����ֵ��С�ġ�
	�����ڳ�ʼ����ʱ�������ڵ���׶���m����������ӵ����������µ����ʱ����ȻΪ0������dp[0][m]=0��
	��������׶�֮ǰû���������ܵĻ��ᣬ������������״̬û�кϷ�ֵ����˳�ʼ��ΪINF��
*/
#include <iostream>
#include <cstdio>
#include <climits>
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
int dp[120][120];
int main()
{
	//freopen("in.txt", "r", stdin);
	int T, N, M, i, j, v, T1, T2, T3, F1, F2, mini;
	cin >> T;
	while ( T-- )
	{
		cin >> N >> M;
		for ( i = 0; i < M; i++ )
			dp[0][i] = INT_MAX - 1000;
		dp[0][M] = 0;
		for ( i = 1; i <= N; i++ )
		{
			cin >> T1 >> T2 >> T3 >> F1 >> F2;
			for ( v = M ; v >= 0; v-- )
				dp[i][v] = dp[i-1][v] + T2;
			for ( v = M + F2; v >= 0; v-- )
			{
				if ( v + F1 <= M )
					dp[i][v] = MIN(dp[i][v], dp[i-1][v+F1] + T1);
				if ( v >= F2 )
					( v < M ) ? dp[i][v] = MIN(dp[i][v], dp[i-1][v-F2] + T3) : dp[i][M] = MIN(dp[i][M], dp[i-1][v-F2] + T3);
			}
		}
		mini = INT_MAX - 1000;
		for( j = 0; j <= M; j++ )
			if( dp[N][j] < mini )
				mini = dp[N][j];
		cout << mini << endl;
	}
}