/**
 * @file POJ_1523.cpp
 * @brief  Tarjan�㷨��ͼ�и��
 * @hint    �������������ʣ�
 *	    1 ����������������ĸ������û��������ϵ���������˸�����ض�Ϊ�ؽڵ㣻
 *	    2 ����������ĳ����Ҷ�Ӷ���v���亢�ӽ���û��ָ�� v �����ȵĻرߣ��� v Ϊ�ؽڵ㡣
 * @input   STL�ڽӱ�洢������/����ͼ
 * @output  res�����д洢ȥ��ĳ����֮�����ӵ���ͨ����������һ�����ǵ�ͼ�б���������һ����ͨ������
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
	int v, cnt = 0;//��¼ȥ���õ�֮�����ͨ��֧����
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v, false);
			LOW[u] = min( LOW[u], LOW[v] );
			//�Ǹ��ڵ�Ļ�����ôv���û�����ʹ�������һ���µ�����
			if ( isroot )
				cnt++;
			//��Ҷ�ӽڵ�ʱ������жϱ�ʾvһ����u���������Ҳ���ǲ����ڻر�
			else if ( LOW[v] >= DFN[u] )
				cnt++;
		}
		else
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( isroot && cnt >= 2 )
		//����Ǹ��ڵ㣬��ôȥ��֮��ʣ�����ͨ��֧����������������
		//��Ϊһ��������ͨ��֧��
		res.push_back( make_pair(u, cnt) );
	else if ( !isroot && cnt )
		//������Ǹ��ڵ㣬ͼ�������ٻ���һ����ͨ��֧������Ҫ����һ��
		//������ⲻ�õĻ�������һ����״ͼģ��һ�¡�
		res.push_back( make_pair(u, cnt + 1) );
}
//��������һ���汾��ʹ�þ�̬�����¼���
void Tarjan( int u, bool isroot )
{
	visited[u] = true;
	int v, cnt = 0;
	DFN[u] = LOW[u] = ++TimeStamp;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		//������������д��ö��ȥ��ĳһ����
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
