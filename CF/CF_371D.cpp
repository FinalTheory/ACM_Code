/**
 * @file CF_371D.cpp
 * @brief   实际上就是一个并查集问题。
 *	    某个节点的根节点表示倒入这里的水实际上被倒入了哪里，然后做对应增减即可。
 *	    注意路径压缩。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-12-10
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
using namespace std;

#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define SQR(x) ((x)*(x))
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REV(i,a,b) for(int i=a-1;i>=b;i--)
#define rep(i,n) REP(i,0,n)
#define rev(i,n) REV(i,n,0)
#define ITER(i,x) for(typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define ALL(v) v.begin(),v.end()
#define PB push_back
#define MP make_pair
#define PQ priority_queue
#define MPQ priority_queue<int, std::vector<int>, std::greater<int> >
#define MAX 200010

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const double PI = 3.141592653589793238;
const double eps = 1e-9;

inline int INT()
{
    register int c = getchar();
    int x = 0;
    for( ; ( c < 48 || c > 57 ); c = getchar() );
    for( ; ( c > 47 && c < 58 ); c = getchar() ) x = x * 10 + c - 48;
	return x;
}

int a[MAX], Tree[MAX], v[MAX], n;

int find_root_2(int v){
    if(Tree[v]!=v)
        Tree[v]=find_root_2(Tree[v]);
    return Tree[v];
}

int find_root( int x )
{
	int root = x;
	while ( Tree[root] != root )
		root = Tree[root];
	int i = x, j;
	while ( i != root )
	{
		j = Tree[i];
		Tree[i] = root;
		i = j;
	}
	return root;
}

void Update( int p, int x )
{
	int root = find_root(p);
	while ( root != n + 1 )
	{
		if ( v[root] + x <= a[root] )
		{
			v[root] += x;
			return;
		}
		else
		{
			Tree[root] = Tree[root + 1];
			x -= a[root] - v[root];
			v[root] = a[root];
			if ( x == 0 ) return;
		}
		root = find_root(root);
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
	int t, p, x, k, m;
	n = INT();
	rep(i, n)
	{
		Tree[i + 1] = i + 1;
		a[i + 1] = INT();
	}
	Tree[n + 1] = n + 1;
	m = INT();
	rep(i, m)
	{
		t = INT();
		if ( t == 1 )
		{
			p = INT();
			x = INT();
			Update(p, x);
		}
		else
		{
			k = INT();
			printf("%d\n", v[k]);
		}
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
