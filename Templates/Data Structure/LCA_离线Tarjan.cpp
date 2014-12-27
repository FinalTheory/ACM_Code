/**
 * @file LCA_离线Tarjan.cpp
 * @brief   离线处理最近公共祖先问题的Tarjan算法
 * @hint    实现效率比较低下，用了一些重量级数据结构
 * @feeling 使用时如果被卡了STL常数，需要进行修改！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */
//临时存储输入的字符串
char str1[100], str2[100];
//最大人数
const int MAX = 100010;
//保存邻接表，使用静态链表会更加高效
VI Adja[MAX];
//记录每个节点在树中的父亲，即第一个灰色节点
int father[MAX];
//记录每个节点的颜色
int color[MAX];
//整数向字符串的映射
string names[MAX];
//记录所有输入的边
struct TMD
{
    int u, v;
} edges[MAX];
//记录两个整数向答案的映射
map<PII, int> ans;
//记录两个整数组成的pair
PII keys[MAX];
//记录节点编号向vector的映射，存储它所对应的节点
//使用静态链表会更加高效
map<int, VI> _map;

enum {WHITE, BLACK, GREY};

int find_root(int u)
{
    if ( father[u] == u ) return u;
    return father[u] = find_root(father[u]);
}

void DFS( int u, int fa )
{
    color[u] = GREY;
    //取出对应的所有节点，进行处理
    VI & others = _map[u];
    rep(i, others.size()) {
        int another = others[i];
        PII key = make_pair(min(u, another), max(u, another));
        if ( color[another] == BLACK ) {
            ans[key] = find_root(another);
        } else if ( color[another] == GREY ) {
            ans[key] = another;
        }
    }
    rep(i, Adja[u].size()) {
        int v = Adja[u][i];
        if ( v != fa ) DFS(v, u);
    }
    color[u] = BLACK;
    if ( fa != -1 ) father[u] = find_root(fa);
}

int main()
{
    int n;
    while ( scanf("%d", &n) != EOF )
    {
        map<string, int> _hash;
        map<string, int> :: iterator iter;
        //将坑爹的字符串映射到整数集合上，这里直接用map了
        //使用字符串哈希会更加高效！
        int num = 0;
        rep(i, n) {
            scanf("%s %s", str1, str2);
            string s1 = str1, s2 = str2;
            if ( (iter = _hash.find(s1)) == _hash.end() ) {
                names[num] = s1;
                edges[i].u = num;
                _hash[s1] = num++;
            } else {
                edges[i].u = iter->second;
            }
            if ( (iter = _hash.find(s2)) == _hash.end() ) {
                names[num] = s2;
                edges[i].v = num;
                _hash[s2] = num++;
            } else {
                edges[i].v = iter->second;
            }
        }
        //vector邻接表建图
        rep(i, num) Adja[i].clear();
        rep(i, n) {
            Adja[edges[i].u].PB(edges[i].v);
            Adja[edges[i].v].PB(edges[i].u);
        }
        //读入请求
        _map.clear();
        int m, u, v;
        scanf("%d", &m);
        rep(i, m) {
            scanf("%s %s", str1, str2);
            u = _hash[str1];
            v = _hash[str2];
            keys[i] = make_pair(min(u, v), max(u, v));
            _map[u].PB(v);
            if ( u != v ) _map[v].PB(u);
        }
        //初始化并查集
        rep(i, num) father[i] = i;
        ans.clear(); CLR(color, 0);
        //DFS离线求最近公共祖先
        DFS(0, -1);
        rep(i, m) puts(names[ans[keys[i]]].c_str());
    }
}
