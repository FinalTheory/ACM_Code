/*
	��׼�Ĳ��鼯�������������е�·��Ϣ������
	����ÿһ����·�����ˣ�������ǵĸ���ͬ������������������ߵĸ���
	����Ǳ������д�ׯ��������ǵĸ��ڵ��Ƿ���ͬ������ͬ�ʹӸ��ڵ���1�ڵ���·��
	���⿴����scanf��I/OЧ�ʻ��Ǳ�cin�첻�ٵģ�����ر���ͬ����
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)
#define SIZE 1005
#define MAX_SIZE 500000
using namespace std;
int set[SIZE];
struct TMD
{
	int A, B;
} roads[MAX_SIZE];
char flags[MAX_SIZE];
bool fuck( TMD A, TMD B )
{
	if ( A.A != B.A )
		return A.A < B.A;
	else
		return A.B < B.B;
}
int find( int x )
{
	int r = x, i = x, j;
	while ( set[r] != r )
		r = set[r];
	while ( i != r )
	{
		j = set[i];
		set[i] = r;
		i = j;
	}
	return r;
}
void merge( int a, int b )
{
	if ( a < b )
		set[b] = a;
	else
		set[a] = b;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, i, sum, root_a, root_b, A, B;
	while ( scanf( "%d %d", &N, &M ) && N )
	{
		sum = 0;
		memset(flags, 1, sizeof(flags));
		for ( i = 1; i <= N; i++ )
			set[i] = i;
		for ( i = 0; i < M; i++ )
		{
			scanf( "%d %d", &A, &B );
			if ( A > B )
				SWAP( A, B );
			roads[i].A = A; roads[i].B = B;
		}
		sort(roads, roads + M, fuck);
		for ( i = 1; i < M; i++ )
			if ( roads[i].A == roads[i-1].A && roads[i].B == roads[i-1].B )
				flags[i] = 0;
		for ( i = 0; i < M; i++ )
			if ( flags[i] )
			{
				root_a = find( roads[i].A );
				root_b = find( roads[i].B );
				merge( root_a, root_b );
			}
		for ( i = 1; i <= N; i++ )
			if ( ( root_a = find( i ) ) != 1 )
			{
				++sum;
				merge( 1, root_a );
			}
		printf("%d\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}