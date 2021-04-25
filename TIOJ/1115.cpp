#include<unistd.h>
#include<cstdio>
#include<cmath>
char OB[12502]; int OP;
inline bool RD(double &d){
	return scanf("%lf",&d) != -1;
}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];}
inline void WD(double n){
	int x = (n * 1000 + 5) / 10;
	W(x / 100);
	x %= 100;
	OB[OP++] = '.';
	OB[OP++] = x / 10 + '0';
	OB[OP++] = x % 10 + '0';
	OB[OP++]='\n';if(OP>12490)write(1,OB,OP),OP=0;
}

const double PI = 3.1415926535;
int main(){
	double x, y, r, angle, tri;
	while(RD(x)){
		RD(y);
		RD(r);
		if(y + r <= 0) WD(0);
		else if(y - r >= 0) WD(PI * r * r);
		else if(y >= 0){
			angle = acos(y / r);
			tri   = y * sqrt(r * r - y * y);
			WD(r * r * (PI - angle) + tri);
		} else {
			angle = acos(-y / r);
			tri   = -y * sqrt(r * r - y * y);
			WD(r * r * angle - tri);
		}
	}
	write(1,OB,OP);
	return 0;
}