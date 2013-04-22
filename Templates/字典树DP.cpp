/**
 * @file 字典树.cpp
 * @brief   辽宁省赛2010题目
 * 主要是字典树配合DP，这里对字符串进行了倒转以保证枚举时的正向。
 * 及时释放了字典树的空间，内存占用还是比较不错的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-22
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
#include <sstream>
#include <iomanip>
#include <stack>
#define MAX 10000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char buffer[MAX+10];
int len[1010], len_word;
int dp[MAX+10];

//预定义字母表以及起始字母
const int sonnum = 26, base = 'a';

struct Trie{
	int num;	//记录有多少个单词能到这里，也即相同前缀的个位
	bool term;	//判断是否已经构成一个单词
	int w;		//如果是单词节点的话，记录它的权重
	struct Trie *son[sonnum];
	Trie()
	{
		num = 1; term = false;
		memset(son,NULL,sizeof(son));
	}
};
//保存所有建立的节点指针，完成后要释放
stack<Trie *> pointers;

void Insert( Trie * root, char * s, int w )
{
	Trie * temp = root;
	while( *s )
	{
		if( temp->son[*s - base] == NULL )   //不存在，则建立子树
		{
			temp->son[*s - base] = new Trie();
			pointers.push(temp->son[*s - base]);	//保存指针
		}
		else 
			temp->son[*s - base]->num++;	//否则记录这里的单词数
		temp = temp->son[*s - base];
		s++;
	}
	temp->term = true;  //到达尾部，标记字符串结束
	temp->w = w;		//更新尾部的价值
}


int Search( Trie * root, char * s )
{
	Trie * temp = root;
	while( *s )
	{
		if( temp->son[*s - base] != NULL ) 
			temp = temp->son[*s - base];
		else
			return -1;
		s++;
	}
	if ( temp->term )
		return temp->w;
	else
		return -1;
}

void reverse( char * str )
{
	char tmp;
	for ( int i = 0, j = strlen(str) - 1; i < j; ++i, --j )
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
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
	char word[40];
	Trie * root;
	int n, i, j, w;
	
	while ( cin >> n )
	{
		CLR( buffer, 0 );
		CLR( dp, 0 );
		while ( !pointers.empty() )
		{
			delete pointers.top();
			pointers.pop();
		}
		root = new Trie();
		pointers.push(root);
		cin >> buffer;
		reverse(buffer);
		len_word = strlen(buffer);
		for ( i = 0; i < n; ++i )
		{
			cin >> word >> w;
			Insert( root, word, w );
		}
		//cout << Search( root, "a" ) << endl;
		Trie * tmp;
		for ( i = 0; i < len_word; ++i )
		{
			//现在的做法是枚举字符串位置和单词，只需要改成一直向前查找，每次成功的时候
			//更新一下情况就可以了，失败了就停止。尼玛劳资没怎么看过查找树啊……
			tmp = root;
			for ( j = i; j >= 0; --j )
			{
				tmp = tmp->son[buffer[j] - base];
				if ( tmp == NULL )	//失败的话就停止匹配
					break;
				if ( tmp->term )
				{
					if ( j != 0 )
					{
						if ( dp[j-1] > 0 && dp[i] < dp[j-1] + tmp->w )
							dp[i] = dp[j-1] + tmp->w;
					}
					else
					{
						if ( dp[i] < tmp->w )
							dp[i] = tmp->w;
					}
				}
			}
		}
		if ( dp[len_word - 1] > 0 )
		{
			cout << dp[len_word - 1] << endl;
		}
		else
			cout << "-1" << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
