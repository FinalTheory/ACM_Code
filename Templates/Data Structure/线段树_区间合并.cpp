#define MAX 80010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

//记录区间左侧、右侧、最大连续可用长度
int lSum[MAX<<2], rSum[MAX<<2], maxSum[MAX<<2];
//记录区间长度、区间标记
int nLen[MAX<<2], Cover[MAX<<2];

void Pushdown( int root )
{
	if ( Cover[root] != -1 )
	{
		Cover[L_son] = Cover[R_son] = Cover[root];
		lSum[L_son] = rSum[L_son] = maxSum[L_son] = ( Cover[L_son] ? 0 : nLen[L_son] );
		lSum[R_son] = rSum[R_son] = maxSum[R_son] = ( Cover[R_son] ? 0 : nLen[R_son] );
		Cover[root] = -1;
	}
}

void Pushup( int root )
{
    //if ( Cover[L_son] == Cover[R_son] ) Cover[root] = Cover[L_son];
    if ( lSum[L_son] == nLen[L_son] ) lSum[root] = nLen[L_son] + lSum[R_son];
    else lSum[root] = lSum[L_son];
    if ( rSum[R_son] == nLen[R_son] ) rSum[root] = nLen[R_son] + rSum[L_son];
    else rSum[root] = rSum[R_son];
    maxSum[root] = rSum[L_son] + lSum[R_son];
    if ( maxSum[L_son] > maxSum[root] ) maxSum[root] = maxSum[L_son];
    if ( maxSum[R_son] > maxSum[root] ) maxSum[root] = maxSum[R_son];
}

void CreateTree( int root, int L, int R )
{
	Cover[root] = 0;
	nLen[root] = R - L + 1;
	lSum[root] = rSum[root] = maxSum[root] = R - L + 1;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Update( int root, int L, int R, int l, int r, int flag )
{
	if ( L == l && R == r ) {
		Cover[root] = flag;
		lSum[root] = rSum[root] = maxSum[root] = flag ? 0 : nLen[root];
		return;
	}
	Pushdown(root);
	int M = ( L + R ) / 2;
	if ( l > M ) {
		Update( R_son, M + 1, R, l, r, flag );
	}
	else if ( r <= M ) {
		Update( L_son, L, M, l, r, flag );
	}
	else {
		Update( L_son, L, M, l, M, flag );
		Update( R_son, M + 1, R, M + 1, r, flag );
	}
	Pushup( root );
}

int Query( int root, int L, int R, int w )
{
 	if ( L == R ) return L;
 	Pushdown(root);
 	int M = ( L + R ) >> 1;
	if ( maxSum[L_son] >= w )
		return Query(L_son, L, M, w);
	else if ( rSum[L_son] + lSum[R_son] >= w )
		return M - rSum[L_son] + 1;
	else
		return Query(R_son, M + 1, R, w);
}

int main()
{
	int N, M, C, D, X;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		CreateTree( 1, 1, N );
		while ( M-- )
		{
			scanf("%d", &C);
			if ( C == 1 ) {
				scanf("%d", &D);
				if ( maxSum[1] < D ) puts("0");
				else {
                    int r = Query(1, 1, N, D);
                    printf("%d\n", r);
                    Update( 1, 1, N, r, r + D - 1, 1 );
				}
			} else {
				scanf("%d %d", &X, &D);
				Update( 1, 1, N, X, X + D - 1, 0 );
 			}
		}
	}
}
