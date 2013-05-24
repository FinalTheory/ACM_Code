/**
 * @file HDU_2222.cpp
 * @brief   AC�Զ���ģ���⡣��Ҫע��ĵط�������ע�͡�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-23
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#include <queue>
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

const int set_num = 26;
const char set_base = 'a';

char key[55];
char buffer[1000010];
int sum;

struct Node
{
	Node * fail;
	Node * next[set_num];
	int num;
	Node()
	{
		num = 0;
		fail = NULL;
		CLR(next, 0);
	}
};

stack<Node *> Pointers;

void Insert( Node * root, char * str )
{
	char * p_str = str;
	Node * tmp = root;
	while ( *p_str )
	{
		if ( tmp->next[*p_str - set_base] != NULL &&\
			 tmp->next[*p_str - set_base] != root )
			tmp = tmp->next[*p_str - set_base];
		else
		{
			tmp->next[*p_str - set_base] = new Node;
			tmp = tmp->next[*p_str - set_base];
			Pointers.push(tmp);
		}
		++p_str;
	}
	tmp->num++;
}
//root����ָ��Ϊ����������ɾ��ؽ���ѭ��
//��Ϊ���ڵ㴦next�����û��NULLָ�룬����һ������root��ֹͣ
//���ҽ�����������ɸ��¸�ֵ
void CreateFail( Node * root )
{
	queue<Node *> Q;
	Node * q, * r, * u, * v;
	int i;
	for ( i = 0; i < set_num; ++i )
		if ( ( q = root->next[i] ) != root )
		{
			q->fail = root;
			Q.push(q);
		}
	while ( !Q.empty() )
	{
		r = Q.front(); Q.pop();
		for ( i = 0; i < set_num; ++i )
		{
			if ( ( u = r->next[i] ) != NULL )
			{
				Q.push(u);
				v = r->fail;
				while ( v->next[i] == NULL ) v = v->fail;
				u->fail = v->next[i];
			}
		}
	}
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, N, i, len;
	Node * root, * q;
	scanf("%d", &T);
	while ( T-- )
	{
		//�ͷ��ڴ�
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		sum = 0;
		//ע�������ˣ��������ڵ��������Чnextָ�붼ָ���Լ�����Ч�Ļ��ں������
		//��������ʧ��ָ��ʱ���Ըɾ�����ؽ�����ѭ��
		root = new Node;
		Pointers.push(root);
		for ( i = 0; i < set_num; ++i )
			root->next[i] = root;

		scanf("%d", &N);
		for ( i = 0; i < N; ++i )
		{
			scanf("%s", key);
			Insert( root, key );
		}
		CreateFail(root);
		scanf("%s", buffer);
		len = strlen(buffer);
		q = root;
		for ( i = 0; i < len; ++i )
		{
			while ( q->next[buffer[i] - set_base] == NULL )
				q = q->fail;
			q = q->next[buffer[i] - set_base];
			Node * tmp = q;
			//ǧ��Ҫע�����ÿ���ҵ�λ��ʱҪ��������ʧ��ָ��
			//��Ϊƥ�䵽�ĵ�ǰ�����ܺ���������
			//�����ܺ�֮���ǵ��Ϳ����ˡ�
			while ( tmp != root && tmp->num != -1 )
			{
				sum += tmp->num;
				tmp->num = -1;
				tmp = tmp->fail;
			}
		}
		printf("%d\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
