/*
	��һ��λ����Ϳ����ˣ�0MS�����ٶȻ��Ǻܿ�ġ�
	ע�������ʽ��WA��һ�Ρ���
*/
#include <stdio.h>

int main()
{
	int T, i, j, num;
	unsigned n, n2;
	scanf("%d" ,&T);
	for ( j = 1; j <= T; j++ )
	{
		num = 0;
		scanf("%d" ,&n);
		for ( i = 0; i < 32; i++ )
		{
			n2 = n>>i;
			n2 &= 1;
			if ( n2 )
				num++;
		}
		printf("Case %d: %s\n", j, ( num%2 ) ? "odd" : "even");
	}
}