/**
 * @file �ֵ���.cpp
 * @brief   ����ʡ��2010��Ŀ
 * ��Ҫ���ֵ������DP��������ַ��������˵�ת�Ա�֤ö��ʱ������
 * ��ʱ�ͷ����ֵ����Ŀռ䣬�ڴ�ռ�û��ǱȽϲ���ġ�
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

//Ԥ������ĸ���Լ���ʼ��ĸ
const int sonnum = 26, base = 'a';

struct Trie{
	int num;	//��¼�ж��ٸ������ܵ����Ҳ����ͬǰ׺�ĸ�λ
	bool term;	//�ж��Ƿ��Ѿ�����һ������
	int w;		//����ǵ��ʽڵ�Ļ�����¼����Ȩ��
	struct Trie *son[sonnum];
	Trie()
	{
		num = 1; term = false;
		memset(son,NULL,sizeof(son));
	}
};
//�������н����Ľڵ�ָ�룬��ɺ�Ҫ�ͷ�
stack<Trie *> pointers;

void Insert( Trie * root, char * s, int w )
{
	Trie * temp = root;
	while( *s )
	{
		if( temp->son[*s - base] == NULL )   //�����ڣ���������
		{
			temp->son[*s - base] = new Trie();
			pointers.push(temp->son[*s - base]);	//����ָ��
		}
		else 
			temp->son[*s - base]->num++;	//�����¼����ĵ�����
		temp = temp->son[*s - base];
		s++;
	}
	temp->term = true;  //����β��������ַ�������
	temp->w = w;		//����β���ļ�ֵ
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
			//���ڵ�������ö���ַ���λ�ú͵��ʣ�ֻ��Ҫ�ĳ�һֱ��ǰ���ң�ÿ�γɹ���ʱ��
			//����һ������Ϳ����ˣ�ʧ���˾�ֹͣ����������û��ô����������������
			tmp = root;
			for ( j = i; j >= 0; --j )
			{
				tmp = tmp->son[buffer[j] - base];
				if ( tmp == NULL )	//ʧ�ܵĻ���ֹͣƥ��
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
