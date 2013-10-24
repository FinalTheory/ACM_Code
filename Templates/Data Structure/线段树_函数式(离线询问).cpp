/**
 * @file POJ_2104.cpp
 * @brief   ����ʽ�߶���ģ�棬�����K������
 * @hint    ����ʽ˼�룬ֻ��ֵ���޸ģ�����������ʷ�汾��Ȼ����������������Խ�������ѯ�ʡ�
 *	    ��������Ҫѯ�����������ڵĵ�k������ֻ����ɢ���������ö����������ѯ�ʷ�ʽ���ɡ�
 *	    ��������Ԫ�ظ���sum>=k���ݹ������������k�󣬷���ݹ������������k - sum��ֱ��Ҷ�ӡ�
 *	    ע���������õ�������������ʣ�ʵ���������Ų�ͬ��ʷ�������������
 *	    һ���ǲ��뵽��l-1��Ԫ�صľ�����һ���ǲ��뵽��rԪ�ص�������
 *	    �������֮��õ������൱��ֻ������[l, r]Ԫ�ص�һ�ż�¼���������ָ������߶�����
 *	    ������߶�������BST�ķ�ʽѯ�ʣ����ɵõ������k��
 *	    ����ÿ�ν������������ǲ���Ҫ�½����еĽڵ㣬����ֻ�½����ӵĽڵ㡣
 *	    Ҳ���ǴӸ��ڵ���������½��ڵ㲢����ԭ�ڵ��ֵ��Ȼ������޸ļ�sum+1���ɡ�
 *	    Ȼ������ֻ��Ҫ�޸�����ӻ����Ҷ�����һ����Ϣ��һֱ�ݹ鵽Ҷ�ӡ�
 *	    ע���ʼ״̬�£����ս���������Ҷ�ӽڵ�����Ҷ��Ӷ�ָ��0�Žڵ㣬Ҳ�����൱��NULL��
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-08
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
//��¼ԭ���顢���������顢ÿ��Ԫ�ض�Ӧ�ĸ��ڵ�
int nums[MAX], sorted[MAX], root[MAX];
int cnt;
struct TMD
{
	int sum, L_son, R_son;
} Tree[MAX<<5];
inline int CreateNode( int _sum, int _L_son, int _R_son )
{
	int idx = ++cnt;
	Tree[idx].sum = _sum;
	Tree[idx].L_son = _L_son;
	Tree[idx].R_son = _R_son;
	return idx;
}
void Insert( int & root, int pre_rt, int pos, int L, int R )
{
	//�Ӹ��ڵ����¸��µ�Ҷ�ӣ��½�����һ·���µĽڵ㣬��������һ�������ˡ�
	root = CreateNode( Tree[pre_rt].sum + 1, Tree[pre_rt].L_son, Tree[pre_rt].R_son );
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M )
		Insert( Tree[root].L_son, Tree[pre_rt].L_son, pos, L, M );
	else
		Insert( Tree[root].R_son, Tree[pre_rt].R_son, pos, M + 1, R );
}
int Query( int S, int E, int L, int R, int K )
{
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	//��������sum���ǵ�ǰѯ�ʵ������У�������е�Ԫ�ظ�����
	int sum = Tree[Tree[E].L_son].sum - Tree[Tree[S].L_son].sum;
	if ( K <= sum )
		return Query( Tree[S].L_son, Tree[E].L_son, L, M, K );
	else
		return Query( Tree[S].R_son, Tree[E].R_son, M + 1, R, K - sum );
}
int main()
{
	int n, m, num, pos, T;
	while ( scanf("%d %d", &n, &m) != EOF )
	{
		cnt = 0; root[0] = 0;
		for ( int i = 1; i <= n; ++i )
		{
			scanf("%d", &nums[i]);
			sorted[i] = nums[i];
		}
		sort( sorted + 1, sorted + 1 + n );
		num = unique( sorted + 1, sorted + n + 1 ) - ( sorted + 1 );
		for ( int i = 1; i <= n; ++i )
		{
			//ʵ�����Ƕ�ÿ��Ԫ�ؽ�����һ���߶�������������ڵ�
			pos = lower_bound( sorted + 1, sorted + num + 1, nums[i] ) - sorted;
			Insert( root[i], root[i - 1], pos, 1, num );
		}
		int l, r, k;
		while ( m-- )
		{
			scanf("%d %d %d", &l, &r, &k);
			pos = Query( root[l - 1], root[r], 1, num, k );
			printf("%d\n", sorted[pos]);
		}
	}
}

