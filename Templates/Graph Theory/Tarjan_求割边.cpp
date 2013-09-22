/**
 * @file Tarjan_����.cpp
 * @brief   Tarjan���ߣ�ģ�档
 * @input   vector��̬�ڽӱ��Լ�Ȩ�ؾ���
 * @output  Ȩ����С�ĸ�ߣ������ʵ��޸�ans�ļ�¼��ʽ����Ӧ��ͬ�����
 * @hint    ע�ⲻҪ�����׽ڵ㣬��Ϊ����������������֦�ߡ�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-20
 */
const int INF = 0x3f3f3f3f;
#define MAX_e 1010
#define MAX 1010
//��¼��Ȩ��
int wei[MAX_e][MAX_e];
//��¼ʱ������𰸣���������СȨ�ߣ����Ѿ������Ľڵ���
int TimeStamp, ans, v_num;
int LOW[MAX+10], DFN[MAX+10];
//�ڽӱ��¼��Ϣ
vector<int> Adja[MAX_e];
void Tarjan( int u, int fa )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		//������ǰ�ڵ�ĸ��ף�ֱ������
		if ( v == fa )
			continue;
		if ( !DFN[v] ) {
			Tarjan(v, u);
			//���vû�б���������ô����DFNֵһ���ȵ�ǰ��LOW[u]��
			//��������ӵ�v����DFS�Ļ������ܻ����ĳ���DFN��С��ʹ��LOW[v]���º��С
			//���Ծ��ȼ���DFS�ٸ�����Сֵ
			LOW[u] = min( LOW[u], LOW[v] );
			//����˵��vͨ���Ǹ��ӱ���������׷�ݵ������ȱ�u�ı��������
			//Ҳ����˵vֻ������u���汻�������ģ�����u,v����
			if ( LOW[v] > DFN[u] && wei[u][v] < ans )
				ans = wei[u][v];
		} else {
			//���v�Ѿ����������ˣ���ô����ֵ���ܱȵ�ǰ��LOW[u]ҪС
			//��������������LOW[u]
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	++v_num;
}
