/**
 * @file HDU_3308.cpp
 * @brief   线段树区间合并问题，本以为是神题，结果发现居然是求连续升序长度……
 * PushUp的时候注意一下左右子树能否合并；
 * Query的时候注意选取哪个有效长度。
 * 1A但是效率很挫，初始化的方法很不给力，整整多了一个2的常数，就这样吧先！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-29
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
int nums[MAX];
struct TMD
{
	int L, R;
	int lSum, rSum, maxSum;
	int len(){return R - L + 1;}
} Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].lSum = Tree[root].rSum = Tree[root].maxSum = 1;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void PushUp( int root )
{
	if ( nums[Tree[R_son].L] > nums[Tree[L_son].R] )
	{
		if ( Tree[L_son].lSum == Tree[L_son].len() )
			Tree[root].lSum = Tree[L_son].lSum + Tree[R_son].lSum;
		else
			Tree[root].lSum = Tree[L_son].lSum;
		if ( Tree[R_son].rSum == Tree[R_son].len() )
			Tree[root].rSum = Tree[L_son].rSum + Tree[R_son].rSum;
		else
			Tree[root].rSum = Tree[R_son].rSum;
		Tree[root].maxSum = Tree[L_son].rSum + Tree[R_son].lSum;
		if ( Tree[L_son].maxSum > Tree[root].maxSum ) Tree[root].maxSum = Tree[L_son].maxSum;
		if ( Tree[R_son].maxSum > Tree[root].maxSum ) Tree[root].maxSum = Tree[R_son].maxSum;
	}
	else
	{
		Tree[root].lSum = Tree[L_son].lSum;
		Tree[root].rSum = Tree[R_son].rSum;
		Tree[root].maxSum = max( Tree[L_son].maxSum, Tree[R_son].maxSum );
	}
}

void Insert( int root, int pos )
{
	if ( Tree[root].L == pos && Tree[root].R == pos )
		return;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos <= M )
		Insert( L_son, pos );
	else
		Insert( R_son, pos );
	PushUp(root);
}

int Query( int root, int L, int R )
{
	if ( L == Tree[root].L && R == Tree[root].R )
		return Tree[root].maxSum;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query( L_son, L, R );
	else if ( L > M )
		return Query( R_son, L, R );
	else
	{
		if ( nums[Tree[R_son].L] > nums[Tree[L_son].R] )
		{
			int left = min( Tree[L_son].rSum, M - L + 1 );
			int right = min( Tree[R_son].lSum, R - M );
			return max( left + right, max( Query( 1, L, M ), Query( 1, M + 1, R ) ) );
		}
		else
			return max( Query( 1, L, M ), Query( 1, M + 1, R ) );
	}
}

int main()
{
	int T, n, m, i, a, b;
	char op[3];
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &n, &m);
		CreateTree( 1, 1, n );
		for ( i = 1; i <= n; ++i )
			scanf("%d", &nums[i]);
		for ( i = 1; i <= n; ++i )
			Insert( 1, i );
		for ( i = 0; i < m; ++i )
		{
			scanf("%s %d %d", op, &a, &b);
			if ( op[0] == 'U' )
			{
				nums[++a] = b;
				Insert( 1, a );
			}
			else
				printf("%d\n", Query( 1, ++a, ++b ));
		}
	}
}
