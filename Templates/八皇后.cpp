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
#define SIZE 50
using namespace std;
char map1[SIZE];	//��¼�����귽����û�з��ûʺ�
char map2[SIZE];	//��¼���Խ��߷�����û�з��ûʺ�
char map3[SIZE];	//��¼���Խ��߷�����û�з��ûʺ�
int N;	//���̴�С
int K;	//�ʺ���Ŀ
unsigned long long sum;	//��������

//num�ȱ�ʾ��ǰ�Ѿ����õĻʺ���Ŀ��Ҳ��ʾ�Ѿ��ŵ��˵ڼ��С�
//����num������Ϳ��Ա��������귽��Ҳ���ǰ��зŻʺ�
void DFS( int num )
{
	if ( num == K )
	{
		 sum++;
		 return;
	}
	//���������귽��
	for ( int i = 0; i < N; i++ )
		if ( !map1[i] && !map2[num - i + N - 1] && !map3[num + i] )	//����(num - i + N - 1)�е�-1��Ϊ����map2��0��ʼ��¼��
		{
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 1;	//���ñ��
			DFS(num + 1);
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 0;	//����
		}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif

	while( cin >> N >> K )
	{
		sum = 0;
		memset(map1, 0, sizeof(map1));
		memset(map2, 0, sizeof(map2));
		memset(map3, 0, sizeof(map3));
		DFS(0);
		cout << sum << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}