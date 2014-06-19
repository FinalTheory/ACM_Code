/**
 * @file    POJ_3070.cpp
 * @brief   矩阵快速幂模版
 * @hint    有递归和非递归版本，后者利用了二进制思想。
 * @test    模版测试题目：POJ_3070
 * @author FinalTheory
 * @version 1.0
 * @date 2014-05-13
 */
const int MAX = 2;

struct Mat
{
    int val[MAX][MAX], n;
} M;

inline Mat operator * ( Mat A, Mat B )
{
    Mat res;
    res.n = A.n;
    CLR(res.val, 0);
    rep(i, A.n)
    rep(j, A.n)
    rep(k, A.n) {
        res.val[i][j] += A.val[i][k] * B.val[k][j];
        res.val[i][j] %= MOD;
    }
    return res;
}

Mat Fast_Pow( Mat A, int k )
{
    if ( k == 1 ) return A;
    A = Fast_Pow( A, k / 2 );
    if ( k % 2 )
        return A * A * M;
    else
        return A * A;
}

Mat Fast_Pow2( Mat A, int k )
{
	Mat ans;
	ans.n = A.n;
	CLR( ans.val, 0 );
	rep(i, A.n) ans.val[i][i] = 1;
	while ( k )
	{
		if ( k & 1 )
			ans = ans * A;
		k >>= 1;
		A = A * A;
	}
	return ans;
}

int main()
{
	int n;
	M.n = 2;
	M.val[0][0] = 1; M.val[0][1] = 1;
	M.val[1][0] = 1; M.val[1][1] = 0;
	while ( scanf("%d", &n) != EOF && n != -1 )
	{
		if ( n == 0 ) {
			puts("0");
			continue;
		}
		Mat res = Fast_Pow(M, n);
		printf("%d\n", res.val[0][1]);
	}
}

