/**
 * @file POJ_2104.cpp
 * @brief   划分树模版
 * @author FinalTheory
 * @version 1.0
 * @date 2013-08-05
 */
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;

int nums[MAX], pos_new[MAX], p[MAX], tmp[MAX], num_left[20][MAX];

struct TMD
{
	int L, R;
	int len(){return R - L + 1;}
	int Mid(){return ( L + R ) >> 1;}
} Tree[MAX<<2];

bool fuck( int a, int b )
{
	if ( nums[a] != nums[b] )
		return nums[a] < nums[b];
	else
		return a < b;
}

void CreateTree( int root, int L, int R, int depth )
{
	Tree[root].L = L;
	Tree[root].R = R;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	int count = 0, i = L, j = M + 1;
	//pos_new数组记录每个元素在排序之后的新位置，这个数组中的元素被划分到左右两边；
	//相当于模拟了在已知每个元素最终位置的情况下，对数组进行快速排序的过程，而不管元素实际上是什么。
	//其实划分树的核心也就是要记录这个划分情况，在后面的查询过程中会用到，这里采用了非常漂亮的实现。
	//划分后的范围为[L, M]， [M + 1, R]，这样相对位置仍然不变，再递归下去跟先前就是完全等价的子问题。
	//num_left数组记录当前层每个元素在自己之前（包括自己）被划分到左子树的元素个数。
	for ( int k = L; k <= R; ++k )
		if ( pos_new[k] <= M )
		{
			tmp[i++] = pos_new[k];
			num_left[depth][k] = ++count;
		}
		else
		{
			tmp[j++] = pos_new[k];
			num_left[depth][k] = count;
		}
	//更新一下各个元素在这次划分之后的位置
	for ( int k = L; k <= R; ++k )
		pos_new[k] = tmp[k];
	CreateTree( L_son, L, M, depth + 1 );
	CreateTree( R_son, M + 1, R, depth + 1 );
}

int Query( int root, int L, int R, int depth, int k )
{
	//如果查询到了叶子，就返回这个元素
	//p数组记录了排序后的每个元素是原先数组中的第几个元素
	if ( Tree[root].L == Tree[root].R )
		return nums[p[Tree[root].L]];
	int left_LR, left_L;
	//left_L表示区间[Tree[root].L, L)中有多少个被划分到左边的元素
	if ( L == Tree[root].L )
		left_L = 0;
	else
		left_L = num_left[depth][L - 1];
	//left_LR表示区间[L, R]中有多少个被划分到左边的元素
	left_LR = num_left[depth][R] - left_L;
	int L_new, R_new;
	//这一部分的边界处理要特别小心
	//如果有大于等于k个元素都已经被划分到左子树，就应该在左子树递归查找
	if ( left_LR >= k )
	{
		//这里是区间修改，新的查询区间应该是从上一层的[L, R]进入左子树的元素
		L_new = Tree[root].L + left_L;
		R_new = Tree[root].L + left_L + left_LR - 1;
		return Query( L_son, L_new, R_new, depth + 1, k );
	}
	else
	{
		int M = ( Tree[root].L + Tree[root].R ) >> 1;
		//计算区间[Tree[root].L, L)中有多少被划分到右子树
		int right_L = L - Tree[root].L - left_L;
		//计算区间[L, R]中有多少被划分到右子树
		int right_LR = R - L + 1 - left_LR;
		//同理，这里新的查询区间是从上一层的[L, R]（即待查询区间）进入右子树的元素
		L_new = M + right_L + 1;
		R_new = M + right_L + right_LR;
		//因为已经有left_LR个元素进入了左子树，所以要查询的就变为第k - left_LR大的元素
		return Query( R_son, L_new, R_new, depth + 1, k - left_LR );
	}
}

int main()
{
	int n, m;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &nums[i]);
			p[i] = i;
		}
		sort( p + 1, p + n + 1, fuck );
		//这一步是个很巧妙的Trick
		//用于生成每个位置的元素在排序之后的位置
		for ( int i = 1; i <= n; ++i )
			pos_new[p[i]] = i;
		CreateTree( 1, 1, n, 1 );
		int a, b, k;
		while ( m-- )
		{
			scanf("%d %d %d", &a, &b, &k);
			printf("%d\n", Query( 1, a, b, 1, k ));
		}
	}
}
