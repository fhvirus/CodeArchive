#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
#include<cstdio>
int n;
inline void eek(int R, int G, int B, int &X, int &Y, int &Z){
	X = 5149 * R + 3244 * G + 1607 * B;
	Y = 2654 * R + 6704 * G +  642 * B;
	Z =  248 * R + 1248 * G + 8504 * B;
}

char OB[65536]; int OP;
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65516)write(1,OB,OP),OP=0;}
inline void WD(int x, char e){
	W(x / 10000);
	OB[OP++] = ('.');
	OB[OP++] = (x % 10000 / 1000 + '0');
	OB[OP++] = (x % 1000 / 100 + '0');
	OB[OP++] = (x % 100 / 10 + '0');
	OB[OP++] = (x % 10 + '0');
	OB[OP++] = (e);
	if(OP > 65516) write(1,OB,OP), OP=0;
}

int main(){
	double sumy = 0;
	n = R();

	int r, g, b;
	int x, y, z;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			r = R(), g = R(), b = R();
			eek(r, g, b, x, y, z);
			WD(x, ' ');
			WD(y, ' ');
			WD(z, '\n');
			sumy += y;
		}
	}
	write(1,OB,OP);
	printf("The average of Y is %.4lf\n", sumy / n / n / 10000.0);
}