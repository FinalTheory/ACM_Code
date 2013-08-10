/**
 * @file POJ_3468.cpp
 * @brief   线段树水题，加入了更新操作，具体情况代码里有注释。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-24
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
#include <stack>
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
typedef long long LL;

inline int max( int a, int b )
{
	return a > b ? a : b;
}
inline int min( int a, int b )
{
	return a < b ? a : b;
}

struct TMD
{
	int L, R;		//区间左右端点
	LL nSum;		//保存求和
	LL nInc;		//保存增量
	TMD * p_left, * p_right;	//左右子树指针
	TMD()
	{
		p_left = p_right = NULL;
		nSum = nInc = 0;
	}
};

stack<TMD *> Pointers;

TMD * CreateTree( int L, int R )
{
	TMD * root = new TMD;
	Pointers.push(root);
	root->L = L;
	root->R = R;
	if ( L != R )
	{
		int M = ( L + R ) / 2;
		root->p_left  = CreateTree( L, M );
		root->p_right = CreateTree( M + 1, R );
	}
	return root;
}
//将元素插入线段树
void Insert( TMD * root, LL num, int pos )
{
	if ( pos >= root->L && pos <= root->R )
		root->nSum += num;
	if ( root->L == pos && root->R == pos )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( pos > M )
		Insert( root->p_right, num, pos );
	else
		Insert( root->p_left, num, pos );
}

void Add( TMD * root, int L, int R, int num )
{
	//如果区间匹配的话直接更新增量，避免一直处理到叶子
	if ( root->L == L && root->R == R )
	{
		root->nInc += num;
		return;
	}
	//不完全匹配的话肯定也保证了在范围内，所以对当前区间直接增量就可以
	root->nSum += ( R - L + 1 ) * num;
	int M = ( root->L + root->R ) / 2;
	if ( L > M )
	{
		Add( root->p_right, L, R, num );
	}
	else if ( R <= M )
	{
		Add( root->p_left, L, R, num );
	}
	else
	{
		Add( root->p_left, L, M, num );
		Add( root->p_right, M + 1, R, num );
	}
}

LL Query( TMD * root, int L, int R )
{
	//查询区间匹配的话直接返回值
	if ( root->L == L && root->R == R )
		return root->nSum + root->nInc * ( R - L + 1 );
	//如果遇到不匹配，首先更新当前区间的求和
	root->nSum += root->nInc * ( root->R - root->L + 1 );
	int M = ( root->L + root->R ) / 2;
	//然后把增量传递给两个子树并清空当前节点的增量
	if ( root->nInc != 0 )
	{
		Add( root->p_left, root->L, M, root->nInc );
		Add( root->p_right, M + 1, root->R, root->nInc );
		root->nInc = 0;
	}
	//接下来继续递归查询
	if ( L > M )
	{
		return Query( root->p_right, L, R );
	}
	else if ( R <= M )
	{
		return Query( root->p_left, L, R );
	}
	else
	{
		return Query( root->p_left, L, M ) + Query( root->p_right, M + 1, R );
	}
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

	int N, Q, i, a, b, c;
	char com;
	LL num;
	TMD * root;
	while ( scanf("%d %d", &N, &Q) != EOF )
	{
		//释放内存
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}

		root = CreateTree( 1, N );

		for ( i = 1; i <= N; ++i )
		{
			scanf("%lld", &num);
			Insert( root, num, i );
		}
		for ( i = 1; i <= Q; ++i )
		{
			do 
			{
				com = getchar();
			} while ( com == '\n' );
			if ( com == 'C' )
			{
				scanf( "%d %d %d", &a, &b, &c );
				Add( root, a, b, c );
			}
			else
			{
				scanf("%d %d", &a, &b);
				printf( "%lld\n", Query( root, a, b ) );
			}
		}

	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
