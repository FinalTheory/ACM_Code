/**
 * @file ZOJ_3705.cpp
 * @brief   模拟题，各种无节操STL，1A甚爽！注意素数打表范围！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-18
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <sstream>
#include <iomanip>
#define MAX 10000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char prime[MAX+10];
void Init_Prime()
{
	int i, j, k, tmp;
	memset( prime, 1, sizeof(prime) );
	for ( i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
}

struct TMD
{
	string name;
	double score;
};

bool fuck( const TMD & A, const TMD & B )
{
	if ( A.score != B.score )
		return A.score > B.score;
	else
		return A.name < B.name; 
}

bool fuck2( const int A, const int B )
{
	return A > B;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	Init_Prime();
	int T, N, M, R, S, i, index, Q, j, problems, onlines;
	set<int> MMS, OSC;
	set<int> :: iterator set_iter;
	map<string, int> team;
	map<string, int> :: iterator iter;
	map<string, double> person;
	map<string, double> :: iterator p_iter;
	vector <int> ratings;
	vector<TMD> res;
	string name, p_name;
	char buffer[100], team_name[100], per_name[100], sex[4];
	scanf("%d", &T);
	while ( T-- )
	{
		MMS.clear(); OSC.clear(); team.clear(); person.clear(); res.clear();
		scanf("%d %d", &N, &M);
		scanf("%d", &R);
		for ( i = 0; i < R; ++i )
		{
			scanf("%d", &index);
			MMS.insert(index);
		}
		scanf("%d", &S);
		for ( i = 0; i < S; ++i )
		{
			scanf("%d", &index);
			OSC.insert(index);
		}
		scanf("%d", &Q);
		for ( i = 0; i < Q; ++i )
		{
			scanf("%s %d", buffer, &index);
			name = buffer;
			team[name] = index;
		}
		for ( i = 0; i < N; ++i )
		{
			scanf("%s %s %s %d %d", per_name, team_name, sex, &problems, &onlines );
			p_name = per_name;
			person[p_name] = 0.0;
			p_iter = person.find(p_name);
			//校内赛的加分 
			name = team_name;
			iter = team.find(name);
			if ( iter != team.end() )
			{
				switch ( iter->second )
				{
				case 3:
					p_iter->second += 18;
					break;
				case 2:
					p_iter->second += 27;
					break;
				case 1:
					p_iter->second += 36;
					break;
				}
			}
			if ( sex[0] == 'F' ) p_iter->second += 33;
			for ( j = 0; j < problems; ++j )
			{
				scanf("%d", &index);
				set_iter = MMS.find(index);
				if ( set_iter != MMS.end() )
				{
					p_iter->second += 2.5;
					continue;
				}
				set_iter = OSC.find(index);
				if ( set_iter != OSC.end() )
				{
					p_iter->second += 1.5;
					continue;
				}
				if ( prime[index] )
					p_iter->second += 1;
				else
					p_iter->second += 0.3;
			}
			ratings.clear();
			for ( j = 0; j < onlines; ++j )
			{
				scanf("%d", &index);
				ratings.push_back(index);
			}
			if ( ratings.size() >= 3 )
			{
				sort(ratings.begin(), ratings.end(), fuck2);
				p_iter->second += max( 0., (((double)ratings[2]-1200.) / 100.)*1.5 );
			}
		}
		TMD tmp;
		for ( p_iter = person.begin(); p_iter != person.end(); ++p_iter )
		{
			tmp.name = p_iter->first;
			tmp.score = p_iter->second;
			res.push_back(tmp);
		}
		sort( res.begin(), res.end(), fuck );
		for ( i = 0; i < M; ++i )
			printf("%s %.3lf\n", res[i].name.c_str(), res[i].score);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

