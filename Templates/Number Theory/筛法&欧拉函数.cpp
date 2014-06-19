/**
 * @file    筛法&欧拉函数.cpp
 * @brief   先使用筛法求素数，然后再求一个范围内的欧拉函数。
 * @test    模版测试题目：HDU_2824
 * @author FinalTheory
 * @version 1.0
 * @date 2014-05-13
 */
const int MAX = 3000010;
//记录质数
bool prime[MAX];
//记录欧拉函数
int E[MAX];

LL euler(LL n)
{
     LL i;
     LL res = n, a = n;
     for( i = 2; i * i <= a; ++i ) {
         if ( a % i == 0 ) {
             res -= res / i;
             while( a % i == 0 ) a /= i;
         }
     }
     if( a > 1 ) res -= res / a;
     return res;
}

int main()
{
	//筛法求素数
	CLR(prime, 1);
	prime[0] = prime[1] = false;
	for ( int i = 2; i < MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j < MAX; j += i )
				prime[j] = false;
	//求欧拉函数
	rep(i, MAX) E[i] = i;
	for ( int i = 2; i < MAX; ++i ) if ( prime[i] ) {
        for ( int j = 2 * i; j < MAX; j += i )
            E[j] = E[j] / i * ( i - 1 );
        E[i] = i - 1;
    }
    int a, b;
    while ( scanf("%d %d", &a, &b) != EOF )
    {
        LL sum = 0;
        REP(i, a, b + 1) sum += E[i];
        cout << sum << endl;
    }
}
