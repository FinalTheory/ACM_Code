/**
 * @file POJ_2828_2.cpp
 * @brief   SB树模版测试，使用功能：删除第k元素。
 * @author FinalTheory
 * @version 0.2
 * @date 2013-08-14
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
#define MAX 200010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const unsigned INF = 0xffffffff;
// Template for Operator Overloading
struct Node
{
	int key, priority, idx;
	Node() {}
	Node(int a,int b) :key(a), priority(b) {}
	bool operator < (Node b) {
		return priority < b.priority;
	}
	bool operator == (Node b) {
		return priority == b.priority;
	}
	Node operator + (int a) {
		return Node(key , priority + a);
	}
};
template <typename Type>
class SizeBalancedTree
{
public:
	struct Node
	{
		Type Key;
		int L_son, R_son, Size;
	} Tree[MAX];
	void clear()
	{
		root = 0;
		index = 0;
		Tree[root].Size = 0;
		Tree[root].L_son = Tree[root].R_son = 0;
	}
	int get_root() {return root;};
	int size() {return Tree[root].Size;}
	bool empty() {return root == 0;}
	bool find( Type Key ) {return Find(root, Key);}
	// Insert elements
	void insert( Type Key ) {Insert( root, Key );}
	// Remove elements
	void remove( Type Key ) {Delete( root, Key );}
	// Remove elements smaller than Key
	void remove_smaller( Type Key ) {Delete_Smaller(root, Key);}
	int rank( Type Key ) {return Rank( root, Key );}
	// Select the k-th element in ascending order
	Type select( int k ) {return Select( root, k );}
	Type remove_select( int k ) {return Delete_Select(root, k);}
	// Find predecessor and successor, return the Key itself when failed
	Type predecessor( Type Key ) {return Predecessor( root, Key );}
	Type successor( Type Key ) {return Successor( root, Key );}
	// Get the min and max element in the tree
	Type get_min()
	{
		int temp = root;
		while ( Tree[temp].L_son ) temp = Tree[temp].L_son;
		return Tree[temp].Key;
	}
	Type get_max()
	{
		int temp = root;
		while ( Tree[temp].R_son ) temp = Tree[temp].R_son;
		return Tree[temp].Key;
	}
private:
	int index, root;
	bool Find( int & root, Type Key )
	{
		if ( root == 0 )
			return false;
		else if ( Key < Tree[root].Key )
			return Find( Tree[root].L_son, Key );
		else
			return( Tree[root].Key == Key || Find( Tree[root].R_son, Key ) );
	}
	void Insert( int & root, Type Key )
	{
		if ( root == 0 )
		{
			root = ++index;
			Tree[root].L_son = Tree[root].R_son = 0;
			Tree[root].Size = 1;
			Tree[root].Key = Key;
			return;
		}
		Tree[root].Size++;
		if ( Key < Tree[root].Key )
			Insert( Tree[root].L_son, Key );
		else
			Insert( Tree[root].R_son, Key );
		Maintain( root, !( Key < Tree[root].Key ) );
	}
	Type Delete( int & root, Type Key )
	{
		Tree[root].Size--;
		if ( Tree[root].Key == Key || \
			( Key < Tree[root].Key ) && Tree[root].L_son == 0 ||\
			( Tree[root].Key < Key && Tree[root].R_son == 0 ) ) {
			Type ret = Tree[root].Key;
			if ( Tree[root].L_son == 0 || Tree[root].R_son == 0 ) {
				// Discard the value of current node
				root = Tree[root].L_son + Tree[root].R_son;
			} else {
				Tree[root].Key = Delete( Tree[root].L_son, Tree[root].Key + 1 );
			}
			return ret;	
		}
		else {
			if ( Key < Tree[root].Key )
				Delete( Tree[root].L_son, Key );
			else
				Delete( Tree[root].R_son, Key );
		}
	}
	void Delete_Smaller( int & root, Type Key )
	{
		if ( root == 0 )
			return;
		if ( Tree[root].Key < Key ) {
			root = Tree[root].R_son;
			Delete_Smaller( root, Key );
		} else {
			Delete_Smaller( Tree[root].L_son, Key );
			Tree[root].Size = Tree[Tree[root].L_son].Size + Tree[Tree[root].R_son].Size + 1;
		}
	}
	Type Delete_Select( int & root, int K )
	{
		Tree[root].Size--;
		if ( Tree[Tree[root].L_son].Size + 1 == K ) {
			Type ret = Tree[root].Key;
			if ( Tree[root].L_son == 0 || Tree[root].R_son == 0 ) {
				root = Tree[root].L_son + Tree[root].R_son;
			} else {
				Tree[root].Key = Delete( Tree[root].L_son, Tree[root].Key + 1 );
			}
			return ret;
		} else if ( K > Tree[Tree[root].L_son].Size ) {
			return Delete_Select( Tree[root].R_son, K - 1 - Tree[Tree[root].L_son].Size );
		} else {
			return Delete_Select( Tree[root].L_son, K );
		}
	}
	Type Select( int & root, int K )
	{
		if ( Tree[Tree[root].L_son].Size + 1 == K )
			return Tree[root].Key;
		else if ( Tree[Tree[root].L_son].Size < K )
			return Select( Tree[root].R_son, K - 1 - Tree[Tree[root].L_son].Size );
		else
			return Select( Tree[root].L_son, K );
	}
	int Rank( int & root, Type Key )
	{
		if ( Tree[root].Key == Key )
			return Tree[Tree[root].L_son].Size + 1;
		else if ( Key < Tree[root].Key )
			return Rank( Tree[root].L_son, Key );
		else
			return Tree[Tree[root].L_son].Size + 1 + Rank( Tree[root].R_son, Key );
	}
	Type Predecessor( int & root, Type Key )
	{
		if ( root == 0 ) {
			return Key;
		} else if ( Tree[root].Key < Key ) {
			Type ret = Predecessor( Tree[root].R_son, Key );
			if ( ret == Key ) return Tree[root].Key;
			return ret;
		} else {
			return Predecessor( Tree[root].L_son, Key );
		}
	}
	Type Successor( int & root, Type Key )
	{
		if ( root == 0 ) {
			return Key;
		} else if ( Key < Tree[root].Key ) {
			Type ret = Successor( Tree[root].L_son, Key );
			if ( ret == Key ) return Tree[root].Key;
			return ret;
		} else {
			return Successor( Tree[root].R_son, Key );
		}
	}
	void Left_Rotate( int & root )
	{
		int tmp = Tree[root].R_son;
		Tree[root].R_son = Tree[tmp].L_son;
		Tree[tmp].L_son = root;
		Tree[tmp].Size = Tree[root].Size;
		Tree[root].Size = Tree[Tree[root].L_son].Size + Tree[Tree[root].R_son].Size + 1;
		root = tmp;
	}
	void Right_Rotate( int & root )
	{
		int tmp = Tree[root].L_son;
		Tree[root].L_son = Tree[tmp].R_son;
		Tree[tmp].R_son = root;
		Tree[tmp].Size = Tree[root].Size;
		Tree[root].Size = Tree[Tree[root].L_son].Size + Tree[Tree[root].R_son].Size + 1;
		root = tmp;
	}
	void Maintain( int & root, bool Flag )
	{
		if ( root == 0 )
			return;
		if ( Flag == false ) {
			if ( Tree[Tree[Tree[root].L_son].L_son].Size > Tree[Tree[root].R_son].Size ) {
				Right_Rotate(root);
			}
			else if ( Tree[Tree[Tree[root].L_son].R_son].Size > Tree[Tree[root].R_son].Size ) {
				Left_Rotate(Tree[root].L_son);
				Right_Rotate(root);
			}
			else {
				return;
			}
		} else {
			if ( Tree[Tree[Tree[root].R_son].R_son].Size > Tree[Tree[root].L_son].Size ) {
				Left_Rotate(root);
			}
			else if ( Tree[Tree[Tree[root].R_son].L_son].Size > Tree[Tree[root].L_son].Size ) {
				Right_Rotate(Tree[root].R_son);
				Left_Rotate(root);
			}
			else {
				return;
			}
		}
		Maintain( Tree[root].L_son, false );
		Maintain( Tree[root].R_son, true );
		Maintain( root, false );
		Maintain( root, true );
	}
};
SizeBalancedTree<int> Tree;
int ans[MAX], pos[MAX], val[MAX];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, res;
	while ( scanf("%d", &N) != EOF )
	{
		Tree.clear();
		for ( int i = 1; i <= N; ++i )
			Tree.insert(i);
		for ( int i = 0; i < N; ++i )
			scanf("%d %d", &pos[i], &val[i]), pos[i]++;
		for ( int i = N - 1; i >= 0; --i )
		{
			res = Tree.remove_select(pos[i]);
			ans[res] = val[i];
		}
		bool outed = false;
		for ( int i = 1; i <= N; ++i )
			if ( outed ) {
				printf(" %d", ans[i]);
			} else {
				outed = true;
				printf("%d", ans[i]);
			}
		puts("");
	}
	
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
