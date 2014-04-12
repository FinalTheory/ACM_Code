#define MAX 50010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

int Sum[MAX<<2];

inline void PushUp( int root )
{
    Sum[root] = Sum[L_son] + Sum[R_son];
}

void CreateTree( int root, int L, int R )
{
	Sum[root] = 0;
	if ( L == R ) {
        scanf("%d", &Sum[root]);
        return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
	PushUp(root);
}

void Insert( int root, int L, int R, int pos, int value )
{
	if ( L == pos && R == pos ) {
        Sum[root] += value;
        return;
    }
	int M = ( L + R ) >> 1;
	if ( pos > M )
		Insert( R_son, M + 1, R, pos, value );
	else
		Insert( L_son, L, M, pos, value );
    PushUp(root);
}

int Query( int root, int L, int R, int l, int r )
{
	if ( l == L && r == R )
		return Sum[root];
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
	int T, N, a, b, idx;
	char str[20];
	scanf("%d", &T);
	for ( idx = 1; idx <= T; ++idx )
	{
		printf("Case %d:\n", idx);
		scanf("%d", &N);
		CreateTree( 1, 1, N );
		while (true)
		{
			scanf("%s", str);
			if ( str[0] == 'E' )
				break;
			scanf("%d %d", &a, &b);
			if ( str[0] == 'Q' )
				printf("%d\n", Query( 1, 1, N, a, b ));
			else if ( str[0] == 'A' )
				Insert( 1, 1, N, a, b );
			else
				Insert( 1, 1, N, a, -b );
		}
	}
}

