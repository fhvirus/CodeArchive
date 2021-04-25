#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

int n, k, cnt[26];
char c;

int main(){
	n = R();
	for(; n; --n){
		k = R();
		while((c = RC()) < 'a');
		for(int i = 0; i < 26; ++i) cnt[i] = 0;
		for(; k; --k)
			++cnt[c - 'a'],
			c = RC();
		int mx = 0;
		for(int i = 0; i < 26; ++i)
			mx = (mx > cnt[i] ? mx : cnt[i]);
		for(int i = 0; i < 26; ++i)
			(cnt[i] == mx) and (OB[OP++] = 'a' + i);
		OB[OP++] = ('\n');
	}
	write(1, OB, OP);
}