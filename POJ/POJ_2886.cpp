/**
 * @file POJ_2886.cpp
 * @brief   线段树单点更新，这次用了数组模拟的写法，这贱题卡链表！
 * 注意完全二叉树的性质，对于一个节点i，它的父亲是i>>2，左儿子是i<<1，右儿子是i<<1|1
 * 至于计算下一个位置的方法是抄的别人的，这种东西我一向绕不过来。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-30
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
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>
#include <stack>
#define MAX 500010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
using namespace std;
char prime[MAX+10];
char names[MAX+10][20];
int move_p[MAX+10], F[MAX+10];
void Init_Prime()
{
	//生成整除的个数表
	int i, j, k, tmp;
	memset( prime, 1, sizeof(prime) );
	for ( i = 1; i <= MAX; ++i )
		F[i] = 1;
	for ( i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	for ( i = 2; i <= MAX; ++i )
	{
		if ( prime[i] )
		{
			for ( j = i; j <= MAX; j += i )
			{
				k = j;
				tmp = 1;
				while ( !(k % i) )
				{
					tmp++;
					k /= i;
				}
				F[j] *= tmp;
			}
		}
	}
}
struct TMD
{
	int L, R, nSum;
}Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nSum = R - L + 1;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

int Query( int root, int pos )
{
	Tree[root].nSum--;
	//如果查询到了根节点
	if ( Tree[root].L == Tree[root].R )
		return Tree[root].L;
	if ( Tree[L_son].nSum >= pos )
		return Query( L_son, pos );
	else
		return Query( R_son, pos - Tree[L_son].nSum );
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, K, i, seq, max_can;
	int current, move, index;
	char max_name[20];
	Init_Prime();
	while ( scanf("%d %d", &N, &K) != EOF )
	{
		for ( i = 1; i <= N; ++i )
			scanf("%s %d", names[i], &move_p[i]);
		CreateTree( 1, 1, N );
		seq = 1; max_can = 0;
		current = K;
		while ( 1 )
		{
			N--;
			if ( N == 0 )
				break;
			index = Query( 1, current );
			if ( move_p[index] > 0 )
				current = ( current - 1 + move_p[index] - 1 ) % N + 1;
			else
				current = ( ( current - 1 + move_p[index] ) % N + N ) % N + 1;
			if ( F[seq] > max_can )
			{
				max_can = F[seq];
				strcpy( max_name, names[index] );
			}
			seq++;
		}
		if ( F[seq] > max_can )
		{
			index = Query( 1, 1 );
			max_can = F[seq];
			strcpy( max_name, names[index] );
		}
		printf( "%s %d\n", max_name, max_can );
	}


#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
