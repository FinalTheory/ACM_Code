/**
 * @file HDU_4907.cpp
 * @brief   无修改的最前空位查询
 * @hint    从后向前遍历并记录位置即可
 * @feeling 居然还写了个线段树，明明没有修改啊，还TLE了……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-08-04
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

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef priority_queue<int, std::vector<int>, std::greater<int> > MPQ;

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

#define MAX 200010

bool flag[MAX];
int res[MAX];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int n, m;
    int T;
    scanf("%d", &T);
    while ( T-- ) {
        scanf("%d %d", &n, &m);
        int val;
        CLR(flag, 0); CLR(res, 0);
        rep(i, n) {
            scanf("%d", &val);
            flag[val] = true;
        }
        res[200001] = 200001;
        rev(i, 200001) {
            if ( !flag[i] ) {
                res[i] = i;
            } else {
                res[i] = res[i + 1];
            }
        }
        rep(i, m) {
            scanf("%d", &val);
            printf("%d\n", res[val]);
        }
    }
}
