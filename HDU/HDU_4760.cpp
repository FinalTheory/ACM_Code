/**
 * @file HDU_4760.cpp
 * @brief   字典树模拟
 * @hint    题意要求匹配满足的子网地址，相当于前缀匹配问题，所以建一颗字典树。
 *	    字典树每个节点用一个set记录到达这个节点时匹配的规则列表编号；
 *	    每条子网规则相当于一个01串，因此可以记录到达这个节点的规则的前缀长度。
 *	    这样对于源ip和目标ip，用set记录其所有能够匹配到的规则列表，对两个set取交集即可。
 * @feeling 第一次在网络赛中过掉这种难度的题目，不能更爽！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-29
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
#define MAX	33768
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;

const int sonnum = 2, base = '0';

struct TMD
{
	int prefix;
	string ip;
};

vector<TMD> rules[1100];

struct Trie{
	int prefix;
	set<int> rule_id;
	struct Trie *son[sonnum];
	Trie()
	{
		prefix = 0;
		rule_id.clear();
		memset(son,NULL,sizeof(son));
	}
};
void Insert( Trie * root, char * s, int prefix, int id )
{
	Trie * temp = root;
	while( *s )
	{
		if( temp->son[*s - base] == NULL )
			temp->son[*s - base] = new Trie();
		temp = temp->son[*s - base];
		s++;
	}
	temp->prefix = prefix;
	temp->rule_id.insert(id);
}

void Search( Trie * root, char * s, set<int> & matched )
{
	Trie * temp = root;
	matched.clear();
	int depth = 0;
	while( *s )
	{
		if ( temp->rule_id.size() && temp->prefix == depth )
			for ( set<int>::iterator iter = temp->rule_id.begin(); iter != temp->rule_id.end(); ++iter )
				matched.insert(*iter);
		if( temp->son[*s - base] != NULL ) 
			temp = temp->son[*s - base];
		else
			break;
		s++;
		depth++;
	}
}

void disable( Trie * root, const char * s, int id )
{
	Trie * temp = root;
	while( *s )
	{
		temp = temp->son[*s - base];
		s++;
	}
	temp->rule_id.erase(id);
}

char buffer[1000];

void num2str( int num, char * buffer )
{
	for ( int i = 0; i < 8; ++i )
	{
		if ( num & ( 1 << 7 - i ) )
			buffer[i] = '1';
		else
			buffer[i] = '0';
	}
	buffer[8] = 0;
}

int conv( char * res_ip, char * IP, bool type )
{
	int num[4], prefix;
	char res[10]; res[0] = 0; res_ip[0] = 0;
	if ( type )
	{
		sscanf(IP, "%d.%d.%d.%d/%d", &num[0], &num[1], &num[2], &num[3], &prefix);
		for ( int j = 0; j < 4; ++j )
		{
			num2str( num[j], res );
			strcat( res_ip, res );
		}
		return prefix;
	}
	else
	{
		sscanf(IP, "%d.%d.%d.%d", &num[0], &num[1], &num[2], &num[3]);
		for ( int j = 0; j < 4; ++j )
		{
			num2str( num[j], res );
			strcat( res_ip, res );
		}
		return 0;
	}
}

int output[MAX];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	char str[5], subnet[40], res_ip[40], ip1[40], ip2[40], res_ip1[40], res_ip2[40];
	set<int> mat_rules1, mat_rules2;
	int id, n;
	TMD tmp;
	istringstream iss;
	Trie * root = new Trie();
	while ( gets(buffer) != NULL )
	{
		if ( !buffer[0] ) continue;
		switch ( buffer[0] )
		{
		case 'E':
			iss.clear();
			iss.str(buffer);
			iss >> str >> id >> n;
			rules[id].clear();
			for ( int i = 0; i < n; ++i )
			{
				iss >> subnet;
				tmp.prefix = conv( res_ip, subnet, true );
				res_ip[tmp.prefix] = 0;
				tmp.ip = res_ip;
				rules[id].push_back(tmp);
				Insert( root, res_ip, tmp.prefix, id );
			}
			break;
		case 'F':
			sscanf( buffer, "%s %s %s", str, ip1, ip2 );
			conv( res_ip1, ip1, false );
			conv( res_ip2, ip2, false );
			Search( root, res_ip1, mat_rules1 );
			Search( root, res_ip2, mat_rules2 );
			if ( set_intersection( mat_rules1.begin(), mat_rules1.end(), mat_rules2.begin(), mat_rules2.end(), output) - output > 0 )
				puts("F");
			else
				puts("D");
			break;
		case 'D':
			sscanf(buffer, "%s %d", str, &id);
			for ( int i = 0; i < rules[id].size(); ++i )
			{
				strcpy( buffer, rules[id][i].ip.c_str() );
				disable( root, buffer, id );
			}
			break;
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
