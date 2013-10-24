/**
 * @file POJ_2104.cpp
 * @brief   函数式线段树模版，区间第K大数。
 * @hint    函数式思想，只赋值不修改，保存所有历史版本，然后利用区间相减特性进行区间询问。
 *	    假设我们要询问整个区间内的第k大，我们只需离散化建树后，用二叉查找树的询问方式即可。
 *	    即如果左边元素个数sum>=k，递归查找左子树第k大，否则递归查找右子树第k - sum大，直到叶子。
 *	    注意这里利用到的区间相减性质，实际上是两颗不同历史的树进行相减：
 *	    一颗是插入到第l-1个元素的旧树，一颗是插入到第r元素的新树，
 *	    这样相减之后得到的是相当于只插入了[l, r]元素的一颗记录了区间数字个数的线段树。
 *	    对这颗线段树按照BST的方式询问，即可得到区间第k大。
 *	    但是每次建立新树，我们不需要新建所有的节点，而是只新建增加的节点。
 *	    也就是从根节点出发，先新建节点并复制原节点的值，然后进行修改即sum+1即可。
 *	    然后我们只需要修改左儿子或者右儿子其一的信息，一直递归到叶子。
 *	    注意初始状态下，即刚建树后，所有叶子节点的左右儿子都指向0号节点，也就是相当于NULL。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-08
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
//记录原数组、排序后的数组、每个元素对应的根节点
int nums[MAX], sorted[MAX], root[MAX];
int cnt;
struct TMD
{
	int sum, L_son, R_son;
} Tree[MAX<<5];
inline int CreateNode( int _sum, int _L_son, int _R_son )
{
	int idx = ++cnt;
	Tree[idx].sum = _sum;
	Tree[idx].L_son = _L_son;
	Tree[idx].R_son = _R_son;
	return idx;
}
void Insert( int & root, int pre_rt, int pos, int L, int R )
{
	//从根节点往下更新到叶子，新建立出一路更新的节点，这样就是一颗新树了。
	root = CreateNode( Tree[pre_rt].sum + 1, Tree[pre_rt].L_son, Tree[pre_rt].R_son );
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M )
		Insert( Tree[root].L_son, Tree[pre_rt].L_son, pos, L, M );
	else
		Insert( Tree[root].R_son, Tree[pre_rt].R_son, pos, M + 1, R );
}
int Query( int S, int E, int L, int R, int K )
{
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	//下面计算的sum就是当前询问的区间中，左儿子中的元素个数。
	int sum = Tree[Tree[E].L_son].sum - Tree[Tree[S].L_son].sum;
	if ( K <= sum )
		return Query( Tree[S].L_son, Tree[E].L_son, L, M, K );
	else
		return Query( Tree[S].R_son, Tree[E].R_son, M + 1, R, K - sum );
}
int main()
{
	int n, m, num, pos, T;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		cnt = 0; root[0] = 0;
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &nums[i]);
			sorted[i] = nums[i];
		}
		sort( sorted + 1, sorted + 1 + n );
		num = unique( sorted + 1, sorted + n + 1 ) - ( sorted + 1 );
		for ( int i = 1; i <= n; ++i )
		{
			//实际上是对每个元素建立了一颗线段树，保存其根节点
			pos = lower_bound( sorted + 1, sorted + num + 1, nums[i] ) - sorted;
			Insert( root[i], root[i - 1], pos, 1, num );
		}
		int l, r, k;
		while ( m-- )
		{
			scanf("%d %d %d", &l, &r, &k);
			pos = Query( root[l - 1], root[r], 1, num, k );
			printf("%d\n", sorted[pos]);
		}
	}
}

