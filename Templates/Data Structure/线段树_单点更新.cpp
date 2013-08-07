/**
 * @file 线段树_单点更新.cpp
 * @brief   HDU1166，线段树单点更新问题，Insert函数用于插入。
 * 更新的时候直接相当于对于指定位置插入新元素就可以了。
 * @author FinalTheory
 * @version 1.0
 * @date 2013-04-24
 */
#define MAX 50010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	int L, R, Sum;
} Tree[MAX<<2];

void CreateTree( int root, int L, int R )
{
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Sum = 0;
	if ( L == R )
		return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Insert( int root, int pos, int value )
{
	Tree[root].Sum += value;
	if ( Tree[root].L == pos && Tree[root].R == pos )
		return;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos > M )
		Insert( R_son, pos, value );
	else
		Insert( L_son, pos, value );
}

int Query( int root, int L, int R )
{
	if ( L == Tree[root].L && R == Tree[root].R )
		return Tree[root].Sum;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query( L_son, L, R );
	else if ( L > M )
		return Query( R_son, L, R );
	else
		return Query( L_son, L, M ) + Query( R_son, M + 1, R );
}

int main()
{
	int T, N, num, a, b, idx;
	char str[20];
	scanf("%d", &T);
	for ( idx = 1; idx <= T; ++idx )
	{
		printf("Case %d:\n", idx);
		scanf("%d", &N);
		CreateTree( 1, 1, N );
		for ( int i = 0; i < N; ++i )
		{
			scanf( "%d", &num );
			Insert( 1, i + 1, num );
		}
		while (true)
		{
			scanf("%s", str);
			if ( str[0] == 'E' )
				break;
			scanf("%d %d", &a, &b);
			if ( str[0] == 'Q' )
				printf("%d\n", Query( 1, a, b ));
			else if ( str[0] == 'A' )
				Insert( 1, a, b );
			else
				Insert( 1, a, -b );
		}
	}
}

