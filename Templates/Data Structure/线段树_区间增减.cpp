#define MAX 100010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

LL nSum[MAX<<2], nInc[MAX<<2];
int Len[MAX<<2];

inline void PushUp( int root )
{
	nSum[root] = nSum[L_son] + nSum[R_son];
}

inline void PushDown( int root )
{
	if ( nInc[root] != 0 )
	{
		nInc[L_son] += nInc[root];
		nInc[R_son] += nInc[root];
		nSum[L_son] += nInc[root] * Len[L_son];
		nSum[R_son] += nInc[root] * Len[R_son];
		nInc[root] = 0;
	}
}

void CreateTree( int root, int L, int R )
{
	nInc[root] = 0;
	Len[root] = R - L + 1;
	if (L == R) {
		scanf("%I64d", &nSum[root]);
		return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
	PushUp(root);
}


void Update( int root, int L, int R, int l, int r, int num )
{
	if ( l == L && r == R )
	{
		nInc[root] += num;
		nSum[root] += (LL)num * Len[root];
		return;
	}
	PushDown(root);
	int M = ( L + R ) >> 1;
	if ( r <= M )
		Update( L_son, L, M, l, r, num );
	else if ( l > M )
		Update( R_son, M + 1, R, l, r, num );
	else
	{
		Update( L_son, L, M, l, M, num );
		Update( R_son, M + 1, R, M + 1, r, num );
	}
	PushUp(root);
}

LL Query( int root, int L, int R, int l, int r )
{
	if ( L == l && R == r )
		return nSum[root];
	PushDown(root);
	int M = ( L + R ) >> 1;
	if ( r <= M )
		return Query( L_son, L, M, l, r );
	else if ( l > M )
		return Query( R_son, M + 1, R, l, r );
	else
		return Query( L_son, L, M, l, M ) + Query( R_son, M + 1, R, M + 1, r );
}

int main()
{
	int N, Q;
	char str[5];
	while ( scanf("%d %d", &N, &Q) != EOF )
	{
		CreateTree( 1, 1, N );
		int a, b, c;
		for ( int i = 0; i < Q; ++i )
		{
			scanf("%s %d %d", str, &a, &b);
			if ( str[0] == 'C' )
			{
				scanf("%d", &c);
				Update( 1, 1, N, a, b, c );
			}
			else
				printf("%I64d\n", Query( 1, 1, N, a, b ));
		}
	}
}
