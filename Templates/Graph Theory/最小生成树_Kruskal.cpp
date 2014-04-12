/**
 * @file 最小生成树_Kruskal.cpp
 * @brief  最小生成树算法模版 
 * @hint    时间复杂度O(e*lg(e))，其中e为边数。
 *	    简单的实现就可以带来较好的时间复杂度，推荐使用！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-03-21
 */
#define MAX_e 100010
#define MAX_v 10010

int c[MAX_v];

struct TMD
{
    int u, v, w;
} r[MAX_e];

bool fuck( const TMD & a, const TMD & b )
{
    return a.w < b.w;
}

int Tree[MAX_v];

int find_root( int node )
{
    if ( Tree[node] == node )
        return node;
    else
        return Tree[node] = find_root(Tree[node]);
}

int main()
{
    int n, m;
    while ( scanf("%d %d", &n, &m) != EOF )
    {
        rep(i, m) {
            r[i].u = INT();
            r[i].v = INT();
            r[i].w = INT();
        }
        REP(i, 1, n + 1) Tree[i] = i;
        sort( r, r + m, fuck );
        int ans = 0;
        rep(i, m)
        {
            int u = r[i].u, v = r[i].v;
            int root_u = find_root(u), root_v = find_root(v);
            if ( root_u != root_v )
            {
                ans += r[i].w;
                Tree[root_u] = root_v;
            }
        }
        cout << ans << endl;
    }
}
