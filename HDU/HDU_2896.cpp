/**
 * @file HDU_2896.cpp
 * @brief   AC自动机模版题，节点记录一下ID信息。
 * 由于是完整匹配，所以不需要像HDU_2222那样一次匹配完成后一直回溯fail指针。
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
const int set_num = 128;
const char set_base = '\0';

char buffer[10010];
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
void Insert( Node * root, char * str, int ID )
{
	char * p_str = str;
	Node * tmp = root;
	while ( *p_str )
	{
		if ( tmp->next[*p_str - set_base] != NULL &&\
			tmp->next[*p_str - set_base] != root ) {
			tmp = tmp->next[*p_str - set_base];
		} else {
			tmp->next[*p_str - set_base] = new Node;
			tmp = tmp->next[*p_str - set_base];
			Pointers.push(tmp);
		}
		++p_str;
	}
	tmp->ID = ID;
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
	int N, M;
	char str[300];
	vector <int> ans[1010];
	while ( scanf("%d", &N) != EOF )
	{
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		Node * root = new Node;
		Pointers.push(root);
		for ( int i = 0; i < set_num; ++i )
			root->next[i] = root;
		for ( int i = 0; i < N; ++i )
		{
			scanf("%s", str);
			Insert(root, str, i + 1);
		}
		CreateFail(root);
		scanf("%d", &M);
		for ( int i = 0; i < M; ++i )
		{
			ans[i].clear();
			int sum = 0;
			scanf("%s", buffer);
			int len = strlen(buffer);
			Node * q = root;
			for ( int j = 0; j < len; ++j )
			{
				while ( q->next[buffer[j] - set_base] == NULL )
					q = q->fail;
				q = q->next[buffer[j] - set_base];
				if ( q->ID )
					ans[i].push_back(q->ID);
			}
		}
		int sum_all = 0;
		for ( int k = 0; k < M; ++k ) if ( ans[k].size() )
		{
			sum_all++;
			sort(ans[k].begin(), ans[k].end());
			printf("web %d: %d", k + 1, ans[k][0]);
			for ( int j = 1; j < ans[k].size(); ++j )
				printf(" %d", ans[k][j]);
			puts("");
		}
		printf("total: %d\n", sum_all);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
