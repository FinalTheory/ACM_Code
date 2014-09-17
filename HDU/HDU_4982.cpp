/**
 * @file HDU_4982.cpp
 * @brief   һ������Ĺ�������
 * @hint    �ο�ע��
 * @feeling ��cha�ˣ����ơ�������Ҳcha�˱���
 * @author FinalTheory
 * @version 0.1
 * @date 2014-08-26
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

bool check( int num, int k, int rem )
{
    if ( rem == 0 ) return false;
    int inc = 1;
    //���ȳ���ǰ1~k-1�ĺͣ�����Ҫ�������Ϸ�ֵ
    //�����Щ�����Ѿ�װ���ˣ��������Ϊʧ��
    rep(i, k - 1) {
        if ( inc == rem ) inc++;
        if ( num <= inc ) return false;
        num -= inc;
        inc++;
    }
    //Ȼ�������һ���������
    //��Ϊ�ж���ǰ������������ٳ������⣬��һ�������һ����������
    while ( 1 ) {
        //��Ҫ�����һ��������ʣ���������ʧ��
        if ( num < inc ) return false;
        //ʣ����������ڲ��Ϸ�ֵ�����Ҵ��ڵ���inc����ô�Ϳ���ֱ����Ϊ���һ������ȷ���Ϸ�
        if ( num != rem ) return true;
        //����������㣬����������������ʣ�����
        //�������˼��˵���ѵ����ڶ�������ǰŲ���ٿ����һ�����ܷ�Ϸ�����
        inc++;
        num--;
    }
    return false;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int n, k;
    while ( cin >> n >> k )
    {
        bool found = false;
        for ( int i = 1; i * i <= n; i++ ) {
            int rem = n - i * i;
            if ( check(i * i, k - 1, rem) ) {
                found = true;
                break;
            }
        }
        if ( found ) puts("YES");
        else puts("NO");
    }
}
