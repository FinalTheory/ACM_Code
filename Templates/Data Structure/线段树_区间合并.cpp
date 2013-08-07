/**
 * @file POJ_3667.cpp
 * @brief   ����ϲ������⣬��Ҫ˼·�������������ֱ��¼��������������ұ����������Լ��������������
 * ǧ��ҪС�ĵĵط�����ν��в�ѯ����������������Ϳ���ֱ�Ӽ�¼λ�ò����ء�
 * ������߼��ж�֮����Чλ��ֻ�����ֿ��ܣ��������С����������Լ����������ұ߼�������������ߡ�
 * �����Ϳ��Եݹ鴦���ˡ�����ο�������Query������ִ���߼���
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-08
 */
#define MAX 80010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	int L, R, Cover;
	//��¼���������ҵ������������
	int lSum, rSum, maxSum;
	int len(){return R - L + 1;}
} Tree[MAX<<2];

int r;

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Cover = 1;
	Tree[root].lSum = Tree[root].rSum = Tree[root].maxSum = ( R - L + 1 );
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Pushdown( int root )
{
	if ( Tree[root].Cover != -1 )
	{
		Tree[L_son].Cover = Tree[R_son].Cover = Tree[root].Cover;
		Tree[L_son].lSum = Tree[L_son].rSum = Tree[L_son].maxSum = \
			Tree[L_son].Cover ? Tree[L_son].len() : 0;
		Tree[R_son].lSum = Tree[R_son].rSum = Tree[R_son].maxSum = \
			Tree[R_son].Cover ? Tree[R_son].len() : 0;
		Tree[root].Cover = -1;
	}
}

void Pushup( int root )
{
	//������Ҳ��ͬ�Ļ�һ����������ע���������ĸ����߼���
	if ( Tree[L_son].Cover == Tree[R_son].Cover )
		Tree[root].Cover = Tree[L_son].Cover;
	if ( Tree[L_son].lSum == Tree[L_son].len() )
		Tree[root].lSum = Tree[L_son].lSum + Tree[R_son].lSum;
	else
		Tree[root].lSum = Tree[L_son].lSum;
	if ( Tree[R_son].rSum == Tree[R_son].len() )
		Tree[root].rSum = Tree[L_son].rSum + Tree[R_son].rSum;
	else
		Tree[root].rSum = Tree[R_son].rSum;
	Tree[root].maxSum = Tree[L_son].rSum + Tree[R_son].lSum;
	if ( Tree[L_son].maxSum > Tree[root].maxSum ) Tree[root].maxSum = Tree[L_son].maxSum;
	if ( Tree[R_son].maxSum > Tree[root].maxSum ) Tree[root].maxSum = Tree[R_son].maxSum;
}

void Update( int root, int L, int R, int flag )
{
	if ( L == Tree[root].L && R == Tree[root].R )
	{
		Tree[root].Cover = flag;
		Tree[root].lSum = Tree[root].rSum = Tree[root].maxSum = \
			flag ? Tree[root].len() : 0;
		return;
	}
	Pushdown(root);
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( L > M )
	{
		Update( R_son, L, R, flag );
	}
	else if ( R <= M )
	{
		Update( L_son, L, R, flag );
	}
	else
	{
		Update( L_son, L, M, flag );
		Update( R_son, M + 1, R, flag );
	}
	Pushup( root );
}

void Query( int root, int w )
{
	if ( r != -1 )
		return;
	//��������������䶼������ͷ���
	if ( Tree[root].maxSum < w )
		return;
	//ǧ��Ҫע����������ߵ�����Ļ�ֱ�Ӹ��²�����
	if ( Tree[root].lSum >= w )
	{
		r = Tree[root].L;
		return;
	}
	//����Ҷ�ӽڵ�ҲҪ����
 	if ( Tree[root].L == Tree[root].R )
 		return;
	if ( Tree[L_son].maxSum >= w )
	{
		Query(L_son, w);
	}
	else if ( Tree[L_son].rSum + Tree[R_son].lSum >= w )
	{
		r = Tree[L_son].R - Tree[L_son].rSum + 1;
		return;
	}
	else
	{
		Query(R_son, w);
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int N, M, com, D, X;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		CreateTree( 1, 1, N );
		while ( M-- )
		{
			scanf("%d", &com);
			if ( com == 1 )
			{
				scanf("%d", &D);
				r = -1;
				Query(1, D);
				if ( r != -1 )
				{
					printf("%d\n", r);
					Update( 1, r, r + D - 1, 0 );
				}
				else
				{
					printf("0\n");
				}
			}
			else if ( com == 2 )
			{
				scanf("%d %d", &X, &D);
				Update( 1, X, X + D - 1, 1 );
 			}
		}
	}
}
