/*
	树状数组，主要记住求和方法以及修改某个元素的方法。
	另外，这种大量I/O的题目，建议使用C++编译器，效率更高。
	似乎G++经常出现诡异的问题，不知道是不是版本原因。
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
		x++;	//这一步为了保证x是正的，防止在Lowbit函数陷入死循环。
		level[Sum(x)]++;
		plus(x);
	}
	for ( i = 0; i < N; i++ )
		cout << level[i] << '\n';
	return 0;
}