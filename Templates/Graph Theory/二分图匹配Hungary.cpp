/**
 * @file HDU_2444.cpp
 * @brief   二分图判定和匹配模版
 * @hint    由于建图时为了进行判定而双向加边，所以求出的最大匹配应该除以2.
 * @feeling 总算把Tarjan搞明白了。
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-04
 */
const int MAX = 210;
//vector存储邻接表
VI Adja[MAX];
//保存节点的染色情况
int color[MAX];
//保存节点的匹配节点，以及某个节点是否被加入了增广路
int match[MAX], visited[MAX];
//点数、边数
int n, m;
//二分图判定
bool judge( int u, int prev )
{
    if ( color[u] != 0 ) {
        if ( color[u] != -prev ) return false;
        else  return true;
    }
    color[u] = -prev;
    rep(i, Adja[u].size()) {
        if ( !judge(Adja[u][i], color[u]) )
            return false;
    }
    return true;
}
//初始化
void Init()
{
    CLR(color, 0);
    rep(i, n + 1) Adja[i].clear();
}
//数据读入
void Read()
{
    int a, b;
    rep(i, m) {
        scanf("%d %d", &a, &b);
        Adja[a].PB(b);
        Adja[b].PB(a);
    }
}
//DFS寻找增广路
bool DFS( int u )
{
	rep(i, Adja[u].size())
	{
		//枚举与点u相邻的所有点（邻接表存储）
		int v = Adja[u][i];
		//如果在本次DFS中未被访问过，即不在交替路上
		if ( !visited[v] )
		{
			visited[v] = true;
			//如果是未匹配点，就可以结束并返回true
			//如果从这个点继续DFS可以找到未匹配点，则DFS后返回true
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	//若找不到交替路，则返回false
	return false;
}
//二分图匹配
int Hungary()
{
	int res = 0;
	CLR(match, -1);
	REP(u, 1, n + 1)
	{
	    //清空标记数组
		CLR( visited, 0 );
		if ( DFS(u) ) res++;
	}
	return res;
}

int main()
{
	//std::ios::sync_with_stdio(false);
    while ( scanf("%d %d", &n, &m) != EOF )
    {
        Init();
        Read();
        if ( !judge(1, 1) ) {
            puts("No");
        } else {
            int res = Hungary();
            printf("%d\n", res / 2);
        }
    }
}
