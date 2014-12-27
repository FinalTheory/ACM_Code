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

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef priority_queue<int, std::vector<int>, std::greater<int> > MPQ;

const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const double PI = 3.141592653589793238;
const double eps = 1e-9;

inline int INT()
{
	register int c = getchar();
	int x = 0;
	for ( ; (c < 48 || c > 57); c = getchar() );
	for ( ; (c > 47 && c < 58); c = getchar() ) x = x * 10 + c - 48;
	return x;
}


void contractionGraph( int rand_u, int rand_v, map<int, VI> & Adja )
{
	rep( i, Adja[rand_v].size() ) Adja[rand_u].PB( Adja[rand_v][i] );
	Adja.erase( Adja.find( rand_v ) );
	for ( map<int, VI> ::iterator iter = Adja.begin(); iter != Adja.end(); iter++ ) {
		rep( i, iter->second.size() ) if ( iter->second[i] == rand_v )
			iter->second[i] = rand_u;
	}
	VI temp;
	rep( i, Adja[rand_u].size() ) if ( Adja[rand_u][i] != rand_u )
		temp.PB( Adja[rand_u][i] );
	Adja[rand_u] = temp;
}

int Solve( map<int, VI> Adja )
{
	while ( Adja.size() > 2 )
	{
		VI keys;
		for ( map<int, VI> ::iterator iter = Adja.begin(); iter != Adja.end(); iter++ )
			keys.push_back( iter->first );
		int rand_u = keys[rand() % keys.size()];
		int rand_v = Adja[rand_u][rand() % Adja[rand_u].size()];
		contractionGraph( rand_u, rand_v, Adja );
	}
	return (Adja.begin())->second.size();
}

char buf[20000];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "kargerMinCut.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
	srand( time( NULL ) );
	int n = 200;
	map<int, VI> graph;
	rep( i, n ) graph[i] = vector<int>();
	rep( i, n )
	{
		int u, v;
		gets( buf );
		istringstream iss( buf );
		iss >> u;
		while ( iss >> v ) graph[u - 1].PB( v - 1 );
	}
	int ans = INF, cur;
	rep( i, 1000 )
	{
		if ( (cur = Solve( graph )) < ans ) ans = cur;
	}
	cout << ans << endl;
}
