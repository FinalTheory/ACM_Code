/**
 * @file HDU_2795.cpp
 * @brief   线段树单点更新问题。
 * 这道题需要注意的是每次建树不能一开始就完全建立，因为区间太大会MLE。
 * 因为每个区间的初始最大值是确定的，所以只需要每次查询时建立节点即可。
 * 由于在递归调用的过程中传递了区间端点，所以节点中不用保存端点信息。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-25
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int h, w;
int h_pos;

inline int _max( int A, int B )
{
	return A > B ? A : B;
}
struct TMD
{
	int nMax;
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nMax = w;
	}
};
stack<TMD *> Pointers;

void Query( TMD * root, int wei, int L, int R )
{
	//这里添加左右孩子节点
	if ( root->p_left == NULL )
	{
		root->p_left = new TMD();
		Pointers.push(root->p_left);
	}
	if ( root->p_right == NULL )
	{
		root->p_right = new TMD();
		Pointers.push(root->p_right);
	}
	//查询失败的话直接返回
	if ( root->nMax < wei )
		return;
	if ( L == R )//如果查询到叶子节点，无论如何都要返回
	{
		if ( root->nMax >= wei )
		{
			h_pos = L;
			root->nMax -= wei;
		}
		return;
	}
	//上述都不成立的话优先查询左子树
	int M = ( L + R ) / 2;
	if ( root->p_left->nMax >= wei )
		Query( root->p_left, wei, L, M );
	else
		Query( root->p_right, wei, M + 1, R );
	//最后更新区间最大值
	root->nMax = _max( root->p_left->nMax, root->p_right->nMax );
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
	int n, i, wei;
	TMD * root;
	while ( scanf( "%d %d %d", &h, &w, &n ) != EOF )
	{
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = new TMD;
		Pointers.push(root);
		for ( i = 1; i <= n; ++i )
		{
			scanf("%d", &wei);
			h_pos = -1;
			Query( root, wei, 1, h );
			if ( h_pos != -1 )
				printf( "%d\n", h_pos );
			else
				printf("-1\n");
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
