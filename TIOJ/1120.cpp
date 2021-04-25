#include<unistd.h>
char OB[2048]; int OP;
inline char RC(){static char buf[2048],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,2048))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return -1;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){if(n > 9) OB[OP++] = n / 10 + '0'; OB[OP++] = n % 10 + '0';}

int x[40] = {10,11,12,13,14,15,15,15,15,15,15,15,15,15,15,15,14,13,12,11,10,9,8,7,6,5,5,5,5,5,5,5,5,5,5,5,6,7,8,9,};
int y[40] = {5,5,5,5,5,5,6,7,8,9,10,11,12,13,14,15,15,15,15,15,15,15,15,15,15,15,14,13,12,11,10,9,8,7,6,5,5,5,5,5,};

int main(){
	int t;
	while((t = R()) != -1){
		t = t * 6 % 40;
		OB[OP++] = '(';
		W(x[t]);
		OB[OP++] = ',';
		W(y[t]);
		OB[OP++] = ')';
		OB[OP++]='\n';
		if(OP > 2021) write(1,OB,OP),OP=0;
	}
	write(1,OB,OP);
	return 0;
}
