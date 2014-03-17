/**
 * @file POJ_1699.cpp
 * @brief   略
 * @hint    遗传算法求解
 * @feeling qsort能A但是sort就WA，这你敢信？！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-02-03
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

int get_dist( char * a, char * b )
{
	int len_A = strlen(a);
	int len_B = strlen(b);
	int len;
	rep(i, len_A)
	{
		len = 0;
		rep(j, len_A - i)
		{
			if ( j >= len_B ) break;
			if ( a[i + j] == b[j] ) len++;
			else break;
		}
		if ( len == len_A - i ) return len;
	}
	return 0;
}

const int MAX = 12;
const int Size = 128;
const int K = 64;
const int KK = 48;
const int Age = 4096;
const int Pm = 20;

char DNA[MAX][24];
int _map[MAX][12], n;


inline void _swap( int * a, int * b )
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

typedef struct TMD
{
	int res[MAX], val;
	void init()
	{
		int a, b;
		rep(i, n) res[i] = i;
		rep(i, n)
		{
			a = rand() % n;
			b = rand() % n;
			_swap(res + a, res + b);
		}
		this->fitness();
	}
	void Mutate()
	{
		int a, b;
		if ( rand() % 100 < Pm )
		{
			a = rand() % n;
			b = rand() % n;
			_swap(res + a, res + b);
		}
		this->fitness();
	}
	void fitness()
	{
		val = 0;
		REP(i, 1, n) val += _map[res[i - 1]][res[i]];
	}
} Gene;

Gene Population[Size];
Gene * Pop[Size];

typedef int (*CMP)(const void *,const void *);

int Cmp(Gene **a,Gene **b)
{
    return (*b)->val - (*a)->val;
}

bool fuck( const Gene * a, const Gene * b )
{
	return a->val > b->val;
}

void CrossOver( Gene * a, Gene * b )
{
	int down = rand() % n;
	int up = rand() % n;
	int pos1[MAX], p1 = 0, pos2[MAX], p2 = 0;
	rep(i, n)
	{
		if ( down <= a->res[i] && a->res[i] <= up )
			pos1[p1++] = i;
		if ( down <= b->res[i] && b->res[i] <= up )
			pos2[p2++] = i;
	}
	rep(i, min(p1, p2))
		_swap(&(a->res[pos1[i]]), &(b->res[pos2[i]]));
}

int I_am_God()
{
	//srand(time(NULL));
	rep(i, Size)
	{
		Pop[i] = Population + i;
		Pop[i]->init();
	}
	rep(t, Age)
	{
		//sort(Pop, Pop + Size, fuck);
		qsort(Pop,Size,sizeof(Pop[0]),(CMP)Cmp);
		for ( int i = K; i < Size; i += 2 )
		{
			*Pop[i] = *Pop[rand() % K];
			*Pop[i + 1] = *Pop[rand() % K];
			CrossOver(Pop[i], Pop[i + 1]);
		}
		REP(i, KK, Size) (Pop[i])->Mutate();
	}
	return (Pop[0])->val;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
	int T = INT(), len;
	while ( T-- )
	{
		CLR(_map, 0);
		len = 0;
		n = INT();
		rep(i, n)
		{
			scanf("%s", DNA[i]);
			len += strlen(DNA[i]);
		}
		rep(i, n)
		rep(j, n) if ( i != j )
			_map[i][j] = get_dist(DNA[i], DNA[j]);
		int ans = I_am_God();
		printf("%d\n", len - ans);
	}
}
