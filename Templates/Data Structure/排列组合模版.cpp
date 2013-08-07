/*
	���������㷨���õݹ鷨����ʹ���ֵ�����ֱ��ʹ��STL����Ӧ������
	����㷨����01ת������������m��ѡn��������Ҫȫ�����ֱ��ʹ�ö�����ת�������ɡ�
	����㷨�ĵݹ�ʵ�ֲ���д�ˣ����е��������ЧһЩ��
*/
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)
using namespace std;
unsigned sum;

template <typename Any>
void swap( Any * a, Any * b )
{
	Any temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

template <typename Any>
//n������ʼԪ��λ��(Ĭ�ϴ��㿪ʼ)��num����Ԫ���ܸ�����
void perm( Any array[], int n, int num )
{
	if ( n == num )
	{
		output( array, num );
		sum++;
		return;
	}
	for ( int i = n; i < num; i++ )
	{
		swap( array + n, array + i );
		perm( array, n + 1, num );
		swap( array + n, array + i );
	}
}
template <typename Any>
//n��ʾѡ�����ٸ�Ԫ�أ�num��ʾ��Ԫ�ظ�����ע��num>1.
void combine( Any array[], int n, int num )
{
	int i, zeros, end, loop = 1;
	char * flags = new char [num];
	memset(flags, 0, sizeof(char) * num);
	for ( i = 0; i < n; i++ )
		flags[i] = 1;
	if ( n != num )
		output( array, flags, num );
	while ( loop )
	{
// 		for ( i = 0; i < num; i++ )
// 			cout << (int) flags[i] << ' ';
// 		cout << endl;
		for ( i = 0; i < num - 1; i++ )
			if ( flags[i] && !flags[i+1] )
			{
				flags[i] = 0;
				flags[i+1] = 1;
				break;
			}
		end = i;zeros = 0;
		for ( i = 0; i < end; i++ )
			if ( flags[i] )
				zeros++;
		for ( i = 0; i < end; i++ )
			if ( zeros )
			{
				flags[i] = 1;
				zeros--;
			}
			else
				flags[i] = 0;
		output( array, flags, num );
		loop = 0;
		for ( i = num - 1; i >= num - n; i-- )
			if ( !flags[i] )
			{
				loop = 1;
				break;
			}
	}
	delete [] flags;
}
template <typename Any>
//nΪҪѡ����Ԫ�أ�mΪ��ѡ����result[]�������������䣬��¼ѡ������Ŀλ�ã�M=n��
void combine( Any array[], int position[], int n, int m, const int M )
{
	for( int i = m - 1; i >= n - 1; i-- )

	{
		position[n-1] = i;
		if ( n > 1 )
			combine( array, position, n - 1, i, M );
		else
		{

			for( int j = M - 1; j >= 0; j-- )
				cout << array[position[j]] << " ";
			cout << endl;
			++sum;
		}
	}
}
template <typename Any>
void output( Any array[], int num )
{
	for ( int i = 0; i < num; i++ )
		cout << array[i] << ' ';
	cout << endl;
}
template <typename Any>
void output( Any array[], char flags[], int num )
{
	for ( int i = 0; i < num; i++ )
		if ( flags[i] )
			cout << array[i] << ' ';
	sum++;
	cout << endl;
}

int main()
{
	int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int pos[10];
	//combine( nums, 6, 10 );
	combine( nums, pos, 3, 10, 3 );
	cout << "Total: " << sum << endl;
}
