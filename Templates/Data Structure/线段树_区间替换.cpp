/**
 * @file HDU_1698.cpp
 * @brief   线段树区间替换问题，具体看下面注释；
 * 核心思路就是，每次更新的时候先前的所有信息都应该保留；
 * 这里的情况就是，每次区间完全匹配的时候要将区间信息更新上去，
 * 每次不完全匹配的时候把区间信息更新下去然后再分开处理。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-02
 */
#define MAX 100010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
struct TMD
{
	int L, R, nSum, nNew;
}Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nSum = R - L + 1;
	Tree[root].nNew = 0;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}
//将子树的信息更新到父亲，一直更新到树根
void PushUp( int root )
{
	if ( root )
	{
		Tree[root].nSum = Tree[L_son].nSum + Tree[R_son].nSum;
		PushUp(Father);
	}
}
//将当前这一节点的信息更新到两个子树上，然后清空当前节点。（注意这个时候当前节点的信息已经更新上去了）
void PushDown( int root )
{
	if ( Tree[root].nNew )
	{
		Tree[L_son].nNew = Tree[R_son].nNew = Tree[root].nNew;
		Tree[L_son].nSum = ( Tree[L_son].R - Tree[L_son].L + 1 ) * Tree[L_son].nNew;
		Tree[R_son].nSum = ( Tree[R_son].R - Tree[R_son].L + 1 ) * Tree[R_son].nNew;
		Tree[root].nNew = 0;
	}
	
}
//这里是处理更新操作
void Update( int root, int L, int R, int Z )
{
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		//如果区间匹配，就把这个区间的信息强制更新，然后刷新上面的信息
		Tree[root].nNew = Z;
		Tree[root].nSum = ( R - L + 1 ) * Z;
		PushUp( Father );
		return;
	}
	//如果区间不匹配，就直接把这个区间的信息更新到下面两个子树去，然后再分别处理下面。
	//这样便保证了每次Update时先前的所有信息都已经被更新到了上面并且保留到了下面。
	PushDown( root );
	if ( L > M )
	{
		Update( R_son, L, R, Z );
	}
	else if ( R <= M )
	{
		Update( L_son, L, R, Z );
	}
	else
	{
		Update( L_son, L, M, Z );
		Update( R_son, M + 1, R, Z );
	}
}
int main()
{
	int T, i, k, N, Q, X, Y, Z;
	scanf("%d", &T);
	for ( k = 1; k <= T; ++k )
	{
		scanf("%d", &N);
		CreateTree( 1, 1, N );
		scanf("%d", &Q);
		for ( i = 0; i < Q; ++i )
		{
			scanf("%d %d %d", &X, &Y, &Z);
			Update( 1, X, Y, Z );
		}
		printf( "Case %d: The total value of the hook is %d.\n", k, Tree[1].nSum );
	}
}
