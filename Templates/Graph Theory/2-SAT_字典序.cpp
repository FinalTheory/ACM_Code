#define MAX_v 16010
#define MAX_e 40010
int col[MAX_v];
struct TMD
{
	int from, to, next;
} edges[MAX_e];
int p_edges, head[MAX_v];
void Add_Edge( int _u, int _v )
{
	edges[p_edges].from = _u; edges[p_edges].to = _v;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
}
void Init()
{
	CLR( col, 0 );
	CLR( head, -1 );
	p_edges = 0;
}
int ans[MAX_v], p_ans;
bool DFS( int u )
{
	if ( col[u] == 1 ) return true;
	if ( col[u] == 2 ) return false;
	col[u] = 1;
	col[u ^ 1] = 2;
	ans[p_ans++] = u;
	for ( int e = head[u]; e != -1; e = edges[e].next ) {
		int v = edges[e].to;
		if ( !DFS(v) ) return false;
	}
	return true;
}
int n, m;
bool Solve()
{
	for ( int i = 0; i < 2 * n; ++i ) {
		if ( col[i] ) continue;
		p_ans = 0;
		if ( !DFS(i) ) {
			for ( int j = 0; j < p_ans; ++j ) {
				col[ans[j] ^ 1] = 0;
				col[ans[j]] = 0;
			}
			p_ans = 0;
			if ( !DFS(i ^ 1) )
				return false;
		}
	}
	return true;
}
int main()
{
	int a, b;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		Init();
		for ( int i = 0; i < m; ++i ) {
			scanf("%d %d", &a, &b);
			a--; b--;
			Add_Edge( a, b ^ 1 );
			Add_Edge( b, a ^ 1 );
		}
		if ( Solve() ) {
			for ( int i = 0; i < 2 * n; ++i ) if ( col[i] == 1 )
				printf("%d\n", i + 1);
		} else {
			puts("NIE");
		}
	}
}

