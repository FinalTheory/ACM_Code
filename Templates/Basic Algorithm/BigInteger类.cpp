/**
 * @file BigInteger��.cpp
 * @brief   һ��ģ��Java�������������C++ʵ��
 * @hint    Ϊ�˷��㣬˫Ŀ������ʹ����Ԫ�������أ�
 *	    ����ʹ����cin/cout����˹ر�����stdio��ͬ����
 *	    �����������I/OЧ�ʣ����ǲ�����ʹ��scanf()/printf()��
 *	    MAXDIGITS������������󳤶ȣ�����˷�ʱ��Ҫע�����ݵĳ��ȡ�
 * @author FinalTheory
 * @version 0.1
 * @date 2012-07-13
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <ctime>
#define MAXDIGITS 1010		
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)
using namespace std;

class BigInteger
{
	private:
		char digits[MAXDIGITS];	//���ַ�����洢��������
		signed char signbit;	//����λ��
		int lastdigit;			//ָ�����λ��
	public:
		BigInteger(){ initialize(); }
		BigInteger( int N )
		{
			int len, i, j;
			char c;
			if ( N < 0 )
			{
				signbit = -1;
				N = -N;
			}
			else
				signbit = 1;
			sprintf( digits, "%d", N );
			len = strlen( digits );
			lastdigit = len - 1;
			for ( i = len - 1, j = 0; i > j; i--, j++ )
			{
				c = digits[i];
				digits[i] = digits[j];
				digits[j] = c;
				digits[i] -= '0';
				digits[j] -= '0';
			}
			if ( len % 2 )
				digits[len / 2] -= '0';
		};
		void zero_justify();												//ȥ���ȵ���
		void initialize();													//��ʼ������
		const BigInteger & operator = ( const BigInteger & );							//���ظ�ֵ
		friend bool operator > ( BigInteger &, BigInteger & );				//���ش���
		friend istream & operator >> ( istream & is, BigInteger & );		//��������
		friend ostream & operator << ( ostream & os, const BigInteger & );	//�������
		friend BigInteger   operator <<  ( BigInteger &, int );				//������λ
		friend BigInteger & operator <<= ( BigInteger &, int );
		friend BigInteger operator + ( BigInteger &, BigInteger & );		//���ؼӷ�
		friend BigInteger operator - ( BigInteger &, BigInteger & );		//���ؼ���
		friend BigInteger operator * ( BigInteger &, BigInteger & );		//���س˷�
		friend BigInteger operator / ( BigInteger &, BigInteger & );		//���س���
		friend BigInteger operator % ( BigInteger &, BigInteger & );		//������ģ
		friend BigInteger operator * ( BigInteger &, long long );
		friend BigInteger operator / ( BigInteger &, long long );
		friend BigInteger operator * ( long long, BigInteger & );
		friend BigInteger operator ^ ( BigInteger, int );					//��������
};

void BigInteger :: zero_justify()
{
	while ( lastdigit > 0 && digits[lastdigit] == 0 )
		--lastdigit;
	if ( lastdigit == 0 && digits[0] == 0 )
		signbit = 1;
}

void BigInteger :: initialize()
{
	//��������ʼ��Ϊ0
	signbit = 1;
	lastdigit = 0;
	memset( digits, 0, sizeof(digits) );
}

const BigInteger & BigInteger :: operator = ( const BigInteger & B )
{
	signbit = B.signbit;
	lastdigit = B.lastdigit;
	memcpy( digits, B.digits, MAXDIGITS * sizeof(char));
	return B;
}

ostream & operator << ( ostream & os, const BigInteger & A )
{
	int i;
	if ( A.signbit == -1 )
		os << "-";
	for ( i = A.lastdigit; i >= 0; i-- )
		os << (char) ( A.digits[i] + '0' );
	return os;
}

istream & operator >> ( istream & is, BigInteger & A )
{
	A.initialize();
	char * str = new char[MAXDIGITS];
	int len, i, j;
	is >> str;
	len = strlen( str );
	A.signbit = ( str[0] == '-' ) ? -1 : 1;
	A.lastdigit = len - ( ( str[0] == '-' ) ? 2 : 1 );
	for ( i = len - 1, j = 0; i >= ( str[0] == '-' ) ? 1 : 0; i--, j++ )
		A.digits[j] = str[i] - '0';
	A.digits[j] = 0;
	delete [] str;
	return is;
}

BigInteger   operator <<  ( BigInteger & A, int d )
{
	BigInteger B = A;
	if ( B.lastdigit == 0 && B.digits[0] == 0 )
		return B;
	int i;
	for ( i = B.lastdigit; i >= 0; i-- )
		B.digits[i + d] = B.digits[i];
	for ( i = 0; i < d; i++ )
		B.digits[i] = 0;
	B.lastdigit += d;
	return B;
}

BigInteger & operator <<= ( BigInteger & A, int d )
{
	if ( A.lastdigit == 0 && A.digits[0] == 0 )
		return A;
	int i;
	for ( i = A.lastdigit; i >= 0; i-- )
		A.digits[i + d] = A.digits[i];
	for ( i = 0; i < d; i++ )
		A.digits[i] = 0;
	A.lastdigit += d;
	return A;
}

bool operator > ( BigInteger & A, BigInteger & B )
{
	char mark = 0;
	if ( A.signbit * B.signbit == -1 )
	{
		if ( A.signbit == -1 && B.signbit == 1 )
			return 0;
		else
			return 1;
	}
	if ( A.signbit == 1 && B.signbit == 1 )
		mark = 1;
	if ( A.lastdigit > B.lastdigit )
		return ( mark ) ? 1 : 0;
	if ( A.lastdigit < B.lastdigit )
		return ( mark ) ? 0 : 1;
	for ( int i = A.lastdigit; i >= 0; i-- )
	{
		if ( A.digits[i] > B.digits[i] )
			return ( mark ) ? 1 : 0;
		if ( A.digits[i] < B.digits[i] )
			return ( mark ) ? 0 : 1;
	}
	return 0;
}

BigInteger operator + ( BigInteger & A, BigInteger & B )
{
	int carry, i;
	BigInteger C;
	if ( A.signbit == B.signbit )
		C.signbit = A.signbit;
	else
	{
		if ( A.signbit == -1 )
		{
			A.signbit = 1;
			C = B - A;
			A.signbit = -1;
		}
		else
		{
			B.signbit = 1;
			C = A - B;
			B.signbit = -1;
		}
		return C;
	}
	C.lastdigit = MAX( A.lastdigit, B.lastdigit ) + 1;
	carry = 0;
	for ( i = 0; i <= C.lastdigit; i++ )
	{
		C.digits[i] = ( carry + A.digits[i] + B.digits[i] ) % 10;
		carry = ( carry + A.digits[i] + B.digits[i] ) / 10;
	}
	C.zero_justify();
	return C;
}

BigInteger operator - ( BigInteger & A, BigInteger & B )
{
	int borrow, i, v;
	BigInteger C;
	if ( A.signbit == -1 || B.signbit == -1 )
	{
		B.signbit *= -1;
		C = A + B;
		B.signbit *= -1;
		return C;
	}
	if ( B > A )
	{
		C = B - A;
		C.signbit = -1;
		return C;
	}
	C.lastdigit = MAX( A.lastdigit, B.lastdigit );
	borrow = 0;
	for ( i = 0; i <= C.lastdigit; i++ )
	{
		v = A.digits[i] - B.digits[i] - borrow;
		if ( A.digits[i] > 0 )
			borrow = 0;
		if ( v < 0 )
		{
			v += 10;
			borrow = 1;
		}
		C.digits[i] = v % 10;
	}
	C.zero_justify();
	return C;
}

BigInteger operator * ( BigInteger & A, BigInteger & B )
{
	int i;
	BigInteger C, tmp;
	tmp = A;
	for ( i = 0; i <= B.lastdigit; i++ )
	{
		BigInteger TMP = tmp * B.digits[i];
		C = C + TMP;
		tmp <<= 1;
	}
	C.signbit = A.signbit * B.signbit;
	C.zero_justify();
	return C;
}

BigInteger operator / ( BigInteger & A, BigInteger & B )
{
	int i;
	BigInteger C, row;
	//���������������ֱ�ӷ����㡣
	if ( B.lastdigit == 0 && B.digits[0] == 0 )
		return C;
	char A_signbit, B_signbit;
	C.signbit = A.signbit * B.signbit;
	A_signbit = A.signbit;
	B_signbit = B.signbit;
	A.signbit = B.signbit = 1;
	if ( B > A )
		return C;
	C.lastdigit = A.lastdigit;
	for ( i = A.lastdigit; i >= 0; i-- )
	{
		row <<= 1;
		row.digits[0] = A.digits[i];
		C.digits[i] = 0;
		while ( !( B > row ) )
		{
			C.digits[i]++;
			row = row - B;
		}
	}
	C.zero_justify();
	A.signbit = A_signbit;
	B.signbit = B_signbit;
	return C;
}

BigInteger operator % ( BigInteger & A, BigInteger & B )
{
	BigInteger tmp = A / B;
	BigInteger TMP = B * tmp;
	return ( A - TMP );
}

BigInteger operator * ( BigInteger & A, long long n )
{
	int i, len;
	unsigned long long sum, carry;
	char num[20];
	BigInteger C;
	if ( n < 0 )
	{
		n = -n;
		C.signbit = A.signbit * -1;
	}
	else
		C.signbit = A.signbit;
	sprintf( num, "%d", n );
	len = strlen( num );
	C.lastdigit = A.lastdigit + len;
	carry = 0;
	for ( i = 0; i <= C.lastdigit; i++ )
	{
		sum = A.digits[i] * n + carry;
		C.digits[i] = sum % 10;
		carry = sum / 10;
	}
	C.zero_justify();
	return C;
}

BigInteger operator / ( BigInteger & A, long long n )
{
	BigInteger C;
	if ( n == 0 )
		return C;
	if ( n < 0 )
	{
		n = -n;
		C.signbit = A.signbit * -1;
	}
	else
		C.signbit = A.signbit;
	int i;
	unsigned long long remain;
	remain = 0;
	C.lastdigit = A.lastdigit;
	for ( i = C.lastdigit; i >= 0; i-- )
	{
		remain *= 10;
		remain += A.digits[i];
		C.digits[i] = remain / n;
		remain -= C.digits[i] * n;
	}
	C.zero_justify();
	return C;
}

BigInteger operator * ( long long n, BigInteger & A )
{
	return A * n;
}

BigInteger operator ^ ( BigInteger A, int B )
{
	if ( B == 0 )
		return BigInteger(1);
	if ( B == 1 )
		return A;
	if ( B == 2 )
		return A * A;
	BigInteger tmp1 = ( ( A ^ ( B / 2 ) ) ^ 2 ), tmp2 = ( A ^ ( B % 2 ) );
	return tmp1 * tmp2;
}

int main()
{
}
