/**
 * @file HDU_1166.cpp
 * @brief   树状数组模版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#define MAX 50010
int Tree[MAX];
//计算当前节点编号所支配的元素个数
inline int Lowbit( int x )
{
	return x & (-x);
}

//num of elements
int N;
void Add( int pos, int num )
{
	while ( pos <= N )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}
//Calculate the sum of 1 ~ pos
//核心在于每次减去当前节点所支配的元素个数
//直到位置变为零，也就是退回了序列的开头位置。
int Query( int pos )
{
	int sum = 0;
	//注意这里，不能为零，否则死循环
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
}
//应用：逆序对：
int main()
{
	int n;
	while ( scanf("%d", &n) != EOF )
	{
		CLR(Tree, 0);
		int res = 0;
		N = n;
		for ( int i = 0; i < n; ++i )
			{scanf("%d", &nums[i]); nums[i]++;}
		for ( int i = 0; i < n; ++i )
		{
			Add(nums[i], 1);
			res += i + 1 - Query(nums[i]);
		}
		printf("%d\n", res);
	}
    
}
