#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!=-1);a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<cstdio>
const int N = 1e6+2, INF = 8e7;
int n, count[128], l, r, ansl, ansr, appear;
char s[N];

int main(){
	while((n = R()) != 0){
		for(int i = 0; i < 26; ++i) count[i+'a'] = 0;
		l = 0, r = 0, ansl = 0, ansr = INF, appear = 0;
		s[0] = RC();
		while(s[0] > 'z' or s[0] < 'a') s[0] = RC();
		for(; r < n; ++r){
			s[r+1] = RC();
			if(count[s[r]] == 0) ++appear;
			++count[s[r]];
			while(count[s[l]] > 1) --count[s[l]], ++l;
			if(appear == 26 and r - l < ansr - ansl) ansl = l, ansr = r;
			if(ansr - ansl == 25) break;
		}
		if(appear < 26){
			puts("not found");
		}
		else{
			s[ansr+1] = '\0';
			puts(s + ansl);
		}
	}
}