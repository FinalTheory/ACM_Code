/**
 * @file POJ_1251.cpp
 * @brief   �ֵ���ģ���⣬�ڵ��¼���ʸ���
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char buffer[50];

//Ԥ������ĸ���Լ���ʼ��ĸ
const int sonnum = 26, base = 'a';

struct Trie{
	int num;	//��¼�ж��ٸ������ܵ����Ҳ����ͬǰ׺�ĸ�λ
	bool term;	//�ж��Ƿ��Ѿ�����һ������
	struct Trie *son[sonnum];
	Trie()
	{
		num = 1; term = false;
		memset(son,NULL,sizeof(son));
	}
};
//�������н����Ľڵ�ָ�룬��ɺ�Ҫ�ͷ�
stack<Trie *> pointers;

void Insert( Trie * root, char * s )
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
}

int Search( Trie * root, char * s )
{
	Trie * temp = root;
	while( *s )
	{
		if( temp->son[*s - base] != NULL ) 
			temp = temp->son[*s - base];
		else
			return 0;
		s++;
	}
	return temp->num;
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
	Trie * root = new Trie;
	while (true)
	{
		gets(buffer);
		if ( buffer[0] == 0 ) break;
		Insert( root, buffer );
	}
	while ( scanf("%s", buffer) != EOF )
	{
		printf("%d\n", Search(root, buffer));
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
