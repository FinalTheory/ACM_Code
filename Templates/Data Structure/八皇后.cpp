#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SIZE 50
using namespace std;
char map1[SIZE];	//��¼�����귽����û�з��ûʺ�
char map2[SIZE];	//��¼���Խ��߷�����û�з��ûʺ�
char map3[SIZE];	//��¼���Խ��߷�����û�з��ûʺ�
int N;	//���̴�С
int K;	//�ʺ���Ŀ
unsigned long long sum;	//��������

//num�ȱ�ʾ��ǰ�Ѿ����õĻʺ���Ŀ��Ҳ��ʾ�Ѿ��ŵ��˵ڼ��С�
//����num������Ϳ��Ա��������귽��Ҳ���ǰ��зŻʺ�
void DFS( int num )
{
	if ( num == K )
	{
		 sum++;
		 return;
	}
	//���������귽��
	for ( int i = 0; i < N; i++ )
		if ( !map1[i] && !map2[num - i + N - 1] && !map3[num + i] )	//����(num - i + N - 1)�е�-1��Ϊ����map2��0��ʼ��¼��
		{
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 1;	//���ñ��
			DFS(num + 1);
			map1[i] = map2[num - i + N - 1] = map3[num + i] = 0;	//����
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


//������һ�ֿ�����������Ľⷨ������˼·������һ��������LeetCode�����ύ�Ĵ���
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
