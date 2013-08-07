#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cstring>
#include <random>
#define DEBUG 1
#define TEST_LEVEL 2
//#define OUTPUT 1
#define MAXDATASIZE 10000000
#define SCALE_ordered 0.2
#define SCALE_unordered 0.05
#define MAX_DEPTH 10000
using namespace std;
unsigned long long compare_times;	//关键字比较次数
unsigned long long move_times;	//关键字移动次数
unsigned num[MAXDATASIZE];
unsigned Pointer[MAXDATASIZE];
unsigned max_depth = 0;
unsigned char LEVEL = TEST_LEVEL;
clock_t program_start, program_end;


//比较函数
bool fuck( unsigned A, unsigned B )
{
#ifdef DEBUG
	++compare_times;
#endif // DEBUG
	return A < B;
}
//交换函数
template <class Any>
inline void swap ( Any * A, Any * B )
{
#ifdef DEBUG
	move_times += 3;
#endif // DEBUG
	Any TMP = *A;
	*A = *B;
	*B = TMP;
}
//冒泡排序
template <class Any>
void BubbleSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	char changed;
	Any * Pointer_A, * Pointer_B;
	for ( Pointer_A = Begin; Pointer_A < End - 1; Pointer_A ++ )
	{
		changed = 0;
		for ( Pointer_B = End - 2; Pointer_B >= Pointer_A; Pointer_B -- )
			if ( compare( *( Pointer_B + 1 ), *Pointer_B ) )
			{
				changed = 1;
				swap( Pointer_B + 1, Pointer_B );
			}
		if ( !changed )
			return;
	}
}
//选择排序
template <class Any>
void SelectSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	Any * Pointer_A, * Pointer_B, * Key;
	for ( Pointer_A = Begin; Pointer_A < End - 1; Pointer_A ++ )
	{
		Key = Pointer_A;
		for ( Pointer_B = Pointer_A + 1; Pointer_B < End; Pointer_B ++ )
			if ( compare( *Pointer_B, *Key ) )
				Key = Pointer_B;
		if ( Key != Pointer_A )
			swap( Pointer_A, Key );
	}
}
//插入排序
template <class Any>
void InsertSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	Any * Pointer_A, * Pointer_B, Key;
	for ( Pointer_A = Begin + 1; Pointer_A < End; Pointer_A ++ )
	{
		if ( compare( *Pointer_A, *( Pointer_A - 1 ) ) )
		{
#ifdef DEBUG
			++move_times;
#endif // DEBUG
			Key = * Pointer_A;
			Pointer_B = Pointer_A - 1;
			do
			{
#ifdef DEBUG
				++move_times;
#endif // DEBUG
				*( Pointer_B + 1 ) = *Pointer_B;
				--Pointer_B;
			}
			while ( Pointer_B >= Begin && compare( Key, *Pointer_B ) );
#ifdef DEBUG
			++move_times;
#endif // DEBUG
			*( Pointer_B + 1 ) = Key;
		}
	}
}
//快速排序
template <class Any>
void  __QuickSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ), char stop )
{
	static unsigned depth = 0;
	if ( End - 1 > Begin && !stop )
	{
		++depth;
		if ( depth > max_depth )
			max_depth = depth;
		if ( depth > MAX_DEPTH )
		{
			cout << "Stack overflow!\n";
			stop = 1;
		}
		Any * Pointer_A = Begin, * Pointer_B = End - 1, Key = * Pointer_A, * Pos;
		while ( Pointer_A < Pointer_B )
		{
			while ( Pointer_A < Pointer_B && !compare( * Pointer_B, Key ) )
				--Pointer_B;
			if ( Pointer_A < Pointer_B )
			{
#ifdef DEBUG
				++move_times;
#endif // DEBUG
				*(Pointer_A++) = *Pointer_B;
			}
			while ( Pointer_A < Pointer_B && !compare( Key, * Pointer_A ) )
				++Pointer_A;
			if ( Pointer_A < Pointer_B )
			{
#ifdef DEBUG
				++move_times;
#endif // DEBUG
				*(Pointer_B--) = *Pointer_A;
			}
		}
#ifdef DEBUG
		++move_times;
#endif // DEBUG
		* Pointer_A = Key;
		Pos = Pointer_A;
		__QuickSort( Begin,   Pos, compare, stop );
		__QuickSort( Pos + 1, End, compare, stop );
		--depth;
	}
}
template <class Any>
void  QuickSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	__QuickSort( Begin, End, compare, 0 );
}
//希尔排序
unsigned Dlta[1000];
unsigned Incre = MAXDATASIZE - 1;
template <class Any>
void ShellInsert( Any * const Begin, Any * const End, bool compare( Any A, Any B ), const unsigned Incre )
{
	Any * Pointer_A, * Pointer_B, Key;
	for ( Pointer_A = Begin + Incre; Pointer_A < End; ++ Pointer_A )
	{
		if ( compare( *Pointer_A, *( Pointer_A - Incre ) ) )
		{
#ifdef DEBUG
			++move_times;
#endif // DEBUG
			Key = * Pointer_A;
			Pointer_B = Pointer_A - Incre;
			do
			{
#ifdef DEBUG
				++move_times;
#endif // DEBUG
				*( Pointer_B + Incre ) = *Pointer_B;
				Pointer_B -= Incre;
			}
			while ( Pointer_B >= Begin && compare( Key, *Pointer_B ) );
#ifdef DEBUG
			++move_times;
#endif // DEBUG
			*( Pointer_B + Incre ) = Key;
		}
	}
}
template <class Any>
void  ShellSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	unsigned i = 1;
	if ( !Dlta[0] )
	{
		do 
		{
			Dlta[i++] = Incre;
			Incre = Incre / 3 + 1;
		} while ( Incre > 1 );
		Dlta[i] = 1;
		Dlta[0] = i;
	}
	for ( i = 1; i <= Dlta[0]; i++ )
		ShellInsert( Begin, End, compare, Dlta[i] );
}
//堆排序
template <class Any>
void HeapAdjust( Any * const Begin, unsigned Root, unsigned Max, bool compare( Any A, Any B ) )
{
	unsigned i;
	Any Record = Begin[Root];
	for ( i = 2 * Root; i <= Max; i *= 2 )
	{
		if ( i < Max && compare( Begin[i], Begin[i + 1] ) )
			++i;
		if ( !compare( Record, Begin[i] ) )
			break;
#ifdef DEBUG
		++move_times;
#endif // DEBUG
		Begin[Root] = Begin[i];
		Root = i;
	}
#ifdef DEBUG
	++move_times;
#endif // DEBUG
	Begin[Root] = Record;
}
template <class Any>
void   HeapSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	unsigned len = End - Begin, i;
	for ( i = len / 2; i > 0; --i )
		HeapAdjust( Begin - 1, i, len, compare );
	for ( i = len; i > 1; --i )
	{
		swap( Begin, Begin + i - 1 );
		HeapAdjust( Begin - 1, 1, i - 1, compare );
	}
}
//归并排序
template <class Any>
void Merge( Any * Buffer, unsigned Low, unsigned Mid, unsigned High, bool compare( Any A, Any B ) )
{
	unsigned i = Low, j = Mid, pointer = 0;
	Any * Result = new Any [High - Low];
	while ( i < Mid && j < High )
	{
#ifdef DEBUG
		++move_times;
#endif // DEBUG
		Result[pointer++] = !compare( Buffer[j], Buffer[i] ) ? Buffer[i++] : Buffer[j++];
	}
	while ( i < Mid )
	{
#ifdef DEBUG
		++move_times;
#endif // DEBUG
		Result[pointer++] = Buffer[i++];
	}
	while ( j < High )
	{
#ifdef DEBUG
		++move_times;
#endif // DEBUG
		Result[pointer++] = Buffer[j++];
	}
#ifdef DEBUG
	move_times += High - Low;
#endif // DEBUG
	memcpy( Buffer + Low, Result, sizeof(Any) * ( High - Low ) );
	delete [] Result;
}
template <class Any>
void  MergeSort( Any * const Begin, Any * const End, bool compare( Any A, Any B ) )
{
	unsigned Len = End - Begin, pos, length;
	for ( length = 1; length < Len; length *= 2 )
	{
		for ( pos = 0; pos + 2 * length <= Len; pos += 2 * length )
			Merge( Begin, pos, pos + length, pos + 2 * length, compare );
		if ( pos + length < Len )	//此时归并排序pos~pos+length-1和pos+length~Len；恰好有一个子文件时pos+length=Len。
			Merge( Begin, pos, pos + length, Len, compare );
	}
}

