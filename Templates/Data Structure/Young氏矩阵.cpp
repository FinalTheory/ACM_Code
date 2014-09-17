/**
 * @file Young氏矩阵.cpp
 * @brief   算法导论课后题6-3
 * @hint    一个类似优先队列的数据结构
 * @feeling 算导上面的伪代码的确千锤百炼啊……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-08-31
 */

const int m = 5, n = 5;

class Young
{
public:
    static const int INF = 0x3f3f3f3f;
    Young()
    {
        CLR(data, 0x3f);
    }
    bool Insert_Val( int val )
    {
        if ( this->data[m - 1][n - 1] != Young::INF ) return false;
        this->data[m - 1][n - 1] = val;
        Young_Adjust_In(m - 1, n - 1);
        return true;
    }
    int Extract_Min()
    {
        int result = this->data[0][0];
        this->data[0][0] = Young::INF;
        this->Young_Adjust_Out(0, 0);
        return result;
    }
    void FormatOutput()
    {
        rep(i, m) {
            rep(j, n) printf("%d ", this->data[i][j]);
            puts("");
        }
    }
    bool CheckLegal()
    {
        rep(i, m) {
            rep(j, n - 1) if ( this->data[i][j] > this->data[i][j + 1] ) return false;
        }
        rep(j, n) {
            rep(i, m - 1) if ( this->data[i][j] > this->data[i + 1][j] ) return false;
        }
        return true;
    }
private:
    int data[m][n];
    void Young_Adjust_Out(int row, int col)
    {
        int min_r, min_c = col;
        if ( row + 1 < m && this->data[row + 1][col] < this->data[row][col] ) {
            min_r = row + 1;
        } else {
            min_r = row;
        }
        if ( col + 1 < n && this->data[row][col + 1] < this->data[min_r][min_c] ) {
            min_r = row;
            min_c = col + 1;
        }
        if ( min_r != row || min_c != col ) {
            swap(this->data[row][col], this->data[min_r][min_c]);
            Young_Adjust_Out(min_r, min_c);
        }
    }
    void Young_Adjust_In(int row, int col)
    {
        int max_r, max_c = col;
        if ( row - 1 >= 0 && this->data[row - 1][col] > this->data[row][col] ) {
            max_r = row - 1;
        } else {
            max_r = row;
        }
        if ( col - 1 >= 0 && this->data[row][col - 1] > this->data[max_r][max_c] ) {
            max_r = row;
            max_c = col - 1;
        }
        if ( max_r != row || max_c != col ) {
            swap(this->data[row][col], this->data[max_r][max_c]);
            Young_Adjust_In(max_r, max_c);
        }
    }
};

Young Test;

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
#endif
    srand(time(NULL));
    rep(i, m * n) {
        int num = rand() % Young::INF;
        Test.Insert_Val(num);
    }
    Test.FormatOutput();
    if ( Test.CheckLegal() ) puts("The matrix is legal!");
    else puts("The matrix is unlegal!");
    rep(i, m * n) printf("%d ", Test.Extract_Min());
    puts("");
}
