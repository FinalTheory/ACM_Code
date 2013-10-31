/**
 * @file main.cpp
 * @brief   矩阵快速幂模版，注意需要求模的地方.
 * @hint    注意这里的非递归版本实际上是利用了二进制的思想
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-27
 */
#define MAX 10
#define CLR(arr,val) memset(arr,val,sizeof(arr))
const int MOD = 9973;
struct Mat
{
    int val[MAX][MAX], n;
} M;
inline Mat operator * ( Mat A, Mat B )
{
    Mat res;
    res.n = A.n;
    CLR(res.val, 0);
    for ( int i = 0; i < A.n; ++i )
    for ( int j = 0; j < A.n; ++j )
    for ( int k = 0; k < A.n; ++k )
    {
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

Mat Fast_Pow2( Mat & A, int k )
{
	Mat ans;
	ans.n = A.n;
	CLR( ans.val, 0 );
	for ( int i = 0; i < A.n; ++i )
		ans.val[i][i] = 1;
	while ( k )
	{
		if ( k & 1 )
			ans = ans * A;
		k >>= 1;
		A = A * A;
	}
	return ans;
}
//示例：求矩阵的秩
int main()
{
	
    int T, n, k;
    scanf("%d", &T);
    while ( T-- )
    {
    	scanf("%d %d", &n, &k);
    	M.n = n;
        for ( int i = 0; i < n; ++i )
        	for ( int j = 0; j < n; ++j )
            	scanf("%d", &M.val[i][j]);
        Mat res = Fast_Pow2(M, k);
        int ans = 0;
        for ( int i = 0; i < n; ++i )
        {
            ans += res.val[i][i];
            ans %= MOD;
        }
        printf("%d\n", ans);
    }
}

