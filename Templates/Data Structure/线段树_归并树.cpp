/**
 * @file �߶���_�鲢��.cpp
 * @brief  �鲢��ģ��
 * ���ȿ�������˼·�������н������򲢼�¼����Ԫ�صĳ�ʼλ�ã�Ȼ��ÿ��ѯ�ʣ���������ɨһ�飻
 * ��һ������c��ʾ�Ѿ�ɨ���˴���ѯ����ĵ�cС��������Ϊ���ڵ������Ѿ���������ˣ�
 * ��������ҵ�һ��Ԫ�����ڴ���ѯ���䣬�Ϳ�������c������ֱ��c == kʱ������
 * ����������������ȷ����Ȼ������Ч�ʷǳ�����Ϊ��������ѯ�ٶȣ������������˼�롣
 * ����������������е�ÿһ��Ԫ�أ�������һ�ֲ�ѯ�����ܹ�֪�����Ǵ���ѯ�����еĵڼ���Ԫ�أ�
 * ��ô�Ϳ�����log(N)�β�ѯ���ҳ���k��Ԫ�أ�����������ĵ�һ����֡�
 * ��������鲢����ÿ�β�ѯ���������䣬һ�����Ա����ϵ�ĳЩ����Ĳ�����ʾ�������߶����Ļ������ܣ�
 * ���Խ�����һ������ѯ�����ֳ���Щ����Ĳ������Ӷ�ͬ����log(N)�������ǵڶ�����֣�
 * ������ڹ鲢����ÿ�������е�Ԫ�ض�������ģ�����Щ����ѯ�������ҳ�����ѯԪ���ǵڼ���Ԫ�أ�
 * Ҳ��������һ�ζ��ֲ��ң��临�Ӷ�ͬ����log(N)������ǵ����ζ��֡�
 * ���ÿ��ѯ�ʵĸ��ӶȾ���log(N)^3���鲢���������ܸ��Ӷ�ΪM*log(N)^3��
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
	//����һ���Ԫ�ع鲢����ǰ��
	while ( i <= M && j <= R )
	{
		if ( a[depth + 1][i] < a[depth + 1][j] )
			a[depth][k++] = a[depth + 1][i++];
		else
			a[depth][k++] = a[depth + 1][j++];
	}
	//������һ���Ѿ��ǿյģ���������������ִֻ��һ�䣬���ÿ���˳��
	while ( i <= M ) a[depth][k++] = a[depth + 1][i++];
	while ( j <= R ) a[depth][k++] = a[depth + 1][j++];
}
//����ǵ�������ֲ����ˣ����ڵ�ǰ�ڵ������Ԫ������num�ǵڼ���
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
//�����ǵڶ�����ֲ��ң����߶��������ѯ�ʲ���
int Query( int root, int L, int R, int num, int depth )
{
	//�������ѯ�������õ��ڵ�ǰ�ڵ�����䣬������������в���num�ǵڼ���Ԫ��
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
			//�����������Ķ��ֲ��ң������������ж��֣�������ڴ���ѯ�������ǵڼ�С
			//����ѯ��ĳ��ֵ��ʹ�����ڴ���ѯ������ǡ��Ϊ��kСʱ����Ϊ����Ĵ𰸡�
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
