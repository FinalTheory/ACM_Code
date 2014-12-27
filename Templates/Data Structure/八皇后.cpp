#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SIZE 50
using namespace std;
char map1[SIZE];	//记录纵坐标方向有没有放置皇后。
char map2[SIZE];	//记录主对角线方向有没有放置皇后。
char map3[SIZE];	//记录副对角线方向有没有放置皇后。
int N;	//棋盘大小
int K;	//皇后数目
unsigned long long sum;	//方法总数

//num既表示当前已经放置的皇后数目，也表示已经放到了第几列。
//利用num的增大就可以遍历横坐标方向，也就是按列放皇后。
void DFS( int num )
{
	if ( num == K )
	{
		 sum++;
		 return;
	}
	//遍历纵坐标方向。
	for ( int i = 0; i < N; i++ )
		if ( !map1[i] && !map2[num - i + N - 1] && !map3[num + i] )	//这里(num - i + N - 1)中的-1是为了让map2从0开始记录。
		{
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 1;	//设置标记
			DFS(num + 1);
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 0;	//回溯
		}
}

int main()
{
	while( cin >> N >> K )
	{
		sum = 0;
		memset(map1, 0, sizeof(map1));
		memset(map2, 0, sizeof(map2));
		memset(map3, 0, sizeof(map3));
		DFS(0);
		cout << sum << endl;
	}
}


//下面是一种可以输出方案的解法，核心思路跟上面一样，是在LeetCode上面提交的代码
class Solution {
public:
    static const int MAX = 100;
    bool flag[MAX], diag1[2*MAX-1], diag2[2*MAX-1];
    char mp[MAX][MAX];
    vector<vector<string> > res;
    vector<vector<string> > solveNQueens(int n) {
        res.clear();
        CLR(flag, 0);
        CLR(diag1, 0);
        CLR(diag2, 0);
        rep(i, n) rep(j, n) mp[i][j] = '.';
        DFS(0, n);
        return res;
    }
    void DFS( int col, int n )
    {
        if ( col >= n ) {
            vector<string> cur;
            rep(i, n) cur.PB(string(mp[i]));
            res.PB(cur);
            return;
        }
        rep(row, n) {
            if ( flag[row] || diag1[n - row + col - 1] || diag2[row + col] ) continue;
            flag[row] = true;
            diag1[n - row + col - 1] = true;
            diag2[row + col] = true;
            mp[row][col] = 'Q';
            DFS(col + 1, n);
            flag[row] = false;
            diag1[n - row + col - 1] = false;
            diag2[row + col] = false;
            mp[row][col] = '.';
        }
    }
};
