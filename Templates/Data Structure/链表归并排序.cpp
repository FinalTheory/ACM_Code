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


struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

void output(ListNode * p) {
    while ( p != NULL ) {
        printf("%d ", p->val);
        p = p->next;
    }
    puts("");
}

class Solution {
public:
    ListNode *sortList(ListNode * head) {
        if ( head == NULL || head->next == NULL ) return head;
        ListNode * Left, * Right;
        PartitionList(head, &Left, &Right);
        Left = sortList(Left);
        Right = sortList(Right);
        head = MergeList(Left, Right);
        return head;
    }
    void PartitionList( ListNode * head, ListNode ** Left, ListNode ** Right ) {
        ListNode * p_slow = head, * p_fast = head->next, * p_prev = NULL;
        while ( p_fast != NULL ) {
            p_prev = p_slow;
            p_fast = p_fast->next;
            p_slow = p_slow->next;
            if ( p_fast != NULL ) p_fast = p_fast->next;
        }
        if ( p_prev != NULL ) p_prev->next = NULL;
        *Left = head;
        *Right = p_slow;
    }
    ListNode * MergeList( ListNode * Left, ListNode * Right ) {
        if ( Left == NULL ) return Right;
        if ( Right == NULL) return Left;
        ListNode * head, * p;
        if ( Left->val <= Right->val ) {
            head = Left;
            Left = Left->next;
        } else {
            head = Right;
            Right = Right->next;
        }
        p = head;
        while ( Left != NULL && Right != NULL ) {
            if ( Left->val <= Right->val ) {
                p->next = Left;
                p = p->next;
                Left = Left->next;
            } else {
                p->next = Right;
                p = p->next;
                Right = Right->next;
            }
        }
        if ( Left == NULL ) p->next = Right;
        if ( Right == NULL ) p->next = Left;
        return head;
    }
};

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    srand(time(NULL));
    ListNode * head = new ListNode(rand()), * p = head;
    rep(i, 10000000) {
        p->next = new ListNode(rand());
        p = p->next;
    }
    p->next = NULL;
    //output(head);
    Solution Test;
    head = Test.sortList(head);
    //output(head);
}
