#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    if(n < 0) outbuf[outp++] = '-', n = -n;
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

#include<queue>
#include<functional>
int s = 1, cmd, x;

std::priority_queue<int> mx;
std::priority_queue<int, std::vector<int>, std::greater<int>> mn;

inline void CMD(){
	char c;
	while((c = readchar()) != 'P' and c != 'G' and c != 'E');
	cmd = (c == 'P' ? 0 : (c == 'G' ? 1 : ((c = readchar()) == 'X' ? 2 : 3)));
	while(c <= 'Z' and c >= 'A') c = readchar();
}

int main(){
	while(true){
		CMD();
		if(cmd == 0){
			x = R();
			mx.push(x);
			if(mx.size() > s) mn.push(mx.top()), mx.pop();
		} else if(cmd == 1){
			if(s <= mx.size() + mn.size()){
				W(mx.top()), ++s;
				if(mx.size() < s and !mn.empty()) mx.push(mn.top()), mn.pop();
			}
		} else if(cmd == 2){
			s = 1;
			mx = {}, mn = {};
		} else {
			fwrite(outbuf, 1, outp, stdout);
			return 0;
		}
	}
}