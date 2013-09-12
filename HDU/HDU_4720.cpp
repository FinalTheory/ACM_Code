/**
 * @file HDU_4720.cpp
 * @brief   计算几何入门题，可以看作是计算三角形外心的位置。
 *	    但是还是需要额外考虑钝角三角形的情况，所以最好直接枚举一遍。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-11
 */
#include <cstdio>
#include <cmath>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define eps 0.000001
using namespace std;
const int INF = 0x3f3f3f3f;
struct point{double x,y;} p[3];
struct line{point a,b;};

point intersection(line u,line v){
	point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
		/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}
point circumcenter(point a,point b,point c){
	line u,v;
	u.a.x=(a.x+b.x)/2;
	u.a.y=(a.y+b.y)/2;
	u.b.x=u.a.x-a.y+b.y;
	u.b.y=u.a.y+a.x-b.x;
	v.a.x=(a.x+c.x)/2;
	v.a.y=(a.y+c.y)/2;
	v.b.x=v.a.x-a.y+c.y;
	v.b.y=v.a.y+a.x-c.x;
	return intersection(u,v);
}
double distance(point p1,point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

point middle( point p1, point p2 )
{
	point ret = {( p1.x + p2.x ) / 2., ( p1.y + p2.y ) / 2.};
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
	int T, idx;
	point Muggle;
	scanf("%d", &T);
	for ( idx = 1; idx <= T; ++idx )
	{
		for ( int i = 0; i < 3; ++i )
			scanf("%lf %lf", &p[i].x, &p[i].y);
		scanf("%lf %lf", &Muggle.x, &Muggle.y);
		point mid0 = circumcenter( p[0], p[1], p[2] );
		double r0 = distance( mid0, p[0] );
		point mid1 = middle( p[0], p[1] );
		double r1 = distance( p[0], p[1] ) / 2.;
		if ( distance( mid1, p[2] ) < r1 && r1 < r0 )
		{
			mid0 = mid1;
			r0 = r1;
		}
		point mid2 = middle( p[1], p[2] );
		double r2 = distance( p[1], p[2] ) / 2.;
		if ( distance( mid2, p[0] ) < r2 && r2 < r0 )
		{
			mid0 = mid2;
			r0 = r2;
		}
		point mid3 = middle( p[2], p[0] );
		double r3 = distance( p[2], p[0] ) / 2.;
		if ( distance( mid3, p[1] ) < r3 && r3 < r0 )
		{
			mid0 = mid3;
			r0 = r3;
		}
		double r = distance( mid0, Muggle );
		printf("Case #%d: ", idx);
		//printf("%lf %lf %lf %lf\n", distance( p[0], mid ), distance( p[1], mid ), distance( p[2], mid ), r2);
		if ( r - r0 > eps )
			puts("Safe");
		else
			puts("Danger");
	}
}
