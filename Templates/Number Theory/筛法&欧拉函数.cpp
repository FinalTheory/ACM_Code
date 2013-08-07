/**
 * @file POJ_2824.cpp
 * @brief   欧拉函数模版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-02
 */
#define MAX 3000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
bool prime[MAX+10];
//记录欧拉函数
int E[MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
	//筛法部分
	CLR(prime, 1);
	prime[0] = prime[1] = 0;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	//求欧拉函数部分
	for ( int i = 1; i <= MAX; ++i )
		E[i] = i;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
		{
			for ( int j = 2 * i; j <= MAX; j += i )
				E[j] = E[j] / i * ( i - 1 );
			E[i] = i - 1;
		}
}
