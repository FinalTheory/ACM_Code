/**
 * @file HDU_3065.cpp
 * @brief   AC自动机模版题
 * @input   关键字、待匹配文本
 * @output  按照输入顺序，输出每个关键字出现的次数
 * @hint    需要回溯fail指针，但是无需标记掉，因为是统计每个出现的次数，而不是一共出现了多少个。
 *	    另外，节点里面记录的是ID，即字符串的输入顺序。还有就是可以预处理一下待匹配串。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-15
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX 1010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
const int set_num = 27;
const char set_base = 'A';
char key[MAX][55];
int ans[MAX];
char buffer[2000010];
int sum;
struct Node
{
	Node * fail;
	Node * next[set_num];
	int ID;
	Node()
	{
		ID = 0;
		fail = NULL;
		CLR(next, 0);
	}
};
stack<Node *> Pointers;
void Insert( Node * root, char * str, int ID )
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
	tmp->ID = ID;
}
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
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N;
	Node * root, * q, * tmp;
	while ( scanf("%d", &N) != EOF )
	{
		CLR(ans, 0);
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = new Node;
		Pointers.push(root);
		for ( int i = 0; i < set_num; ++i )
			root->next[i] = root;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%s", key[i]);
			Insert(root, key[i], i);
		}
		CreateFail(root);
		scanf("%s", buffer);
		int len = strlen(buffer);
		for ( int i = 0; i < len; ++i )
			if ( buffer[i] < 'A' || buffer[i] > 'Z' )
				buffer[i] = '[';
		q = root;
		for ( int i = 0; i < len; ++i )
		{
			while ( q->next[buffer[i] - set_base] == NULL )
				q = q->fail;
			q = q->next[buffer[i] - set_base];
			tmp = q;
			while ( tmp != root && tmp->ID )
			{
				ans[tmp->ID]++;
				tmp = tmp->fail;
			}
		}
		for ( int i = 1; i <= N; ++i ) if ( ans[i] )
			printf("%s: %d\n", key[i], ans[i]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
