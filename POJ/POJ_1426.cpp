/*
	ֱ��BFS����������MLE������֦�޽ڲ��޽��Ƶ�ʹ��new�ı�Ȼ�����
	Ϊ���ȿ���AC�����������ֱ�Ӵ����һ������ô������ֶΡ�
	����������˻��Ǳ���������Щֱ����unsigned long long��m�ģ�̫TMD����ˣ�����ֻ����Ϊ��������
	�����copy�ı��˵ļ�֦���õ���һ�����ʣ����ĳ���������ֹ����Ͳ��ٶ���������һ���ڵ㡣
	ԭ��������йأ���ʱû�����ס�
	���⻹��һ��ͬ��ģ����������ǰһ�����������������浱ǰ������ֵ������Ż����Ӷȣ�0MS������ô���ġ�
	�������д��һ��������ģ�壬�Ǵ�������С���ģ������Լ���һ���ɹ��ɡ�
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define BIG 100000
using namespace std;
char * nums[BIG];
char flags[BIG];
char * nums_bak[BIG];
char remains[1000];
int div( char * num, int n, char * num_res )
{
	int len = strlen(num), i, j, remain = 0;
	for ( i = 0, j = 0; i < len; i++, j++ )
	{
		remain *= 10;
		remain += num[i] - 48;
		num_res[j] = remain / n;
		remain -= num_res[j] * n;
		num_res[j] += 48;
	}
	num_res[j] = 0;
	return remain;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, N, N_bak, i, j, num_len, k;

	char found, res[101];
	while ( cin >> n && n )
	{
		num_len = 3;
		memset(nums, NULL, sizeof(nums));
		memset(remains, 0, sizeof(remains));
		memset(nums_bak, NULL, sizeof(nums_bak));
		nums[0] = new char [num_len];
		nums[1] = new char [num_len];
		strcpy(nums[0], "10");
		strcpy(nums[1], "11");
		N = 2;
		found = 0;
		while ( !found )
		{
			//�ȼ�⵱ǰ�����нڵ��Ƿ�����
			num_len++;
			N_bak = N;
			N = 0;
			for ( i = 0; i < N_bak; i++ )
			{
				nums_bak[i] = nums[i];
				k = div( nums[i], n, res );
				if ( remains[k] )
					flags[i] = 0;
				else
					remains[k] = 1;
				if ( !k )
				{
					cout << nums[i] << endl;
					found = 1;
					goto end;
				}
			}
			//Ȼ������һ��ڵ㡣(ֻ��ĳ���ڵ������û�г��ֹ�ʱ�Ź��졣)
			for ( i = 0; i < N_bak; i++ )
				for ( j = 48; j <= 49; j++ )
					if ( flags[i] )
					{
						nums[N] = new char [num_len];
						strcpy(nums[N], nums_bak[i]);
						nums[N][num_len - 2] = j;
						nums[N++][num_len - 1] = 0;
					}
end:
			memset(flags, 1, sizeof(flags));
		}
		delete [] nums[0];
		delete [] nums[1];
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}