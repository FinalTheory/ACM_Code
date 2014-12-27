/**
 * @file zkw线段树_单点更新.cpp
 * @brief   一种常数很小的线段树模版。
 * @hint    只能用于处理简单的单点更新问题。想要理解最好画图模拟！
 * @feeling 神奇的自底向上更新思想！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */
const int MAX = 200010;
int nMin[MAX<<2];
int M;

void Create(int n)
{
    M = 1;
    while ( M < n + 2 ) M <<= 1;
    REP(i, 1, n + 1) scanf("%d", &nMin[M + i]);
    rev(i, M) nMin[i] = max(nMin[i<<1], nMin[i<<1|1]);
}

int Query( int l, int r )
{
    int res = 0;
    for ( l=l+M-1, r=r+M+1; (l^r)!=1; l>>=1, r>>=1 ) {
        if ( (l & 1) == 0 ) res = max(res, nMin[l^1]);
        if ( (r & 1) == 1 ) res = max(res, nMin[r^1]);
    }
    return res;
}

void Update( int pos, int val )
{
    pos += M;
    nMin[pos] = val;
    while ( pos >= 1 ) {
        pos >>= 1;
        nMin[pos] = max(nMin[pos<<1], nMin[pos<<1|1]);
    }
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int N, Q;
    while ( scanf("%d %d", &N, &Q) != EOF )
    {
        Create(N);
        int a, b;
        char t[3];
        rep(i, Q) {
            scanf("%s %d %d", t, &a, &b);
            if ( t[0] == 'U' ) {
                Update(a, b);
            } else {
                printf("%d\n", Query(a, b));
            }
        }
    }
}
