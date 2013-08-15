/**
 * @file ZOJ_3430.cpp
 * @brief   AC自动机，解码后就是模版题
 * @input   base64编码后的关键词、待匹配文本
 * @output  文本中出现了多少个不同的关键字
 * @hint    注意输出时不要重复，开一个_hash数组去重，并且要一直回溯fail指针。
 *	    另外要注意的就是解码后存在'\0'这样的字符，所以要另开一个整型数组记录转码后的字符串。
 * @feeling 没想到编码转换居然写搓了，一直就WA在了这里，还有之前数组开小了吃了好几发段错误，气死了！ 
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-16
 */
// #if defined(__GNUC__)
// #pragma GCC optimize ("O2")
// #endif
// #if defined(_MSC_VER)
// #pragma comment(linker, "/STACK:36777216")
// #endif
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
const int set_num = 256;
const int set_base = 0;
char key[100];
//读入待匹配文本
char buffer[3000];
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

void Insert( Node * root, int * str, int len, int ID )
{
	int * p_str = str;
	Node * tmp = root;
	int pos = 0;
	while ( pos < len )
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
		++p_str; ++pos;
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
map<char, unsigned> table;
unsigned _value[2100];
bool bits[18000];
int _res[2100];
int decode( char * str )
{
	int len = strlen(str);
	for ( int i = 0; i < len; ++i ) if ( str[i] != '=' ) {
		_value[i] = table[str[i]];
	} else {
		len = i;
		break;
	}
	for ( int i = 0; i < len; ++i )
		for ( int j = 6 * i, k = 5; j < 6 * ( i + 1 ); ++j, --k )
			if ( (_value[i] >> k) & 1 ) {
				bits[j] = true;
			} else {
				bits[j] = false;
			}
	for ( int i = 0; i < ( 6 * len ) / 8; ++i )
	{
		unsigned res = 0;
		unsigned _inc = 1;
		for ( int j = 8 * i + 7; j >= 8 * i; --j )
		{
			res += bits[j] * _inc;
			_inc <<= 1;
		}
		_res[i] = res;
	}
	return ( 6 * len ) / 8;
}

int decode2( char *a ){
	int n=strlen( a ),i,p=0,cnt;
	for( cnt=0,i=n-1;a[ i ]=='=';cnt++,i-- );
	for( i=0;i<n;i+=4 ){       
		int temp=( table[ a[ i ] ]<<18 )|( table[ a[ i+1 ] ]<<12 )|( table[ a[ i+2 ] ]<<6 )|( table[ a[ i+3 ] ] );
		for( int j=2;j>=0;j-- ){
			_res[ p+j ]=temp&255;
			temp>>=8;
		}
		p+=3;
	}
	return p-cnt;
}
bool _hash[600];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
	int N, M;
	Node * root, * q;
	for ( char c = 'A'; c <= 'Z'; ++c )
		table[c] = c - 'A';
	for ( char c = 'a'; c <= 'z'; ++c )
		table[c] = c - 'a' + 26;
	for ( char c = '0'; c <= '9'; ++c )
		table[c] = c - '0' + 52;
	table['+'] = 62; table['/'] = 63;
	while ( scanf("%d", &N) != EOF )
	{
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = new Node;
		Pointers.push(root);
		for ( int i = 0; i < set_num; ++i )
			root->next[i] = root;
		for ( int i = 0; i < N; ++i )
		{
			scanf("%s", key);
			int len = decode2(key);
			Insert(root, _res, len, i + 1);
		}
		CreateFail(root);
		scanf("%d", &M);
		for ( int k = 0; k < M; ++k )
		{
			int sum = 0;
			CLR(_hash, 0);
			scanf("%s", buffer);
			int len = decode2(buffer);
			q = root;
			for ( int i = 0; i < len; ++i )
			{
				while ( q->next[_res[i] - set_base] == NULL )
					q = q->fail;
				q = q->next[_res[i] - set_base];
				Node * tmp = q;
				while ( tmp != root )
				{
					if ( tmp->ID && !_hash[tmp->ID] ) {
						sum++;
						_hash[tmp->ID] = true;
					}
					tmp = tmp->fail;
				}
			}
			printf("%d\n", sum);
		}
		puts("");
	}
}
