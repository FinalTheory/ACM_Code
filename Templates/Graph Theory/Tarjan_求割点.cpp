/**
 * @file POJ_1523.cpp
 * @brief  Tarjan算法求图中割点，利用了两条性质：
 * 1 若深度优先生成树的根有两棵或两棵以上的子树，则此根顶点必定为关节点；
 * 2 若生成树中某个非叶子顶点v，其孩子结点均没有指向 v 的祖先的回边，则 v 为关节点。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-01
 */
#define MAX 1000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int LOW[MAX+10], DFN[MAX+10];
int TimeStamp;
vector<int> Adja[MAX+10];
vector< pair<int,int> > res;
int ans;
void Tarjan( int u, bool isroot )
{
	int v, cnt = 0;//记录去掉该点之后的连通分支个数
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v, false);
			LOW[u] = min( LOW[u], LOW[v] );
			//是根节点的话，那么v如果没被访问过，就是一颗新的子树
			if ( isroot )
				cnt++;
			//非叶子节点时，这个判断表示v一定在u后面遍历，也就是不存在回边
			else if ( LOW[v] >= DFN[u] )
				cnt++;
		}
		else
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( isroot && cnt >= 2 )
		//如果是根节点，那么去掉之后剩余的连通分支个数就是子树个数
		//因为一定会有连通分支的
		res.push_back( make_pair(u, cnt) );
	else if ( !isroot && cnt )
		//如果不是根节点，图本身至少会有一个连通分支，所以要加上一；
		//这里理解不好的话可以用一个星状图模拟一下。
		res.push_back( make_pair(u, cnt + 1) );
}

int main()
{
	//std::ios::sync_with_stdio(false);
	int u, v;
	bool has_input;
	int idx = 1;
	while (true)
	{
		has_input = false;
		for ( int i = 1; i <= MAX; ++i )
			Adja[i].clear();
		while ( true )
		{
			scanf("%d", &u);
			if ( u != 0 )
			{
				has_input = true;
				scanf("%d", &v);
				Adja[u].push_back(v);
				Adja[v].push_back(u);
			}
			else if ( has_input )
			{
				break;
			}
			else
			{
				goto end;
			}
		}
		CLR( DFN, 0 );
		res.clear();
		TimeStamp = 0; ans = 0; 
		Tarjan( 1, true );
		printf("Network #%d\n", idx++);
		if ( res.size() == 0 )
			printf("  No SPF nodes\n\n");
		else
		{
			sort( res.begin(), res.end() );
			for ( int i = 0; i < res.size(); ++i )
				printf("  SPF node %d leaves %d subnets\n", res[i].first, res[i].second);
			puts("");
		}
	}
	end:;
}
