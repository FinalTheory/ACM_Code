/*
	����û�Ƴ�������������ֱ��DP�ˡ�
	��2^k��ʱ��Ӧ����λ�����ٶȿ죬���ǲ�֪����ô�������������
*/
#include <cstdlib>
#include <cmath>
#include <iostream> 
using namespace std;
unsigned long long mini, sum,  moves[65] = {0, 1, 3, 5};
int main()
{
	int N, i, k;
	for ( i = 2; i <= 64; i++ )
	{
		mini = ~0;
		for ( k = 1; k <= i-1; k++ )
			if ( ( sum = 2 * moves[i-k] + pow((double)2, (double)k) - 1 ) < mini )
				mini = sum;
		moves[i] = mini;
	}
	while ( cin >> N )
		cout << moves[N] << endl;
}