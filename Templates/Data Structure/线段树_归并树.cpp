/**
 * @file 线段树_归并树.cpp
 * @brief  归并树模版
 * 首先考虑朴素思路，把序列进行排序并记录各个元素的初始位置，然后每次询问，都把序列扫一遍；
 * 用一个变量c表示已经扫到了待查询区间的第c小的数，因为现在的序列已经是有序的了，
 * 所以如果找到一个元素属于待查询区间，就可以增加c，这样直到c == k时结束。
 * 上述快排做法的正确性显然，但是效率非常慢。为了提升查询速度，我们引入二分思想。
 * 如果对于有序序列中的每一个元素，我们有一种查询方法能够知道它是待查询区间中的第几大元素，
 * 那么就可以用log(N)次查询来找出第k大元素，这就是最外层的第一层二分。
 * 下面引入归并树，每次查询的任意区间，一定可以被树上的某些区间的并来表示，这是线段树的基本功能；
 * 所以将任意一个待查询区间拆分成这些区间的并，复杂度同样是log(N)，这里是第二层二分；
 * 最后，由于归并树的每个区间中的元素都是有序的，在这些待查询区间中找出待查询元素是第几大元素，
 * 也是利用了一次二分查找，其复杂度同样是log(N)，这就是第三次二分。
 * 最后，每次询问的复杂度就是log(N)^3，归并树操作的总复杂度为M*log(N)^3。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-07
 */
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define MAX 100010
using namespace std;

int a[20][MAX], nums[MAX];

struct TMD
{
	int L, R;
	int len(){return R - L + 1;}
	int Mid(){return ( L + R ) >> 1;}
} Tree[MAX<<2];

void CreateTree( int root, int L, int R, int depth )
{
	Tree[root].L = L;
	Tree[root].R = R;
	if ( L == R )
	{
		a[depth][L] = nums[L];
		return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M, depth + 1 );
	CreateTree( R_son, M + 1, R, depth + 1 );
	int i = L, j = M + 1, k = L;
	//将下一层的元素归并到当前层
	while ( i <= M && j <= R )
	{
		if ( a[depth + 1][i] < a[depth + 1][j] )
			a[depth][k++] = a[depth + 1][i++];
		else
			a[depth][k++] = a[depth + 1][j++];
	}
	//至少有一半已经是空的，所以下面这两句只执行一句，不用考虑顺序
	while ( i <= M ) a[depth][k++] = a[depth + 1][i++];
	while ( j <= R ) a[depth][k++] = a[depth + 1][j++];
}
//这就是第三层二分查找了，是在当前节点的有序元素中找num是第几大
int find( int low, int high, int num, int depth )
{
	if ( a[depth][low]  > num ) return 0;
	if ( a[depth][high] < num ) return high - low + 1;
	int L = low, R = high;
	while ( L <= R )
	{
		int M = ( L + R ) >> 1;
		if ( a[depth][M] >= num )
			R = M - 1;
		else
			L = M + 1;
	}
	return L - low;
}
//这里是第二层二分查找，即线段树本身的询问操作
int Query( int root, int L, int R, int num, int depth )
{
	//如果待查询区间正好等于当前节点的区间，就在这个区间中查找num是第几个元素
	if ( L == Tree[root].L && R == Tree[root].R )
		return find( Tree[root].L, Tree[root].R, num, depth );
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	int res = 0;
	if ( R <= M )
		return Query( L_son, L, R, num, depth + 1 );
	else if ( L > M )
		return Query( R_son, L, R, num, depth + 1 );
	else
		return Query( L_son, L, M, num, depth + 1 ) + Query( R_son, M + 1, R, num, depth + 1 );
}

int main()
{
	int n, m;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		for ( int i = 1; i <= n; ++i )
			scanf("%d", &nums[i]);
		CreateTree( 1, 1, n, 1 );
		int x, y, k;
		while ( m-- )
		{
			scanf("%d %d %d", &x, &y, &k);
			int L = 1, R = n;
			//这里是最外层的二分查找，对排序后的序列二分，求出它在待查询区间中是第几小
			//当查询到某个值，使得它在待查询区间中恰好为第k小时，即为所求的答案。
			while ( L <= R )
			{
				int M = ( L + R ) >> 1;
				int pos = Query( 1, x, y, a[1][M], 1 ) + 1;
				if ( pos <= k )
					L = M + 1;
				else
					R = M - 1;
			}
			printf("%d\n", a[1][R]);
		}
	}
}
