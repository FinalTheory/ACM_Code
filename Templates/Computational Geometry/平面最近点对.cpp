/**
 * @file    HDU_1007.cpp
 * @brief   平面最近点对算法模版
 * @hint    基于《算法导论》的实现，做出了轻微的修改：
 *	    在这份实现中我们放弃在递归中传递三个集合的做法；
 *	    通过预排序，直接用X来代替P，可以大大降低代码的复杂程度以及空间占用。
 *	    这样我们可以每次仅仅对Y做划分，分治完成后直接在本层函数中将其归并排序。
 * @test    模版测试题目：HDU_1007
 * @author FinalTheory
 * @version 1.0
 * @date 2014-06-19
 */
const int MAX = 100100;

struct TMD
{
    double x, y;
    int idx;
} X[MAX], Y[MAX], Y_[MAX], TMP[MAX];

inline double dist( const TMD & a, const TMD & b )
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool cmp_x( const TMD & a, const TMD & b )
{
    if ( fabs(a.x - b.x) > eps )
        return a.x < b.x;
    else
        return a.y < b.y;
}

inline bool cmp_y( const TMD & a, const TMD & b )
{
    if ( fabs(a.y - b.y) > eps )
        return a.y < b.y;
    else
        return a.x < b.x;
}

void Merge( TMD * Dst, TMD * Src, int l, int r )
{
    int m = ( l + r + 1 ) >> 1, p_l = l, p_r = m, p = l;
    while( p_l < m && p_r < r ) {
        if ( cmp_y(TMP[p_l], TMP[p_r]) ) {
            Dst[p++] = Src[p_l++];
        } else {
            Dst[p++] = Src[p_r++];
        }
    }
    while ( p_l < m ) Dst[p++] = Src[p_l++];
    while ( p_r < r ) Dst[p++] = Src[p_r++];
}

double Min_dist( TMD * X, TMD * Y, TMD * TMP, int l, int r )
{
    if ( r - l <= 3 ) {
        double res = INF, tmp;
        REP(i, l, r)
            REP(j, i + 1, r)
                if ( ( tmp = dist(X[i], X[j]) ) < res )
                    res = tmp;
        return res;
    }
    //左集合元素数量取上界，右集合取下界
    int m = ( l + r + 1 ) >> 1, p_l = l, p_r = m;
    //这里直接就用X集合来代替算导中的P集合
    //X本身就有序，可以直接传递下去不需要划分
    //下面的过程是要将Y划分为Y_L和Y_R两个集合
    REP(i, l, r) {
        if ( Y[i].idx < X[m].idx ) TMP[p_l++] = Y[i];
        else TMP[p_r++] = Y[i];
    }
    //这样将划分后的临时数组作为Y集合来传递下去就可以了
    double d1 = Min_dist(X, TMP, Y, l, m);
    double d2 = Min_dist(X, TMP, Y, m, r);
    //分治完成之后直接用归并排序来恢复Y集合的有序状态
    Merge(Y, TMP, l, r);
    double d = min(d1, d2), tmp;
    int p = 0;
    REP(i, l, r) if ( X[m].x - d <= Y[i].x && Y[i].x <= X[m].x + d )
        Y_[p++] = Y[i];
    rep(i, p) {
        REP(j, i + 1, min(i + 8, p))
            if ( ( tmp = dist( Y_[i], Y_[j] ) ) < d )
                d = tmp;
    }
    return d;
}

int main()
{
    int n;
    while ( scanf("%d", &n) != EOF && n )
    {
        rep(i, n) scanf("%lf %lf", &X[i].x, &X[i].y);
        sort(X, X + n, cmp_x);
        rep(i, n) X[i].idx = i;
        memcpy(Y, X, sizeof(Y));
        sort(Y, Y + n, cmp_y);
        double res = Min_dist(X, Y, TMP, 0, n);
        printf("%.2f\n", res / 2.);
    }
}
