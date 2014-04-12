/**
 * @file POJ_1523.cpp
 * @brief  Tarjan算法求图中割点
 * @hint    利用了两条性质：
 *	    1 若深度优先生成树的根有两棵或两棵以上的子树，则此根顶点必定为关节点；
 *	    2 若生成树中某个非叶子顶点v，其孩子结点均没有指向 v 的祖先的回边，则 v 为关节点。
 * @input   STL邻接表存储的有向/无向图
 * @output  res数组中存储去掉某个点之后增加的连通分量个数加一（考虑到图中本身至少有一个连通分量）
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
//这是另外一个版本，使用静态数组记录结果
void Tarjan( int u, bool isroot )
{
	visited[u] = true;
	int v, cnt = 0;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		//可以用这样的写法枚举去掉某一个点
		if ( v == _remove ) continue;
		if ( !DFN[v] ) {
			Tarjan(v, false);
			LOW[u] = min( LOW[u], LOW[v] );
			if ( isroot )
				cnt++;
			else if ( LOW[v] >= DFN[u] )
				cnt++;
		} else {
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( isroot && cnt >= 2 )
		res[u] = cnt;
	else if ( !isroot && cnt )
		res[u] = cnt + 1;
}
