/**
 * @file POJ_3264.cpp
 * @brief   线段树入门题，由于是初学所以采用比较直观的链表形式。
 * 这道题只包含最基本的建树和查找步骤.
 * 使用C++通过，G++超时，而且相当一部分时间花在IO上面。
 * 这次即便关闭了输入流同步，用cin也还是TLE，这尼玛……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-23
 */
#define MAX 50000
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

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
	int nMin, nMax;	//最小值和最大值
	TMD * p_left, * p_right;	//左右子树指针
	//这里初始化的时候就直接用构造函数了
	TMD()
	{
		p_left = p_right = NULL;
		nMin = INF;
		nMax = -1;
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

void Insert( TMD * root, int num, int pos )
{
	root->nMax = max( num, root->nMax );
	root->nMin = min( num, root->nMin );
	if ( root->L == pos && root->R == pos )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( pos > M )
		Insert( root->p_right, num, pos );
	else
		Insert( root->p_left, num, pos );
}

void Query( TMD * root, int L, int R, int * max_num, int * min_num )
{
	//如果刚好匹配，则直接返回
	if ( root->L == L && root->R == R )
	{
		*max_num = root->nMax;
		*min_num = root->nMin;
		return;
	}
	int M = ( root->L + root->R ) / 2;
	if ( R <= M )
		Query( root->p_left, L, R, max_num, min_num );
	else if ( L > M )
		Query( root->p_right, L, R, max_num, min_num );
	else
	{
		//这里要查询两次，保存其最大值
		//为了代码可读性，这里查询了两次，效率略低
		int max1, max2, min1, min2;
		Query( root->p_left, L, M, &max1, &min1 );
		Query( root->p_right, M + 1, R, &max2, &min2 );
		*max_num = max( max1, max2 );
		*min_num = min( min1, min2 );
	}
}

int main()
{
	int A, B, N, Q, i, num;
	int max_num, min_num;
	TMD * root;
	while ( scanf( "%d %d", &N, &Q ) != EOF )
	{
		//初始化
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		//开始建树
		root = CreateTree( 1, N );
		//插入数据
		for ( i = 1; i <= N; ++i )
		{
			scanf("%d", &num);
			Insert( root, num, i );
		}
		//开始查询
		for ( i = 0; i < Q; ++i )
		{
			scanf( "%d %d", &A, &B );
			Query( root, A, B, &max_num, &min_num );
			printf( "%d\n", max_num - min_num );
		}
	}
}
