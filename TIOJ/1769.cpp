#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
typedef unsigned long long ull;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline ull R(){
	ull ans = 0;
	char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

ull t, h, H;
bool flag;

ull stone[1<<20], mn;
const ull INF = 18446744073709551615ull;

int main(){
	t = R();
	for(;t;--t){
		h = R(); H = (1<<(h+1))-1;
		flag = true; mn = INF;
		for(int i = 0; i < H; ++i){
			stone[i] = R();
			if(stone[i] < mn) mn = stone[i];
		}

		int eek = __builtin_clzll(mn);

		for(int i = 0; i < H; ++i){
			int jizz = eek - __builtin_clzll(stone[i]);
			stone[i] >>= jizz;
			if(stone[i] != mn or jizz > h){
				flag = false;
				break;
			}
		}

		puts(flag ? "dodge" : "do not dodge");
	}
	return 0;
}