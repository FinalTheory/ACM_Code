/**
 * @file LCA-RMQ�����㷨.cpp
 * @brief   ����RMQ�Լ�����DFS���ʣ��������LCA������㷨ģ��
 * @hint    ������RMQ-ST�õ�ʵ����Ư��������㷨�������������������ޣ�
 *	    ���Ǿ�������Ľ�Ϻ�ȴ���ӳ�����ô���������
 * @feeling Ư�����㷨��
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
//�������ַ�����ӳ��
string names[MAX];
//��¼��������ı�
struct TMD
{
    int u, v;
} edges[MAX];
//��¼ÿ���ڵ������ֵ�λ�á�ÿ�γ��ֵ�����Լ��ڵ�ı��
//ǧ��ע�������С��
int p;
int pos[MAX], depth[MAX*2], nodes[MAX*2];

void DFS( int u, int fa, int d )
{
    nodes[p] = u;
    depth[p] = d;
    pos[u] = p++;
    rep(i, Adja[u].size()) {
        int v = Adja[u][i];
        if ( v != fa ) {
            DFS(v, u, d + 1);
            nodes[p] = u;
            depth[p] = d;
            pos[u] = p++;
        }
    }

}

int pre_calc[32][2*MAX];
int ans[32][2*MAX];

void initRMQ(int num)
{
    rep(i, num) {
        pre_calc[0][i] = depth[i];
        ans[0][i] = nodes[i];
    }
    for ( int j = 1, val = 2; val <= num; j++, val *= 2 )
        for ( int i = 0; i < num; i++ ) {
            int l = i, r = l + (val >> 1);
            pre_calc[j][i] = min(pre_calc[j - 1][l], r >= num ? INF : pre_calc[j - 1][r]);
            if ( r >= num ) {
                ans[j][i] = ans[j - 1][l];
            } else {
                if ( pre_calc[j - 1][l] <= pre_calc[j - 1][r] ) {
                    ans[j][i] = ans[j - 1][l];
                } else {
                    ans[j][i] = ans[j - 1][r];
                }
            }
        }
}

inline int queryRMQ( int l, int r )
{
    if ( l > r ) swap(l, r);
    int j = 0, T = 1;
    while ( T <= r - l + 1 ) T *= 2, j++;
    T /= 2, j--;
    if ( pre_calc[j][l] <= pre_calc[j][r - T + 1] ) {
        return ans[j][l];
    } else {
        return ans[j][r - T + 1];
    }
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
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
        p = 0;
        rep(i, n) {
            Adja[edges[i].u].PB(edges[i].v);
            Adja[edges[i].v].PB(edges[i].u);
        }
        DFS(0, -1, 0);
//        rep(i, p) printf("%d ", nodes[i]);puts("");
//        rep(i, p) printf("%d ", depth[i]);puts("");
//        rep(i, num) printf("%d ", pos[i]);puts("");
        initRMQ(p);
        //��������
        int m, u, v;
        scanf("%d", &m);
        rep(i, m) {
            scanf("%s %s", str1, str2);
            u = _hash[str1];
            v = _hash[str2];
            int res = queryRMQ(pos[u], pos[v]);
            puts(names[res].c_str());
        }
    }
}