char str[8][11] = { "InsertSort",\
					"SelectSort",\
					"BubbleSort",\
					"QuickSort",\
					"HeapSort",\
					"ShellSort",\
					"MergeSort",\
					"STL sort" };
void  (*Functions[8])( unsigned * const Begin,\
					   unsigned * const End, \
					   bool compare( unsigned A, unsigned B ) ) = {\
					   InsertSort<unsigned>,\
					   SelectSort<unsigned>,\
					   BubbleSort<unsigned>,\
					   QuickSort <unsigned>,\
					   HeapSort  <unsigned>,\
					   ShellSort <unsigned>,\
					   MergeSort <unsigned>,\
					   sort };

void RunTest( unsigned index )
{
	unsigned size;
	cout << str[index] << " test:\n\n";
	for ( size = 10; size <= MAXDATASIZE; size *= 10 )
	{
		cout << "Current data size: " << size << '\n';
		
		//跳过时间过长的测试以及会导致堆栈溢出的测试。
		if ( index < 100 && size >= 100000 )
			continue;
		if ( LEVEL == 2 || LEVEL == 3 && size >= 100000 && Functions[index] == QuickSort <unsigned> )
			continue;

		memcpy( Pointer, num, sizeof(num) );
		move_times = compare_times = 0;
		program_start = clock();
		Functions[index]( Pointer, Pointer + size, fuck );
		program_end = clock();
		cout << /*"Time consumed: " << */( program_end - program_start ) << " MS" << '\n';
		cout << /*"Key compared times: " <<*/ compare_times << '\n';
		if ( index != 8 )	//STL sort()无法计算关键字移动次数
			cout << /*"Key moved times: " <<*/ move_times << '\n';
#ifdef OUTPUT
		fout.open( str[index] );
		for ( int j = 0; j < size; ++j )
			fout << Pointer[j] << ' ';
		fout.close();
#endif
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	freopen( "out.txt", "w", stdout );
	std::ios::sync_with_stdio(false);
	unsigned i, index;
	ofstream fout;
	while ( LEVEL )
	{
		switch ( LEVEL-- )
		{
		case 5 :
			cout << "\n5% unordered data test:\n\n";
			for ( i = 0; i < MAXDATASIZE; ++i )
			{
				if ( (double) rand() / RAND_MAX < SCALE_unordered )
					num[i] = rand();
				else
					num[i] = i + 1;
			}
			for ( index = 0; index < 8; ++index )
				RunTest( index );
						break;
		case 4 :
			cout << "\n20% ordered data test:\n\n";
			for ( i = 0; i < MAXDATASIZE; ++i )
			{
				if ( (double) rand() / RAND_MAX < SCALE_ordered )
					num[i] = i + 1;
				else
					num[i] = rand();
			}
			for ( index = 0; index < 8; ++index )
				RunTest( index );
						break;
		case 3 :
			cout << "\nOrdered data test:\n\n";
			for ( i = 0; i < MAXDATASIZE; ++i )
				num[i] = i + 1;
			for ( index = 0; index < 8; ++index )
				RunTest( index );
						break;
		case 2 :
			cout << "\nUnordered data test:\n\n";
			for ( i = 0; i < MAXDATASIZE; ++i )
				num[i] = MAXDATASIZE - i;
			for ( index = 0; index < 8; ++index )
				RunTest( index );
						break;
		case 1 :
			srand( (unsigned) time( NULL ) );
			cout << "\nRandom data test. The max random number: " << RAND_MAX << "\n\n";
			for ( i = 0; i < MAXDATASIZE; ++i )
				num[i] = rand();
			for ( index = 0; index < 8; ++index )
				RunTest( index );
		default:
			break;
		}
	}
}