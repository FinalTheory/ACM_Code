/**
 * @file HDU_1166.cpp
 * @brief   ��״����ģ��
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#define MAX 50010
int Tree[MAX];
//���㵱ǰ�ڵ�����֧���Ԫ�ظ���
inline int Lowbit( int x )
{
	return x & (-x);
}

//num of elements
int N;
void Add( int pos, int num )
{
	while ( pos <= N )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}
//Calculate the sum of 1 ~ pos
//��������ÿ�μ�ȥ��ǰ�ڵ���֧���Ԫ�ظ���
//ֱ��λ�ñ�Ϊ�㣬Ҳ�����˻������еĿ�ͷλ�á�
int Query( int pos )
{
	int sum = 0;
	//ע���������Ϊ�㣬������ѭ��
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
}
