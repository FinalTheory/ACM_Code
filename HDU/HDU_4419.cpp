/**
 * @file HDU_4419.cpp
 * @brief   扫描线模版题
 * @hint    为记录矩形边的结构体创建一个set方法，用于批量读入并初始化；
 *	    所有离散点排序后，使用STL的unique函数对点进行去重；
 *	    染色时，x坐标相同的点，需要都插入之后才能计算面积；
 *	    排序时，可能存在边重合的情况，这时左边比右边要优先。
 * @feeling 这题跪烂了，不想说什么了，HDU的长整型简直是神坑啊有木有！！！
 *	    首先思路很重要，要注意用什么方法来记录并更新颜色，下面的注释里有。
 *	    后来折腾了那么半天，全是跪在这个垃圾编译器上面了！
 *	    还有就是最后处理插入边的边界时要特别小心，如果超出了，那么计算长度是零！
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
	Tree[root].calc[0] =  height[R + 1] - height[L];
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
	//这种记录信息的方法，可以使得两条边对称地完成更新，并且不用Pushdown函数
	if ( Tree[root].C4 ) Cover |= 4;
	if ( Tree[root].C2 ) Cover |= 2;
	if ( Tree[root].C1 ) Cover |= 1;
	CLR( Tree[root].calc, 0 );
	if ( Tree[root].R == Tree[root].L ) {
		Tree[root].calc[Cover] = height[Tree[root].R + 1] - height[Tree[root].L];
	} else if ( Cover ) {
		for ( int i = 0; i < 8; ++i )
			//这里的或运算使得叶子节点的颜色信息能被更新到父亲节点的正确位置上面。
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
int BinSearch( int Key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( height[mid] == Key )
			return mid;
		else if ( height[mid] > Key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}
int _hash[128];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, p_lines, p_height, j, index = 1, T;
	int x1, y1, x2, y2;
	_hash['R'] = 4; _hash['G'] = 2; _hash['B'] = 1;
	LL sum[8], len;
	char co[4];
	scanf("%d", &T);
	for ( index = 1; index <= T; ++index )
	{
		CLR( sum, 0 );
		p_lines = 0;
		p_height = 1;
		scanf("%d", &n);
		for ( int i = 0; i < n; ++i )
		{
			scanf("%s %d %d %d %d", co, &x1, &y1, &x2, &y2);
			height[p_height++] = y1; height[p_height++] = y2;
			lines[p_lines++].set( y1, y2, x1,  1, co[0] );
			lines[p_lines++].set( y1, y2, x2, -1, co[0] );
		}
		sort( height + 1, height + p_height );
		sort( lines, lines + p_lines, fuck );
		int nn = unique( height + 1, height + p_height ) - height - 1;
		CreateTree( 1, 1, nn );
		int i = 0, left, right;
		while ( i < p_lines )
		{
			int j = i;
			//注意这里的边界判断
			while ( j < p_lines && lines[j].x == lines[i].x )
			{
				left = BinSearch( lines[j].low, 1, nn );
				right = BinSearch( lines[j].high, 1, nn ) - 1;
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
		//这里是神坑啊有木有！
		printf("%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n", sum[4], sum[2], sum[1], sum[6], sum[5], sum[3], sum[7]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
