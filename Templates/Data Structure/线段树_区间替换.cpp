#define MAX 100010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

int nSum[MAX<<2], nNew[MAX<<2], nLen[MAX<<2];

void CreateTree( int root, int L, int R )
{
	nSum[root] = R - L + 1;
	nLen[root] = R - L + 1;
	nNew[root]= 0;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

inline void PushUp( int root )
{
    nSum[root] = nSum[L_son] + nSum[R_son];
}

inline void PushDown( int root )
{
	if ( nNew[root] )
	{
		nNew[L_son] = nNew[R_son] = nNew[root];
		nSum[L_son] = nLen[L_son] * nNew[L_son];
		nSum[R_son] = nLen[R_son] * nNew[R_son];
		nNew[root] = 0;
	}

}

void Update( int root, int L, int R, int l, int r, int Z )
{
	if ( l == L && r == R )
	{
		nNew[root] = Z;
		nSum[root] = ( R - L + 1 ) * Z;
		return;
	}
	PushDown( root );
	int M = ( L + R ) >> 1;
	if ( l > M )
	{
		Update( R_son, M + 1, R, l, r, Z );
	}
	else if ( r <= M )
	{
		Update( L_son, L, M, l, r, Z );
	}
	else
	{
		Update( L_son, L, M, l, M, Z );
		Update( R_son, M + 1, R, M + 1, r, Z );
	}
	PushUp(root);
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
			Update( 1, 1, N, X, Y, Z );
		}
		printf( "Case %d: The total value of the hook is %d.\n", k, nSum[1] );
	}
}
