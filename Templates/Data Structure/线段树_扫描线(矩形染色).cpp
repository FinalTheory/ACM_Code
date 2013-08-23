/**
 * @file HDU_4419.cpp
 * @brief   扫描线模版题
 * @hint    为记录矩形边的结构体创建一个set方法，用于批量读入数据并初始化；
 *	    所有离散点排序后，使用STL的unique函数对坐标点进行去重；
 *	    染色时，x坐标相同的点，需要都插入之后才能计算面积，否则答案是错误的；
 *	    排序时，可能存在边重合的情况，这时左边比右边要优先，写排序函数的时候需要注意。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-23
 */
#define L_son root << 1
#define R_son root << 1 | 1
#define MAX 30010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long LL;
struct NND
{
	int L, R, calc[8], C1, C2, C4;
} Tree[MAX<<2];
struct TMD
{
	int high, low, x;
	int flag;
	char color;
	void set( int _low, int _high, int _x, int _flag, char _col )
	{
		x = _x;
		low = _low;
		high = _high;
		flag = _flag;
		color = _col;
	}
} lines[MAX];
int height[MAX];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].C4 = Tree[root].C2 = Tree[root].C1 = 0;
	CLR( Tree[root].calc, 0 );
	Tree[root].calc[0] =  height[R] - height[L - 1];
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}
bool fuck( const TMD & A,  const TMD & B )
{
	if ( A.x != B.x )
		return A.x < B.x;
	else
		return A.flag > B.flag;
}
void PushUp( int root )
{
	int Cover = 0;
	if ( Tree[root].C4 ) Cover |= 4;
	if ( Tree[root].C2 ) Cover |= 2;
	if ( Tree[root].C1 ) Cover |= 1;
	CLR( Tree[root].calc, 0 );
	if ( Tree[root].R == Tree[root].L ) {
		Tree[root].calc[Cover] = height[Tree[root].R] - height[Tree[root].L - 1];
	} else if ( Cover ) {
		for ( int i = 0; i < 8; ++i )
			Tree[root].calc[i|Cover] += Tree[L_son].calc[i] + Tree[R_son].calc[i];
	} else {
		for ( int i = 0; i < 8; ++i )
			Tree[root].calc[i] = Tree[L_son].calc[i] + Tree[R_son].calc[i];
	}
}
void Insert( int root, int L, int R, int flag, int color )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		if ( color == 4 ) {
			Tree[root].C4 += flag;
		} else if ( color == 2 ) {
			Tree[root].C2 += flag;
		} else if ( color == 1 ) {
			Tree[root].C1 += flag;
		}
		PushUp(root);
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( R <= M ) {
		Insert( L_son, L, R, flag, color );
	} else if ( L > M ) {
		Insert( R_son, L, R, flag, color );
	} else {
		Insert( L_son, L, M, flag, color );
		Insert( R_son, M + 1, R, flag, color );
	}
	PushUp(root);
}
int _hash[128];
int main()
{
	int n, p_lines, p_height, j, index = 1, T;
	int x1, y1, x2, y2;
	_hash['R'] = 4; _hash['G'] = 2; _hash['B'] = 1;
	LL sum[8], len;
	char co[4];
	scanf("%d", &T);
	for ( index = 1; index <= T; ++index )
	{
		CLR( sum, 0 );
		p_lines = p_height = 0;
		scanf("%d", &n);
		for ( int i = 0; i < n; ++i )
		{
			scanf("%s %d %d %d %d", co, &x1, &y1, &x2, &y2);
			height[p_height++] = y1; height[p_height++] = y2;
			lines[p_lines++].set( y1, y2, x1,  1, co[0] );
			lines[p_lines++].set( y1, y2, x2, -1, co[0] );
		}
		sort( height, height + p_height );
		sort( lines, lines + p_lines, fuck );
		int nn = unique( height, height + p_height ) - height;
		CreateTree( 1, 1, nn );
		int i = 0, left, right;
		while ( i < p_lines )
		{
			int j = i;
			while ( j < p_lines && lines[j].x == lines[i].x )
			{
				left = lower_bound( height, height + nn, lines[j].low ) - height + 1;
				right = lower_bound( height, height + nn, lines[j].high ) - height;
				Insert( 1, left, right, lines[j].flag, _hash[lines[j].color] );
				++j;
			}
			if ( j == p_lines )
				len = 0;
			else
				len = lines[j].x - lines[i].x;
			for ( int k = 1; k < 8; ++k )
				sum[k] += (LL)Tree[1].calc[k] * len;
			i = j;
		}
		printf("Case %d:\n", index);
		printf("%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n", sum[4], sum[2], sum[1], sum[6], sum[5], sum[3], sum[7]);
	}
}
