/**
 * @file HDU_3836.cpp
 * @brief   ǿ��ͨ����������
 * @hint    ����������Ӷ��ٸ�֤�������ܹ�ʹ�ü�������֤��Ϊȫ�ȣ�
 *	    Ҳ��������Ӷ��ٱ��ܹ�ʹ��ͼ��Ϊǿ��ͨ��
 *	    �õ���һ�����ʣ���a��b��ΪΪ��ȡ�����Ϊ��ĵ�ĸ���������Ҫ��ӵı���Ϊmax(a, b)
 *	    ע�⵱ֻ��һ��ǿ��ͨ������ʱ����Ҫ�ӱߡ�
 * @feeling һ��ʼ�����ɲ��鼯�ˣ�ģ���Ⱑ���꣬�壡
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-01
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

#define MAX_v 20010
#define MAX_e 50010

struct TMD
{
    int x, y;
} edges[MAX_e];

//������ڵ������Լ�ʱ�������
int LOW[MAX_v], DFN[MAX_v];
//����Ƿ���ջ��
bool Instack[MAX_v];
//��¼������ǿ��ͨ����
int Belong[MAX_v];
//ʱ�������
int TimeStamp;
//Vector�洢�ڽӱ�
vector<int> Adja[MAX_v];
//DFS������ջ
stack<int> Stack;
//����ǿ��ͨ��������
int ans;
//ͳ����Ⱥͳ���
int In[MAX_v], Out[MAX_v];

void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	Stack.push(u); Instack[u] = true;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		}
		else if ( Instack[v] )
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] )
	{
		++ans;
		do
		{
			v = Stack.top();
			Stack.pop();
			Instack[v] = false;
			Belong[v] = ans;
		} while ( v != u );
	}
}
int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
    int n, m;
    while ( scanf("%d %d", &n, &m) != EOF )
    {
        int x, y;
        rep(i, n + 1) Adja[i].clear();
        rep(i, m)
        {
            scanf("%d %d", &x, &y);
            edges[i].x = x;
            edges[i].y = y;
            Adja[x].PB(y);
        }
        while ( !Stack.empty() ) Stack.pop();
		CLR( DFN, 0 ); CLR( Instack, 0 );
		TimeStamp = 0; ans = 0;
		REP(i, 1, n + 1) if ( !DFN[i] )
            Tarjan(i);
        CLR(In, 0); CLR(Out, 0);
        rep(i, m) if ( Belong[edges[i].x] != Belong[edges[i].y] )
        {
            Out[Belong[edges[i].x]]++;
            In[Belong[edges[i].y]]++;
        }
        int res1 = 0, res2 = 0;
        REP(i, 1, ans + 1)
        {
            if ( !In[i] ) res1++;
            if ( !Out[i] ) res2++;
        }
        if ( ans == 1 ) puts("0");
        else printf("%d\n", max(res1, res2));
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
