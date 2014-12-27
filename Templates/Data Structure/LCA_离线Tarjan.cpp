/**
 * @file LCA_����Tarjan.cpp
 * @brief   ���ߴ�������������������Tarjan�㷨
 * @hint    ʵ��Ч�ʱȽϵ��£�����һЩ���������ݽṹ
 * @feeling ʹ��ʱ���������STL��������Ҫ�����޸ģ�
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */
//��ʱ�洢������ַ���
char str1[100], str2[100];
//�������
const int MAX = 100010;
//�����ڽӱ�ʹ�þ�̬�������Ӹ�Ч
VI Adja[MAX];
//��¼ÿ���ڵ������еĸ��ף�����һ����ɫ�ڵ�
int father[MAX];
//��¼ÿ���ڵ����ɫ
int color[MAX];
//�������ַ�����ӳ��
string names[MAX];
//��¼��������ı�
struct TMD
{
    int u, v;
} edges[MAX];
//��¼����������𰸵�ӳ��
map<PII, int> ans;
//��¼����������ɵ�pair
PII keys[MAX];
//��¼�ڵ�����vector��ӳ�䣬�洢������Ӧ�Ľڵ�
//ʹ�þ�̬�������Ӹ�Ч
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
    //ȡ����Ӧ�����нڵ㣬���д���
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
        //���ӵ����ַ���ӳ�䵽���������ϣ�����ֱ����map��
        //ʹ���ַ�����ϣ����Ӹ�Ч��
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
        //vector�ڽӱ�ͼ
        rep(i, num) Adja[i].clear();
        rep(i, n) {
            Adja[edges[i].u].PB(edges[i].v);
            Adja[edges[i].v].PB(edges[i].u);
        }
        //��������
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
        //��ʼ�����鼯
        rep(i, num) father[i] = i;
        ans.clear(); CLR(color, 0);
        //DFS�����������������
        DFS(0, -1);
        rep(i, m) puts(names[ans[keys[i]]].c_str());
    }
}
