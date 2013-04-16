/*
	KMP�㷨���⡣���Ƚ�������ת��Ȼ���ڵ�ת����ƥ��������
	Ȼ����ݷ��ص��ƥ�䳤�ȣ���Ϊ�����ַ�����
	�����������һ��strlen()������Ѫ��������С������ѭ�����TLE�ˡ�
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define SIZE 1000010
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
char str[SIZE], str_turn[SIZE];
int back[SIZE], len;

void get_next()
{
	int i, j;
	memset(back, 0, sizeof(back));
	i = 0; back[0] = -1; j = -1;
	while ( i < len )
	{
		if ( j == -1 || str[i] == str[j] )
		{
			++i, ++j;
			back[i] = j;
		}
		else
			j = back[j];
	}
}

int KMP()
{
	int i, j;
	int max = -2;
	i = j = 0;
	while ( i < len && j < len )
	{
		if ( j == -1 || str[j] == str_turn[i] )
		{
			++i;++j;
			if ( j > max )
				max = j;
		}
		else
			j = back[j];
	}
	return max;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, i, max;
	cin >> N;
	while ( N-- )
	{
		scanf("%s", str);
		len = strlen(str);
		for ( i = 0; i < len; i++ )
			str_turn[len - i - 1] = str[i];
		get_next();
		max = KMP();
		for ( i = len - max; i < len; i++ )
			printf("%c", str_turn[i]);
		printf("\n");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}