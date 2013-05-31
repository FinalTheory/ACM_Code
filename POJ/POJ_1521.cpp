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
#include <queue>
#include <stack>
#include <sstream>
#include <iomanip>
#define MAX 1000

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct Node
{
	char character;
	int weight;
	Node * L_son;
	Node * R_son;
	Node()
	{
		weight = 0;
		character = 0;
		L_son = R_son = NULL;
	}
};

bool operator < ( const Node & A, const Node & B )
{
	return A.weight > B.weight;
}

const int characters = 256;

int char_freq[characters];

int Huffman_len[characters];

char buffer[MAX];

int queue_res[MAX];
int p_queue;

void DFS( Node * root )
{
	if ( root->character )
	{
		Huffman_len[root->character] = p_queue;
// 		printf("%c ", root->character);
// 		for ( int i = 0; i < p_queue; ++i )
// 			printf( "%d", queue_res[i] );
// 		printf("\n");
		return;
	}
	if ( root->L_son != NULL )
	{
		queue_res[p_queue++] = 0;
		DFS( root->L_son );
		queue_res[p_queue--] = 0;
	}
	if ( root->R_son != NULL )
	{
		queue_res[p_queue++] = 1;
		DFS( root->R_son );
		queue_res[p_queue--] = 1;
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
	priority_queue<Node> Q;
	Node root, tmp, * head1, * head2;
	int len, sum;
	while ( gets(buffer) != NULL && strcmp( buffer, "END" ) )
	{
		while ( !Q.empty() ) Q.pop();
		CLR( char_freq, 0 );
		len = strlen(buffer);
		for ( int i = 0; i < len; ++i )
			char_freq[buffer[i]]++;
		for ( int i = 0; i < 256; ++i )
		{
			if ( char_freq[i] )
			{
				tmp.character = i;
				tmp.weight = char_freq[i];
				tmp.L_son = tmp.R_son = NULL;
				Q.push(tmp);
			}
		}
		while ( Q.size() >= 2 )
		{
			head1 = new Node;
			head2 = new Node;
			*head1 = Q.top(); Q.pop();
			*head2 = Q.top(); Q.pop();
			tmp.L_son = head1; tmp.R_son = head2;
			tmp.weight = head1->weight + head2->weight;
			tmp.character = 0;
			Q.push(tmp);
		}
		root = Q.top(); Q.pop();
		CLR( Huffman_len, 0 );
		p_queue = 0;
		DFS( &root );
		sum = 0;
		for ( int i = 0; i < len; ++i )
			sum += Huffman_len[buffer[i]];
		//注意只有一个字母的时候要专门处理！
		if ( sum )
			printf( "%d %d %.1lf\n", len * 8, sum, (len * 8) / (double)sum );
		else
			printf( "%d %d %.1lf\n", len * 8, len, 8.0 );
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
