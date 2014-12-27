/**
 * @file RMQ-ST算法.cpp
 * @brief   一种非常精妙的使用O(1)时间完成区间最值询问的算法
 * @hint    利用了特殊的区间性质，所以只能回答最值询问，不支持其他操作！
 * @feeling 好神奇的算法！大数据的情况下读入优化大显神威……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */

inline int INT()
{
    register int c = getchar();
    int x = 0;
    for( ; ( c < 48 || c > 57 ); c = getchar() );
    for( ; ( c > 47 && c < 58 ); c = getchar() ) x = x * 10 + c - 48;
    return x;
}

const int MAX = 1000010;
int N, Q;
int pre_calc[32][MAX];

void initRMQ()
{
    rep(i, N) pre_calc[0][i] = INT();
    for ( int j = 1, val = 2; val <= N; j++, val *= 2 )
        for ( int i = 0; i < N; i++ ) {
            int l = i, r = l + (val >> 1);
            pre_calc[j][i] = min(pre_calc[j - 1][l], r >= N ? INF : pre_calc[j - 1][r]);
        }
}

inline int queryRMQ( int l, int r )
{
    int j = 0, T = 1;
    while ( T <= r - l + 1 ) T *= 2, j++;
    T /= 2, j--;
    return min(pre_calc[j][l], pre_calc[j][r - T + 1]);
}

int main()
{
    while ( scanf("%d", &N) != EOF )
    {
        initRMQ();
        scanf("%d", &Q);
        int l, r;
        rep(i, Q) {
            l = INT(); r = INT();
            printf("%d\n", queryRMQ(l - 1, r - 1));
        }
    }
}
