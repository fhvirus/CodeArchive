#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[6],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
using namespace std;

const int N = 1e4 + 225;
int n, q;

/* Start Suffix Automaton */
short sz, last;
short ch[N*2][26], len[N*2], par[N*2], cnt[N*2];
short tmp[N*2];
inline void init(){
	len[0] = 0;
	par[0] = -1;
	for(short i = 0; i <= sz; ++i){
		len[i] = 0;
		par[i] = -1;
		cnt[i] = 0;
		for(short j = 0; j < 26; ++j)
			ch[i][j] = 0;
	}
	sz = 1;
	last = 0;
}
inline void add(char c){
	short cur = sz++;
	len[cur] = len[last] + 1;
	cnt[cur] = 1;
	par[cur] = 0;

	short p = last;
	while(p != -1 and ch[p][c] == 0)
		ch[p][c] = cur,
		p = par[p];

	if(p == -1){
		par[cur] = 0;
	} else {
		short q = ch[p][c];
		if(len[p] + 1 == len[q]){
			par[cur] = q;
		} else {
			short clone = sz++;
			len[clone] = len[p] + 1;
			for(int i = 0; i < 26; ++i)
				ch[clone][i] = ch[q][i];
			par[clone] = par[q];
			while(p != -1 and ch[p][c] == q){
				ch[p][c] = clone;
				p = par[p];
			}
			par[q] = par[cur] = clone;
		}
	}

	last = cur;
}
inline void buildSAM(){
	init();
	char c = RC();
	while(c < 'a') c = RC();
	while(c >= 'a')
		add(c - 'a'), c = RC();
	for(int i = 0; i < sz; ++i) tmp[i] = i;
	sort(tmp, tmp + sz, [](int a, int b){return len[a] > len[b];});
	for(int i = 0; i < sz; ++i) cnt[par[tmp[i]]] += cnt[tmp[i]];
}
/* End Suffix Automaton */

inline short solve(){
	short cur = 0;
	bool ans = true;
	char c = RC();
	while(c < 'a') c = RC();
	while(c >= 'a'){
		if(ch[cur][c - 'a'] == 0){ ans = false; break;}
		cur = ch[cur][c - 'a'], c = RC();
	}
	if(!ans) while(c >= 'a') c = RC();
	return ans ? cnt[cur] : 0;
}

int main(){
	n = R();
	for(; n; --n){
		buildSAM();
		for(q = R(); q; --q) W(solve());
	}
	write(1,OB,OP);
	return 0;
}