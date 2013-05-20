/**
 * @file HDU_3397.cpp
 * @brief   线段树区间合并类问题，千万注意lazy标记的处理顺序。
 * Pushup的时候更新上提的nSum和连续长度；Pushdown的时候更新左右儿子的Xor标记或者覆盖标记。
 * 注意这个时候是要立刻对儿子的几个数量标记进行同步的！
 * 另外这题一开始输出搞错了，真是WA到死啊！！！查询总数的时候好办；
 * 查询最大连续长度就要小心了，是要从左右儿子的最大长度、合并后产生的最大长度中取最大值；
 * 而合并后的最大长度要考虑到是否选取了那些区间。具体看代码。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-20
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
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define L_son root << 1
#define R_son root << 1 | 1
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char flags[MAX];

struct TMD
{
	int L, R;
	int lSeq1, rSeq1, mSeq1, lSeq0, rSeq0, mSeq0, nSum, Xor, Cover;
	int len(){return R - L + 1;}
} Tree[MAX<<2];
void Sync( int root )
{
	if ( Tree[root].Cover )
	{
		Tree[root].lSeq1 = Tree[root].rSeq1 = \
			Tree[root].mSeq1 = Tree[root].nSum = Tree[root].len();
		Tree[root].lSeq0 = Tree[root].rSeq0 = Tree[root].mSeq0 = 0;
	}
	else
	{
		Tree[root].lSeq1 = Tree[root].rSeq1 = \
			Tree[root].mSeq1 = Tree[root].nSum = 0;
		Tree[root].lSeq0 = Tree[root].rSeq0 = \
			Tree[root].mSeq0 = Tree[root].len();
	}
}

void PushUp( int root )
{
	Tree[root].nSum = Tree[L_son].nSum + Tree[R_son].nSum;

	if ( Tree[L_son].lSeq1 == Tree[L_son].len() )
		Tree[root].lSeq1 = Tree[L_son].lSeq1 + Tree[R_son].lSeq1;
	else
		Tree[root].lSeq1 = Tree[L_son].lSeq1;
	if ( Tree[R_son].rSeq1 == Tree[R_son].len() )
		Tree[root].rSeq1 = Tree[L_son].rSeq1 + Tree[R_son].rSeq1;
	else
		Tree[root].rSeq1 = Tree[R_son].rSeq1;

	Tree[root].mSeq1 = Tree[L_son].rSeq1 + Tree[R_son].lSeq1;
	if ( Tree[L_son].mSeq1 > Tree[root].mSeq1 )
		Tree[root].mSeq1 = Tree[L_son].mSeq1;
	if ( Tree[R_son].mSeq1 > Tree[root].mSeq1 )
		Tree[root].mSeq1 = Tree[R_son].mSeq1;

	if ( Tree[L_son].lSeq0 == Tree[L_son].len() )
		Tree[root].lSeq0 = Tree[L_son].lSeq0 + Tree[R_son].lSeq0;
	else
		Tree[root].lSeq0 = Tree[L_son].lSeq0;
	if ( Tree[R_son].rSeq0 == Tree[R_son].len() )
		Tree[root].rSeq0 = Tree[L_son].rSeq0 + Tree[R_son].rSeq0;
	else
		Tree[root].rSeq0 = Tree[R_son].rSeq0;
	Tree[root].mSeq0 = Tree[L_son].rSeq0 + Tree[R_son].lSeq0;
	if ( Tree[L_son].mSeq0 > Tree[root].mSeq0 )
		Tree[root].mSeq0 = Tree[L_son].mSeq0;
	if ( Tree[R_son].mSeq0 > Tree[root].mSeq0 )
		Tree[root].mSeq0 = Tree[R_son].mSeq0;
}

void Exec( int root )
{
	Tree[root].nSum = Tree[root].len() - Tree[root].nSum;
	swap( Tree[root].lSeq0, Tree[root].lSeq1 );
	swap( Tree[root].rSeq0, Tree[root].rSeq1 );
	swap( Tree[root].mSeq0, Tree[root].mSeq1 );
	if ( Tree[root].Cover != -1 )
		Tree[root].Cover ^= 1;
}

void PushDown( int root )
{
	if ( Tree[root].Xor )
	{
		Tree[L_son].Xor ^= 1;
		Exec(L_son);
		Tree[R_son].Xor ^= 1;
		Exec(R_son);
		Tree[root].Xor = 0;
	}
	if ( Tree[root].Cover != -1 )
	{
		Tree[L_son].Cover = Tree[R_son].Cover = Tree[root].Cover;
		Sync(L_son);
		Sync(R_son);
		Tree[root].Cover = -1;
	}
}
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Xor = 0;
	Tree[root].Cover = -1;
	if (L == R)
	{
		Tree[root].Cover = flags[L];
		Sync(root);
		return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
	PushUp(root);
}
void Update( int root, int L, int R, int num )
{
	if ( L == Tree[root].L && R == Tree[root].R )
	{
		Tree[root].Cover = num;
		Sync(root);
		return;
	}
	PushDown(root);
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( L > M )
		Update( R_son, L, R, num );
	else if ( R <= M )
		Update( L_son, L, R, num );
	else
	{
		Update( L_son, L, M, num );
		Update( R_son, M + 1, R, num );
	}
	PushUp(root);
}

int Query_Sum( int root, int L, int R )
{
	if ( Tree[root].L == L && Tree[root].R == R )
		return Tree[root].nSum;
	PushDown(root);
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query_Sum( L_son, L, R );
	else if ( L > M )
		return Query_Sum( R_son, L, R );
	else
		return Query_Sum( L_son, L, M ) + Query_Sum( R_son, M + 1, R );
	PushUp(root);
}

int Query_Seq( int root, int L, int R )
{
	if ( Tree[root].L == L && Tree[root].R == R )
		return Tree[root].mSeq1;
	PushDown(root);
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query_Seq( L_son, L, R );
	else if ( L > M )
		return Query_Seq( R_son, L, R );
	else
	{
		int left, right;
		//这一步非常关键！！！
		left  = min( Tree[L_son].rSeq1, M - L + 1 );
		right = min( Tree[R_son].lSeq1, R - M );
		return max( max( Query_Seq( L_son, L, M ), Query_Seq( R_son, M + 1, R ) ), left + right );
	}
	PushUp(root);
}

void Update_Xor( int root, int L, int R )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].Xor ^= 1;
		Exec(root);
		return;
	}
	PushDown(root);
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		Update_Xor( L_son, L, R );
	else if ( L > M )
		Update_Xor( R_son, L, R );
	else
	{
		Update_Xor( L_son, L, M );
		Update_Xor( R_son, M + 1, R );
	}
	PushUp(root);
}
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, n, m, i, tmp, op, a, b, j;
	scanf("%d", &T);
	while ( T-- )
	{
		CLR(flags, 0);
		scanf("%d %d", &n, &m);
		
		for ( i = 1; i <= n; ++i )
		{
			scanf("%d", &tmp);
			flags[i] = tmp;
		}
		CreateTree( 1, 1, n );
		for ( i = 0; i < m; ++i )
		{
			scanf("%d %d %d", &op, &a, &b);
			a++; b++;
			switch ( op )
			{
			case 0:
				Update(1, a, b, 0);
				break;
			case 1:
				Update(1, a, b, 1);
				break;
			case 2:
				Update_Xor( 1, a, b );
				break;
			case 3:
				printf("%d\n", Query_Sum(1, a, b));
				break;
			case 4:
				printf("%d\n", Query_Seq(1, a, b));
				break;
			}
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
