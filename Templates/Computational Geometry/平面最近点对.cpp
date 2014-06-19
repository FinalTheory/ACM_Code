/**
 * @file    HDU_1007.cpp
 * @brief   ƽ���������㷨ģ��
 * @hint    ���ڡ��㷨���ۡ���ʵ�֣���������΢���޸ģ�
 *	    �����ʵ�������Ƿ����ڵݹ��д����������ϵ�������
 *	    ͨ��Ԥ����ֱ����X������P�����Դ�󽵵ʹ���ĸ��ӳ̶��Լ��ռ�ռ�á�
 *	    �������ǿ���ÿ�ν�����Y�����֣�������ɺ�ֱ���ڱ��㺯���н���鲢����
 * @test    ģ�������Ŀ��HDU_1007
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
    //�󼯺�Ԫ������ȡ�Ͻ磬�Ҽ���ȡ�½�
    int m = ( l + r + 1 ) >> 1, p_l = l, p_r = m;
    //����ֱ�Ӿ���X�����������㵼�е�P����
    //X��������򣬿���ֱ�Ӵ�����ȥ����Ҫ����
    //����Ĺ�����Ҫ��Y����ΪY_L��Y_R��������
    REP(i, l, r) {
        if ( Y[i].idx < X[m].idx ) TMP[p_l++] = Y[i];
        else TMP[p_r++] = Y[i];
    }
    //���������ֺ����ʱ������ΪY������������ȥ�Ϳ�����
    double d1 = Min_dist(X, TMP, Y, l, m);
    double d2 = Min_dist(X, TMP, Y, m, r);
    //�������֮��ֱ���ù鲢�������ָ�Y���ϵ�����״̬
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
