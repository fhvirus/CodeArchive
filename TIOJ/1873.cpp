#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

const int N = 1e5+1;

struct point{
	int x, y;
	point(){}
} P[N], G[N];
int Pptr = 0, Gptr = 0, tmp;
bool minus;
char eek;

const char END = "END Z";
char ENDPTR = 0;

int main(){
	while(true){
		Pptr = Gptr = ENDPTR = 0;
		eek = readchar();
		while((eek <= '9' and eek >= '0') or eek == '-' or eek == ' ' or eek == '\n'){
			// read pos
			eek = readchar();
		}
		while(eek != 'Z') eek = readchar();
		while(true){
			eek = readchar();
			if(eek == END[ENDPTR]){
				ENDPTR++;
				if(ENDPTR == 5) break;
			}

			// read int
			if((eek <= '9' and eek >= '0') or eek == '-'){
				// read a girl's pos
				// tmp = 0;
				// if(eek == '-') minus = true, eek = readchar();
				// else minus = false;
				// while(eek <= '9' and eek >= '0') tmp = (tmp<<3) + (tmp<<1) + (c ^ '0'), eek = readchar();
			} else {
				while(eek != 'Z') eek = readchar();
			}
		}
		
	}
}