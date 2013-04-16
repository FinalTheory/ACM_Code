/*
	д����DFS���������һ�������ǣģУ�����ֱ�Ӵ�����͡�
	�˻ʺ���Ҫ�����Ⱑ�����ǽ���ı��˵�˼·�������ˡ�
	����������봿��Ϊ����д���ݹ�ݹ鷳���ˣ�

#include <iostream>
using namespace std;
const long table[9][65] = { { 1 },
{ 1, 4, 4 },
{ 1, 9, 26, 26, 8 },
{ 1, 16, 92, 232, 260, 112, 16 },
{ 1, 25, 240, 1124, 2728, 3368, 1960, 440, 32 },
{ 1, 36, 520, 3896, 16428, 39680, 53744, 38368, 12944, 1600, 64 },
{ 1, 49, 994, 10894, 70792, 282248, 692320, 1022320, 867328, 389312, 81184, 5792, 128 },
{ 1, 64, 1736, 26192, 242856, 1444928, 5599888, 14082528, 22522960, 22057472, 12448832, 
3672448, 489536, 20224, 256 },
 };

int main()
{
long n, k;
while ( cin >> n >> k && n + k )
{
cout << table[n][k] << endl;
}
return 0;
}


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
#define M 0.00001
using namespace std;
char map1[40], map2[40];
int num[50];
unsigned long long sum;
int n, k;
bool check( int i, int j )
{
	if ( i < 0 || i >= n || j < 0 || j >= n )
		return 0;
	return 1;
}
void DFS( int x, int y, int num )
{
	
	if ( num == k )
	{
		sum++;
		return;
	}
	if ( x >= n )
		return;
	int i;
	//���y����û�е��ף���ô�ʹ�y������ѡһ��û�б�ռ�õķš�
	for ( i = y; i < n; i++ )
		if ( !map1[x - i + n] && !map2[x + i] )	//�Խ����ж��Ƿ���Էš�
		{
			map1[x - i + n] = map2[x + i] = 1;
			DFS( x, i, num + 1 );				//����һ�е���һ��λ���Ƿ�ɷš������Ժ���Ȼnum + 1��
			map1[x - i + n] = map2[x + i] = 0;	//����
		}
	DFS( x + 1, 0, num );						//���y�������ˣ��ʹ��ұ�һ�п�ʼ�š�
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	//while ( cin >> n >> k )
	cout << "{ ";
	for ( n = 1; n <= 8; n++ )
	{
		cout << "{ ";
		for ( k = 0; k < 2 * n - 1; k++ )
		{
			sum = 0;
			memset(map1, 0, sizeof(map1));
			memset(map2, 0, sizeof(map2));
			//��x=0, y=0��ʼ����
			DFS(0, 0, 0);
			if ( k != 0 )
				cout << ", ";
			cout << sum;
		}
		cout << " }" << endl;
	}
	cout << " }";
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}