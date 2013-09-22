/**
 * @file Tarjan_求割边.cpp
 * @brief   Tarjan求割边，模版。
 * @input   vector动态邻接表，以及权重矩阵
 * @output  权重最小的割边，可以适当修改ans的记录方式以适应不同情况。
 * @hint    注意不要处理父亲节点，因为满足条件的桥是树枝边。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-20
 */
const int INF = 0x3f3f3f3f;
#define MAX_e 1010
#define MAX 1010
//记录边权重
int wei[MAX_e][MAX_e];
//记录时间戳、答案（这里求最小权边）、已经遍历的节点数
int TimeStamp, ans, v_num;
int LOW[MAX+10], DFN[MAX+10];
//邻接表记录信息
vector<int> Adja[MAX_e];
void Tarjan( int u, int fa )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		//不处理当前节点的父亲，直接跳过
		if ( v == fa )
			continue;
		if ( !DFN[v] ) {
			Tarjan(v, u);
			//如果v没有被遍历，那么它的DFN值一定比当前的LOW[u]大
			//但是如果从点v继续DFS的话，可能会存在某点的DFN较小，使得LOW[v]更新后变小
			//所以就先继续DFS再更新最小值
			LOW[u] = min( LOW[u], LOW[v] );
			//这里说明v通过非父子边所能最早追溯到的祖先比u的遍历次序大
			//也就是说v只能是在u后面被遍历到的，即边u,v是桥
			if ( LOW[v] > DFN[u] && wei[u][v] < ans )
				ans = wei[u][v];
		} else {
			//如果v已经被遍历过了，那么它的值可能比当前的LOW[u]要小
			//所以用它来更新LOW[u]
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	++v_num;
}
