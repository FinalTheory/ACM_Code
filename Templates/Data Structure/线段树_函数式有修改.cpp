/**
 * @file ZOJ_2112.cpp
 * @brief   函数式线段树有修改版本，利用树状数组维护前缀和。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-05
 */
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int MAX = 50010;
const int MAX_q = 10010;
const int INF = 0x3f3f3f3f;
int nums[MAX], all_val[MAX + MAX_q], root[MAX<<1], prefix_l[100], prefix_r[100];
int cnt, p[2];
struct
{
	int a, b, c;
	char type;
} Querys[MAX_q];
struct TMD
{
	int sum, L_son, R_son;
} Tree[MAX*40];
inline int Lowbit( int x )
{
	return x & (-x);
}
inline int CreateNode( int _sum, int _L_son, int _R_son )
{
	int idx = ++cnt;
	Tree[idx].sum = _sum;
	Tree[idx].L_son = _L_son;
	Tree[idx].R_son = _R_son;
	return idx;
}
void Build( int & root, int pre_rt, int pos, int L, int R )
{
	root = CreateNode( Tree[pre_rt].sum + 1, Tree[pre_rt].L_son, Tree[pre_rt].R_son );
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M )
		Build( Tree[root].L_son, Tree[pre_rt].L_son, pos, L, M );
	else
		Build( Tree[root].R_son, Tree[pre_rt].R_son, pos, M + 1, R );
}
void Insert( int & root, int pos, int L, int R, int val )
{
	//如果这颗子树没有被建立，就新建一个节点
	if ( !root )
		root = CreateNode( 0, 0, 0 );
	Tree[root].sum += val;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M )
		Insert( Tree[root].L_son, pos, L, M, val );
	else
		Insert( Tree[root].R_son, pos, M + 1, R, val );
}
int Query( int L, int R, int K )
{
	if ( L == R ) return L;
	int M = ( L + R ) >> 1, sum = 0;
	//计算前缀和
	for ( int i = 0; i < p[0]; i++ ) sum += Tree[Tree[prefix_r[i]].L_son].sum;
	for ( int i = 0; i < p[1]; i++ ) sum -= Tree[Tree[prefix_l[i]].L_son].sum;
	if ( K <= sum ) {
		//更新用于计算前缀和的子树根节点编号
		for ( int i = 0; i < p[0]; i++ ) prefix_r[i] = Tree[prefix_r[i]].L_son;
		for ( int i = 0; i < p[1]; i++ ) prefix_l[i] = Tree[prefix_l[i]].L_son;
		return Query( L, M, K );
	} else {
		for ( int i = 0; i < p[0]; i++ ) prefix_r[i] = Tree[prefix_r[i]].R_son;
		for ( int i = 0; i < p[1]; i++ ) prefix_l[i] = Tree[prefix_l[i]].R_son;
		return Query( M + 1, R, K - sum );
	}
}
int main()
{
	int n, m, p_val, num;
	char str[5];
	int T; scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &n, &m);
		cnt = 0; p_val = n + 1;
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &nums[i]);
			all_val[i] = nums[i];
		}
		//读入所有修改并离散化
		for ( int i = 0; i < m; ++i )
		{
			scanf("%s %d %d", str, &Querys[i].a, &Querys[i].b);
			Querys[i].type = str[0];
			if ( str[0] == 'Q' ) scanf("%d", &Querys[i].c);
			else all_val[p_val++] = Querys[i].b;
		}
		sort( all_val + 1, all_val + p_val );
		num = unique( all_val + 1, all_val + p_val ) - ( all_val + 1 );
		//这里直接将初始数字序列映射到离散化后的值域上
		for ( int i = 1; i <= n; ++i )
			nums[i] = lower_bound( all_val + 1, all_val + num + 1, nums[i] ) - all_val;
		for ( int i = 1; i <= n; ++i )
			Build( root[i + n], root[i - 1 + n], nums[i], 1, num );
		for ( int i = 0; i < m; ++i )
			if ( Querys[i].type == 'Q' ) {
				p[0] = p[1] = 1;
				//初始化用于计算前缀和的线段树根节点
				prefix_r[0] = root[Querys[i].b + n];
				prefix_l[0] = root[Querys[i].a - 1 == 0 ? 0 : Querys[i].a - 1 + n];
				for ( int arr = Querys[i].b; arr; arr -= Lowbit(arr) ) prefix_r[p[0]++] = root[arr];
				for ( int arr = Querys[i].a - 1; arr; arr -= Lowbit(arr) ) prefix_l[p[1]++] = root[arr];
				printf("%d\n", all_val[Query( 1, num, Querys[i].c )]);
			} else {
				for ( int j = Querys[i].a; j <= n; j += Lowbit(j) ) Insert( root[j], nums[Querys[i].a], 1, num, -1 );
				//将修改的结果映射到值域，并更新前缀和
				nums[Querys[i].a] = lower_bound( all_val + 1, all_val + num + 1, Querys[i].b ) - all_val;
				for ( int j = Querys[i].a; j <= n; j += Lowbit(j) ) Insert( root[j], nums[Querys[i].a], 1, num, 1 );
			}
		CLR( root, 0 );
	}
}
