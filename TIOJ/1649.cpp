#pragma GCC optimize("Ofast")
#include<cstdio>
typedef long long ull;
inline char readchar(){
	const int S = 1<<14;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline ull R(){
	ull ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline void W(int n){
    if(n == 0){ putchar_unlocked('0'); return;}
    int rev = n, count = 0;
    while((rev % 10) == 0) count++, rev /= 10;
    rev = 0;
    while(n != 0) rev = (rev<<3) + (rev<<1) + n % 10, n /= 10;
    while(rev != 0) putchar_unlocked(rev % 10 + '0'), rev /= 10;
    while(count--) putchar_unlocked('0');
}

int n, ans;
ull h, curh, damage;

int main(){
	n = R(); h = curh = R();
	for(; n; --n){
		damage = R();
		if(damage >= h){ putchar_unlocked('-'); putchar_unlocked('1'); return 0;}
		if(damage >= curh){ curh = h; ++ans;}
		curh -= damage;
	}
	W(ans);
}