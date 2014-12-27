/**
 * @file 树的直径_分治.cpp
 * @brief   稍微复杂一点的分治法，最好还是用两遍BFS的方法：
 *	    从任意点BFS到最远点，再从这个最远点BFS，得出的最远距离就是答案。
 *	    这个性质可以通过画图分析，然后分类讨论来证明。
 * @hint    考虑树上的最长路，有且只有两种情况：通过根节点，构造的最长路；
 *	    不经过根节点，包含在某个子树中的最长路。由此可以分治，一遍DFS求出答案。
 * @feeling 分治法不是很好理解
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */
const int MAX = 100010;
vector<int> Adja[MAX];
//记录以某个节点为根的子树中的节点的最大深度
int depth[MAX];

int DFS( int u, int fa )
{
    int _max = 0, first = -1, second = -1;
    //遍历所有子树，求子树中的最长路
    rep(i, Adja[u].size()) {
        int v = Adja[u][i];
        if ( v != fa ) {
            _max = max(_max, DFS(v, u));
            //找出所有子树中最深的两个节点
            if ( depth[v] > first ) {
                second = first;
                first = depth[v];
            } else if ( depth[v] > second ) {
                second = depth[v];
            }
        }
    }
    depth[u] = first + 1;
    _max = max(_max, first + second + 2);
    return _max;
}

int main()
{
    int N;
    while ( scanf("%d", &N) != EOF )
    {
        REP(i, 1, N + 1) Adja[i].clear();
        int u, v;
        rep(i, N - 1) {
            scanf("%d %d", &u, &v);
            Adja[u].PB(v);
            Adja[v].PB(u);
        }
        int ans = DFS(1, -1);
        printf("%d\n", ans);
    }
}
