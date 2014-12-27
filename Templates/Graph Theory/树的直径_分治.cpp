/**
 * @file ����ֱ��_����.cpp
 * @brief   ��΢����һ��ķ��η�����û���������BFS�ķ�����
 *	    �������BFS����Զ�㣬�ٴ������Զ��BFS���ó�����Զ������Ǵ𰸡�
 *	    ������ʿ���ͨ����ͼ������Ȼ�����������֤����
 * @hint    �������ϵ��·������ֻ�����������ͨ�����ڵ㣬������·��
 *	    ���������ڵ㣬������ĳ�������е��·���ɴ˿��Է��Σ�һ��DFS����𰸡�
 * @feeling ���η����Ǻܺ����
 * @author FinalTheory
 * @version 0.1
 * @date 2014-12-26
 */
const int MAX = 100010;
vector<int> Adja[MAX];
//��¼��ĳ���ڵ�Ϊ���������еĽڵ��������
int depth[MAX];

int DFS( int u, int fa )
{
    int _max = 0, first = -1, second = -1;
    //���������������������е��·
    rep(i, Adja[u].size()) {
        int v = Adja[u][i];
        if ( v != fa ) {
            _max = max(_max, DFS(v, u));
            //�ҳ���������������������ڵ�
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
