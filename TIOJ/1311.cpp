#include<unistd.h>
#define int unsigned
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline int gcd(int a, int b){
	while(b) a %= b, a ^= b, b ^= a, a ^= b;
	return a;
}
signed main(){
	int z, x1, x2, y1, y2;
	while(z = R(), z != 0){
		x1 = R(), x2 = R(), y1 = R(), y2 = R();
		for(int y = y1; y <= y2; ++y){
			for(int x = x1; x <= x2; ++x)
				OB[OP++] = (gcd(z, gcd(x, y)) == 1 ? 
					'*' : '.');
			OB[OP++] = ('\n');
		}
		OB[OP++] = '-';
		OB[OP++] = '-';
		OB[OP++] = '\n';
		if(OP > 65436) write(1,OB,OP),OP=0;
	}
	write(1,OB,OP);
	return 0;
}