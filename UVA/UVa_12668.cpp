/**
 * @file UVa_12668.cpp
 * @brief   �˻ʺ�ľ�����չ���⣬����ת��Ϊ����ͼ�����ƥ�䡣
 * @hint    ������ȷ����ͼ�Ķ��壬������Խ�ͼ�нڵ��Ϊ�������ϣ�
 *	    ͼ��ÿһ���ߵ���������һ�������������ϣ���ô���ͼ���Ƕ���ͼ��
 *	    ������������������еĶ����ñ߶�Ӧ����������ÿ������ֻ��һ���ߣ���ô�߼����Ƕ���ͼ��ƥ�䡣
 *	    Ҳ���൱�ڽ������㼯�еĵ㡰ƥ�䡱�����������б�������ƥ���Ϊ����ͼ�����ƥ�䡣
 *	    ��ĿҪ����ͬ�л���ͬ�в��ܷ���һ���ʺ�
 *	    ���û����Щ��ǽ������ô����һ���ʺ��λ�ã�ͬ��ͬ�ж������ٷ��á�
 *	    Ҳ���൱���κ�һ��������ֻ����һ����Ӧ�����λ��ֻ�ܷ�һ���ʺ�
 *	    �����������к���Ϊ�ڵ�����ͼ��������ÿһ�����Ӧһ��(��, ��)�ıߣ���Ȼ���ͼ�Ƕ���ͼ��
 *	    �������ʺ�İڷŷ�ʽ�Ͷ�Ӧ��һ��ͼ�����ƥ�䣺
 *	    ��Ϊ�Ѿ�ƥ���˵��к��оͲ������������ཻ���л�����ƥ�䣬������ͻ������������ͼ��n��n�У�
 *	    ��ô1-1,2-2...n-n����һ�����ƥ�䣬��Ӧ��һ���������Խ��ߵİڷŷ�ʽ��
 *	    ͬ��1-n,2-n-1...n-1Ҳ��һ�����ƥ�䣬��Ӧ�����Ÿ��Խ��ߵķ�ʽ��
 *	    �ٿ��ǰڷ���ǽ�����������������ߣ�ÿ��ǽ�൱�ڽ�һ�����С��ڵ����һ�����С��ڵ�����������
 *	    ԭ��������NxN�����̣�������N���нڵ��N���нڵ㣻
 *	    ����ڵ�N-1��λ�÷�һ��ǽ����ô���൱�ڵ�һ���нڵ㱻����������ڵ㣨����˵���Σ���
 *	    ����һ����1~N-2������һ�ξ���N������ͼ�й���N+1���нڵ��N���нڵ㡣
 *	    ����������˼�룬ͬ�������ͼ�����ƥ�䣬�ó��ľ��ǰڷŵ����������
 * @feeling ˼·����ѧϰ�ˣ�
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-02
 */
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

char _map[110][110];
int e1[110][110], e2[110][110];
vector<int> Adja[21000];

int match[21000];
bool visited[21000];

bool DFS( int u )
{
	rep(i, Adja[u].size())
	{
		//ö�����u���ڵ����е㣨�ڽӱ�洢��
		int v = Adja[u][i];
		if ( !visited[v] )
		{
			visited[v] = true;
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungary( int N )
{
	int res = 0;
	CLR( match, -1 );
	for ( int u = 1; u <= N; ++u )
	{
		CLR(visited, 0);
		if ( DFS(u) ) res++;
	}
	return res;
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
    int n;
    while ( scanf("%d", &n) != EOF )
    {
        CLR(e1, 0); CLR(e2, 0);
        rep(i, n) scanf("%s", _map[i]);
        int idx = 0;
        rep(i, n)
        rep(j, n) if ( _map[i][j] == '.' ) {
            if ( j == 0 || _map[i][j] != _map[i][j - 1] ) e1[i][j] = ++idx;
            else e1[i][j] = e1[i][j - 1];
        }
        rep(j, n)
        rep(i, n) if ( _map[i][j] == '.' ) {
            if ( i == 0 || _map[i][j] != _map[i - 1][j] ) e2[i][j] = ++idx;
            else e2[i][j] = e2[i - 1][j];
        }
        rep(i, idx + 1) Adja[i].clear();
        rep(i, n)
        rep(j, n) if ( _map[i][j] == '.' ) {
            Adja[e1[i][j]].PB(e2[i][j]);
        }
        printf("%d\n", Hungary(idx));
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
