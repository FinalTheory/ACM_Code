/**
 * @file POJ_2528.cpp
 * @brief   �߶�����ɢ������Ҫע����ǲ�ѯ��ʱ��
 * ֻ�з���ĳ�����䱻ͬһ�ź������ǲŰ�������Ϣ������ȥ��
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
	//��¼��������Ƿ�ͬһ�ź���������
	bool is_FullFilled;
}Tree[MAX<<3];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	//��ʼ��Ϊ���ʾ����ǽ
	Tree[root].nType = 0;
	//�����൱�ڱ�ǽ����ȫ����
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
	//�����ǰ�����߶������Ǳ�һ�ź������ǵģ��Ͱ���Ϣ������ȥ��Ȼ����յ�ǰ����Ϣ
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
	//��ѯ��ʱ�������ѯ��Χ�պ�ƥ�䣬�����������ֻ��һ�ź������ǣ���׼��������͡�
	//������ǵĻ����ͼ����ݹ��ѯ������ֻ��ѯһ�Σ����µݹ鵽���ڵ�Ҳûʲô��
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
//�����Ƕ��ֲ��ң�ǧ��ע��д��
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
		//�����׼�������е�ӳ�䵽1~n����
		sort( Buffer, Buffer + 2 * n );
		prev = map[1] = Buffer[0];
		for ( i = 1, pointer = 2; i < 2 * n; ++i )
			if ( Buffer[i] != Buffer[i - 1] )
			{
				//��ɢ�������ʱ��ע�⣬������㲻�����������м��ٲ���һ����
				//�����������Ҳ��������һ���ĵ�����
				if ( Buffer[i] - prev > 1 )
					map[pointer++] = ( Buffer[i] + prev ) >> 1;
				map[pointer++] = Buffer[i];
				prev = Buffer[i];
			}
		//�����е������ɢ��������ӳ�䣬һ����pointer-1����
		CreateTree( 1, 1, pointer - 1 );
		int left, right;
		int type = 1;
		for ( i = 1; i <= n; ++i )
		{
			//����������ģ����Զ��ֲ��ҳ���λ�ü�Ϊ�Ǹ����Ӧ��ӳ��
			left = Search( L[i], 1, pointer - 1 );
			right = Search( R[i], 1, pointer - 1 );
			Insert( 1, left, right, type++ );
		}
		sum = 0; flags[0] = 1;
		Query( 1, 1, pointer - 1 );
		printf("%d\n", sum);
	}
}
