#define CLR(arr,val) memset(arr,val,sizeof(arr))
const double eps = 1e-4;
#define MAX_v 210
#define MAX_e 210 * 210 * 2
int LOW[MAX_v], DFN[MAX_v];
bool Instack[MAX_v];
int Belong[MAX_v];
int TimeStamp, ans;
int p_edges;
int _hash[MAX_v];
struct Point
{
	double x, y;
} points[MAX_v];
struct TMD
{
	int from, to, next;
} edges[MAX_e];
struct NND
{
	int top;
	int elem[MAX_v];
} stk;
int head[MAX_v];
void Add_Edge( int _u, int _v )
{
	edges[p_edges].from = _u; edges[p_edges].to = _v;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
}
void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	stk.elem[++stk.top] = u;
	Instack[u] = true;
	for ( int e = head[u]; e != -1; e = edges[e].next )
	{
		v = edges[e].to;
		if ( !DFN[v] )
		{
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		}
		else if ( Instack[v] )
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] )
	{
		++ans;
		do
		{
			v = stk.elem[stk.top--];
			Instack[v] = false;
			Belong[v] = ans;
		} while ( v != u );
	}
}
void Init()
{
	ans = TimeStamp = p_edges = 0;
	stk.top = -1;
	CLR( DFN, 0 ); CLR( Instack, 0 ); CLR( head, -1 );
}
inline double dist( Point a, Point b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}
int N;
void Solve( double low, double high )
{
	double mid;
	while ( high - low > eps )
	{
		mid = ( high + low ) / 2.;
		Init();
		//重新构图
		for ( int i = 0; i < 2 * N; ++i )
			for ( int j = i + 1; j < 2 * N; ++j ) if ( dist( points[i], points[j] ) < mid )
			{
				if ( i != ( j ^ 1 ) )
					Add_Edge( i, j ^ 1 );
				if ( j != ( i ^ 1 ) )
					Add_Edge( j, i ^ 1 );
			}
		for ( int i = 0; i < 2 * N; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < N; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if (!flag)
			high = mid;
		else
			low = mid;
	}
	printf("%.2lf\n", mid / 2.);
}

int main()
{
	while ( scanf("%d", &N) != EOF )
	{
		Init();
		for ( int i = 0; i < 2 * N; i += 2 )
			scanf("%lf %lf %lf %lf", &points[i].x, &points[i].y, &points[i+1].x, &points[i+1].y);
		Solve( 0. - eps, 20000. * sqrt(2.) + eps );
	}
}

