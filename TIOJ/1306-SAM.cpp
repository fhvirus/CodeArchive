#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
inline int RS(char s[]){
	int len = 0;
	while((s[0] = RC()) < 'a' or s[0] > 'z');
	len++;
	while((s[len] = RC()) >= 'a' and s[len] <= 'z') ++len;
	return len;
}

#include<algorithm>
using namespace std;

const int N = 1e4 + 225;
int n, q;
char t[N], p[N];
int lent, lenp;

/* Start Suffix Automaton */
int sz, last;
struct state{
	short ch[26];
	short len, par, cnt;
} st[N * 2];

short tmp[N * 2];
inline void init(){
	st[0].len = 0;
	st[0].par = -1;
	for(int i = 0; i <= sz; ++i){
		st[i].len = 0;
		st[i].par = -1;
		st[i].cnt = 0;
		for(int j = 0; j < 26; ++j)
			st[i].ch[j] = 0;
	}
	sz = 1;
	last = 0;
}
inline void add(char c){
	short cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].cnt = 1;
	st[cur].par = 0;

	short p = last;
	while(p != -1 and st[p].ch[c] == 0){
		st[p].ch[c] = cur;
		p = st[p].par;
	}
	if(p == -1){
		st[cur].par = 0;
	} else {
		short q = st[p].ch[c];
		if(st[p].len + 1 == st[q].len){
			st[cur].par = q;
		} else {
			short clone = sz++;
			st[clone].len = st[p].len + 1;
			for(int i = 0; i < 26; ++i)
				st[clone].ch[i] = st[q].ch[i];
			st[clone].par = st[q].par;
			while(p != -1 and st[p].ch[c] == q){
				st[p].ch[c] = clone;
				p = st[p].par;
			}
			st[q].par = st[cur].par = clone;
		}
	}

	last = cur;
}
inline void buildSAM(){
	init();
	for(int i = 0; i < lent; ++i)
		add(t[i] - 'a');
	for(int i = 0; i < sz; ++i)
		tmp[i] = i;
	sort(tmp, tmp + sz, [](int a, int b){
		return st[a].len > st[b].len;
	});
	for(int i = 0; i < sz; ++i)
		st[st[tmp[i]].par].cnt += st[tmp[i]].cnt;
}
/* End Suffix Automaton */

inline int solve(){
	int cur = 0;
	for(int i = 0; i < lenp; ++i){
		if(st[cur].ch[p[i] - 'a'] == 0) return 0;
		cur = st[cur].ch[p[i] - 'a'];
	}
	return st[cur].cnt;
}

#include<cstdio>

int main(){
	n = R();
	for(; n; --n){
		lent = RS(t);
		buildSAM();
		q = R();
		for(; q; --q){
			lenp = RS(p);
			W(solve());
		}
	}
	write(1,OB,OP);
	return 0;
}