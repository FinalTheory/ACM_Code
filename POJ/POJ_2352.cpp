/*
	��״���飬��Ҫ��ס��ͷ����Լ��޸�ĳ��Ԫ�صķ�����
	���⣬���ִ���I/O����Ŀ������ʹ��C++��������Ч�ʸ��ߡ�
	�ƺ�G++�������ֹ�������⣬��֪���ǲ��ǰ汾ԭ��
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int tree[32001];
int level[15001];
int Lowbit(int t) 
{ 
    return t & ( t ^ ( t - 1 ) ); 
}
int Sum(int end) 
{ 
    int sum = 0; 
    while(end > 0) 
    { 
			sum += tree[end]; 
			end -= Lowbit(end); 
    } 
    return sum; 
}
void plus(int pos)
{
    while(pos <= 32001) 
    { 
			tree[pos]++; 
      pos += Lowbit(pos); 
    }
}
int main(void)
{
	//freopen("123.txt","r",stdin);
	int N, x, y, i;
	scanf("%d", &N);
	for ( i = 0; i < N; i++ )
	{
		scanf("%d %d", &x, &y);
		x++;	//��һ��Ϊ�˱�֤x�����ģ���ֹ��Lowbit����������ѭ����
		level[Sum(x)]++;
		plus(x);
	}
	for ( i = 0; i < N; i++ )
		cout << level[i] << '\n';
	return 0;
}