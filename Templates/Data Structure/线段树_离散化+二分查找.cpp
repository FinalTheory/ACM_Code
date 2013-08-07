/**
 * @file POJ_2528.cpp
 * @brief   线段树离散化。需要注意的是查询的时候，
 * 只有发现某个区间被同一张海报覆盖才把它的信息更新下去。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-03
 */
#define MAX 20010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
int L[MAX], R[MAX], sum, pointer, Buffer[MAX<<1], map[MAX<<1];
char flags[MAX];

struct TMD
{
	int L, R, nType;
	//记录这个区间是否被同一张海报所覆盖
	bool is_FullFilled;
}Tree[MAX<<3];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	//初始化为零表示这是墙
	Tree[root].nType = 0;
	//这里相当于被墙面完全覆盖
	Tree[root].is_FullFilled = true;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void PushDown( int root )
{
	Tree[L_son].is_FullFilled = 1;
	Tree[R_son].is_FullFilled = 1;
	Tree[L_son].nType = Tree[root].nType;
	Tree[R_son].nType = Tree[root].nType;
}

void Insert( int root, int L, int R, int Type )
{
	if ( L == Tree[root].L && R == Tree[root].R )
	{
		Tree[root].is_FullFilled = 1;
		Tree[root].nType = Type;
		return;
	}
	//如果当前这条线段正好是被一张海报覆盖的，就把信息更新下去，然后清空当前的信息
	if ( Tree[root].is_FullFilled == 1 )
	{
		PushDown( root );
		Tree[root].is_FullFilled = 0;
	}	
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
	{
		Insert( L_son, L, R, Type );
	}
	else if ( L > M )
	{
		Insert( R_son, L, R, Type );
	}
	else
	{
		Insert( L_son, L, M, Type );
		Insert( R_son, M + 1, R, Type );
	}
}

void Query( int root, int L, int R )
{
	//查询的时候，如果查询范围刚好匹配，并且这个区间只被一张海报覆盖，就准备更新求和。
	//如果不是的话，就继续递归查询，反正只查询一次，哪怕递归到根节点也没什么。
	if ( L == Tree[root].L && R == Tree[root].R && Tree[root].is_FullFilled )
	{
		if ( !flags[Tree[root].nType] )
		{
			sum++;
			flags[Tree[root].nType] = 1;
		}
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	Query( L_son, L, M );
	Query( R_son, M + 1, R );
}
//这里是二分查找，千万注意写法
int Search( int key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( key < map[mid] )
			high = mid - 1;
		else if ( key > map[mid] )
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int c, n, i, prev;
	scanf( "%d", &c );
	while ( c-- )
	{
		
		CLR(flags, 0);
		scanf( "%d", &n );
		pointer = 0;
		for ( i = 1; i <= n; ++i )
		{
			scanf("%d %d", &L[i], &R[i]);
			Buffer[pointer++] = L[i];
			Buffer[pointer++] = R[i];
		}
		//排序后准备将所有点映射到1~n上面
		sort( Buffer, Buffer + 2 * n );
		prev = map[1] = Buffer[0];
		for ( i = 1, pointer = 2; i < 2 * n; ++i )
			if ( Buffer[i] != Buffer[i - 1] )
			{
				//离散化处理的时候注意，如果两点不相连，就在中间再插入一个！
				//反正这样最多也就是增加一倍的点数。
				if ( Buffer[i] - prev > 1 )
					map[pointer++] = ( Buffer[i] + prev ) >> 1;
				map[pointer++] = Buffer[i];
				prev = Buffer[i];
			}
		//对所有点进行离散化后建立了映射，一共有pointer-1个点
		CreateTree( 1, 1, pointer - 1 );
		int left, right;
		int type = 1;
		for ( i = 1; i <= n; ++i )
		{
			//数组是有序的，所以二分查找出的位置即为那个点对应的映射
			left = Search( L[i], 1, pointer - 1 );
			right = Search( R[i], 1, pointer - 1 );
			Insert( 1, left, right, type++ );
		}
		sum = 0; flags[0] = 1;
		Query( 1, 1, pointer - 1 );
		printf("%d\n", sum);
	}
}
